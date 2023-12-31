//
// Copyright 2017 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/imaging/hdSt/extCompPrimvarBufferSource.h"
#include "pxr/imaging/hdSt/extCompCpuComputation.h"

#include "pxr/imaging/hd/vtBufferSource.h"

PXR_NAMESPACE_OPEN_SCOPE


HdStExtCompPrimvarBufferSource::HdStExtCompPrimvarBufferSource(
    const TfToken &primvarName,
    const HdStExtCompCpuComputationSharedPtr &source,
    const TfToken &sourceOutputName,
    const HdTupleType &valueType)
    : HdBufferSource()
    , _primvarName(primvarName)
    , _source(source)
    , _sourceOutputIdx(HdStExtCompCpuComputation::INVALID_OUTPUT_INDEX)
    , _tupleType(valueType)
    , _rawDataPtr(nullptr)
{
    _sourceOutputIdx = source->GetOutputIndex(sourceOutputName);
}

HdStExtCompPrimvarBufferSource::~HdStExtCompPrimvarBufferSource() = default;

TfToken const &
HdStExtCompPrimvarBufferSource::GetName() const
{
    return _primvarName;
}

void
HdStExtCompPrimvarBufferSource::GetBufferSpecs(HdBufferSpecVector *specs) const
{
    specs->emplace_back(_primvarName, _tupleType);
}

template <class HashState>
void TfHashAppend(HashState &h, HdStExtCompPrimvarBufferSource const &bs)
{
    // Simply return a hash based on the computation and primvar names, 
    // instead of hashing the contents of the inputs to the computation.
    // This effectively disables primvar sharing when using computed primvars.
    h.Append(bs._source->GetName(),
             bs._primvarName);
}

size_t
HdStExtCompPrimvarBufferSource::ComputeHash() const
{
    return TfHash()(*this);
}

bool
HdStExtCompPrimvarBufferSource::Resolve()
{
    bool sourceValid = _source->IsValid();
    if (sourceValid) {
        if (!_source->IsResolved()) {
            return false;
        }
    }

    if (!_TryLock()) return false;

    if (!sourceValid || _source->HasResolveError()) {
        _SetResolveError();
        return true;
    }

    HdVtBufferSource output(_primvarName,
                            _source->GetOutputByIndex(_sourceOutputIdx));

    // Validate output type and count matches what is expected.
    if (output.GetTupleType() != _tupleType) {
        TF_WARN("Output type mismatch on %s. ", _primvarName.GetText());
        _SetResolveError();
        return true;
    }
    if (output.GetNumElements() != _source->GetNumElements()) {
        TF_WARN("Output elements mismatch on %s. ", _primvarName.GetText());
        _SetResolveError();
        return true;
    }

    _rawDataPtr = output.GetData();

    _SetResolved();
    return true;
}


void const *
HdStExtCompPrimvarBufferSource::GetData() const
{
    return _rawDataPtr;
}

HdTupleType
HdStExtCompPrimvarBufferSource::GetTupleType() const
{
    return _tupleType;
}

size_t
HdStExtCompPrimvarBufferSource::GetNumElements() const
{
    return _source->GetNumElements();
}

bool
HdStExtCompPrimvarBufferSource::_CheckValid() const
{
    return (_source &&
            (_sourceOutputIdx !=
                        HdStExtCompCpuComputation::INVALID_OUTPUT_INDEX) &&
            (_tupleType.type != HdTypeInvalid));
}


PXR_NAMESPACE_CLOSE_SCOPE

