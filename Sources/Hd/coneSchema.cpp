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

#include "Hd/coneSchema.h"
#include "Hd/retainedDataSource.h"

#include "Trace/traceImpl.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdConeSchemaTokens,
    HDCONE_SCHEMA_TOKENS);



HdDoubleDataSourceHandle
HdConeSchema::GetHeight()
{
    return _GetTypedDataSource<HdDoubleDataSource>(
        HdConeSchemaTokens->height);
}

HdDoubleDataSourceHandle
HdConeSchema::GetRadius()
{
    return _GetTypedDataSource<HdDoubleDataSource>(
        HdConeSchemaTokens->radius);
}

HdTokenDataSourceHandle
HdConeSchema::GetAxis()
{
    return _GetTypedDataSource<HdTokenDataSource>(
        HdConeSchemaTokens->axis);
}

/*static*/
HdContainerDataSourceHandle
HdConeSchema::BuildRetained(
        const HdDoubleDataSourceHandle &height,
        const HdDoubleDataSourceHandle &radius,
        const HdTokenDataSourceHandle &axis
)
{
    TfToken names[3];
    HdDataSourceBaseHandle values[3];

    size_t count = 0;
    if (height) {
        names[count] = HdConeSchemaTokens->height;
        values[count++] = height;
    }

    if (radius) {
        names[count] = HdConeSchemaTokens->radius;
        values[count++] = radius;
    }

    if (axis) {
        names[count] = HdConeSchemaTokens->axis;
        values[count++] = axis;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdConeSchema
HdConeSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdConeSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdConeSchemaTokens->cone))
        : nullptr);
}

/*static*/
const TfToken &
HdConeSchema::GetSchemaToken()
{
    return HdConeSchemaTokens->cone;
} 
/*static*/
const HdDataSourceLocator &
HdConeSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
        HdConeSchemaTokens->cone
    );
    return locator;
} 
HdConeSchema::Builder &
HdConeSchema::Builder::SetHeight(
    const HdDoubleDataSourceHandle &height)
{
    _height = height;
    return *this;
}

HdConeSchema::Builder &
HdConeSchema::Builder::SetRadius(
    const HdDoubleDataSourceHandle &radius)
{
    _radius = radius;
    return *this;
}

HdConeSchema::Builder &
HdConeSchema::Builder::SetAxis(
    const HdTokenDataSourceHandle &axis)
{
    _axis = axis;
    return *this;
}

HdContainerDataSourceHandle
HdConeSchema::Builder::Build()
{
    return HdConeSchema::BuildRetained(
        _height,
        _radius,
        _axis
    );
}


PXR_NAMESPACE_CLOSE_SCOPE
