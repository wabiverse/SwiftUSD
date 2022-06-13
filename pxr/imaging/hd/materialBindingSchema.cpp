//
// Copyright 2021 Pixar
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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// schema.template.cpp file to make changes.

#include "pxr/imaging/hd/materialBindingSchema.h"
#include "pxr/imaging/hd/retainedDataSource.h"

#include "pxr/base/trace/trace.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdMaterialBindingSchemaTokens,
    HDMATERIALBINDING_SCHEMA_TOKENS);


HdPathDataSourceHandle 
HdMaterialBindingSchema::GetMaterialBinding()
{
    return _GetTypedDataSource<HdPathDataSource>(
            HdMaterialBindingSchemaTokens->allPurpose);
}

HdPathDataSourceHandle
HdMaterialBindingSchema::GetMaterialBinding(TfToken const &purpose)
{
    if (auto b = _GetTypedDataSource<HdPathDataSource>(purpose)) {
        return b;
    }

    // If we can't find the purpose-specific binding, return the fallback.
    return _GetTypedDataSource<HdPathDataSource>(
            HdMaterialBindingSchemaTokens->allPurpose);
}


/*static*/
HdContainerDataSourceHandle
HdMaterialBindingSchema::BuildRetained(
    size_t count,
    TfToken *names,
    HdDataSourceBaseHandle *values)
{
    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdMaterialBindingSchema
HdMaterialBindingSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdMaterialBindingSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdMaterialBindingSchemaTokens->materialBinding))
        : nullptr);
}

/*static*/
const HdDataSourceLocator &
HdMaterialBindingSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
        HdMaterialBindingSchemaTokens->materialBinding
    );
    return locator;
} 
PXR_NAMESPACE_CLOSE_SCOPE