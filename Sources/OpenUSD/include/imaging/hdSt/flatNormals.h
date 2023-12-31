//
// Copyright 2018 Pixar
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
#ifndef PXR_IMAGING_HD_ST_FLAT_NORMALS_H
#define PXR_IMAGING_HD_ST_FLAT_NORMALS_H

#include "pxr/pxr.h"
#include "pxr/imaging/hdSt/api.h"
#include "pxr/imaging/hdSt/computation.h"

#include "pxr/imaging/hd/bufferSource.h"
#include "pxr/imaging/hd/flatNormals.h"

#include "pxr/base/tf/token.h"

PXR_NAMESPACE_OPEN_SCOPE


/// \class HdSt_FlatNormalsComputationCPU
///
/// Flat normal computation CPU.
///
class HdSt_FlatNormalsComputationCPU : public HdComputedBufferSource
{
public:
    HDST_API
    HdSt_FlatNormalsComputationCPU(
        HdMeshTopology const *topology,
        HdBufferSourceSharedPtr const &points,
        TfToken const &dstName,
        bool packed);

    HDST_API
    void GetBufferSpecs(HdBufferSpecVector *specs) const override;

    HDST_API
    bool Resolve() override;

    HDST_API
    TfToken const &GetName() const override;

protected:
    HDST_API
    bool _CheckValid() const override;

private:
    HdMeshTopology const *_topology;
    HdBufferSourceSharedPtr const _points;
    TfToken _dstName;
    bool _packed;
};

/// \class HdSt_FlatNormalsComputationGPU
///
/// Flat normal computation GPU.
///
class HdSt_FlatNormalsComputationGPU : public HdStComputation
{
public:
    HDST_API
    HdSt_FlatNormalsComputationGPU(
        HdBufferArrayRangeSharedPtr const &topologyRange,
        HdBufferArrayRangeSharedPtr const &vertexRange,
        int numFaces,
        TfToken const &srcName,
        TfToken const &dstName,
        HdType srcDataType,
        bool packed);

    HDST_API
    void GetBufferSpecs(HdBufferSpecVector *specs) const override;

    HDST_API
    void Execute(HdBufferArrayRangeSharedPtr const &range,
                 HdResourceRegistry *resourceRegistry) override;

    int GetNumOutputElements() const override;

private:
    HdBufferArrayRangeSharedPtr const _topologyRange;
    HdBufferArrayRangeSharedPtr const _vertexRange;
    int _numFaces;
    TfToken _srcName;
    TfToken _dstName;
    HdType _srcDataType;
    HdType _dstDataType;
};


PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HD_ST_FLAT_NORMALS_H
