//
// Copyright 2023 Pixar
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

/* ************************************************************************** */
/* ** This file is generated by a script.  Do not edit directly.  Edit     ** */
/* ** defs.py or the (*)Schema.template.cpp files to make changes.         ** */
/* ************************************************************************** */

#include "Hd/materialBindingSchema.h"
#include "Hd/retainedDataSource.h"

#include "Trace/traceImpl.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdMaterialBindingSchemaTokens,
    HDMATERIALBINDING_SCHEMA_TOKENS);



HdPathDataSourceHandle
HdMaterialBindingSchema::GetPath()
{
    return _GetTypedDataSource<HdPathDataSource>(
        HdMaterialBindingSchemaTokens->path);
}

HdTokenDataSourceHandle
HdMaterialBindingSchema::GetBindingStrength()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdMaterialBindingSchemaTokens->bindingStrength);
}

/*static*/
HdContainerDataSourceHandle
HdMaterialBindingSchema::BuildRetained(
        const HdPathDataSourceHandle &path,
        const HdTokenDataSourceHandle &bindingStrength
)
{
    TfToken names[2];
    HdDataSourceBaseHandle values[2];

    size_t count = 0;
    if (path) {
        names[count] = HdMaterialBindingSchemaTokens->path;
        values[count++] = path;
    }

    if (bindingStrength) {
        names[count] = HdMaterialBindingSchemaTokens->bindingStrength;
        values[count++] = bindingStrength;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}


HdMaterialBindingSchema::Builder &
HdMaterialBindingSchema::Builder::SetPath(
    const HdPathDataSourceHandle &path)
{
    _path = path;
    return *this;
}

HdMaterialBindingSchema::Builder &
HdMaterialBindingSchema::Builder::SetBindingStrength(
    const HdTokenDataSourceHandle &bindingStrength)
{
    _bindingStrength = bindingStrength;
    return *this;
}

HdContainerDataSourceHandle
HdMaterialBindingSchema::Builder::Build()
{
    return HdMaterialBindingSchema::BuildRetained(
        _path,
        _bindingStrength
    );
}


PXR_NAMESPACE_CLOSE_SCOPE