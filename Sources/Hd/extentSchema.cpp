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

#include "Hd/extentSchema.h"
#include "Hd/retainedDataSource.h"

#include "Trace/traceImpl.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdExtentSchemaTokens,
    HDEXTENT_SCHEMA_TOKENS);



HdVec3dDataSourceHandle
HdExtentSchema::GetMin()
{
    return _GetTypedDataSource<HdVec3dDataSource>(
        HdExtentSchemaTokens->min);
}

HdVec3dDataSourceHandle
HdExtentSchema::GetMax()
{
    return _GetTypedDataSource<HdVec3dDataSource>(
        HdExtentSchemaTokens->max);
}

/*static*/
HdContainerDataSourceHandle
HdExtentSchema::BuildRetained(
        const HdVec3dDataSourceHandle &min,
        const HdVec3dDataSourceHandle &max
)
{
    TfToken names[2];
    HdDataSourceBaseHandle values[2];

    size_t count = 0;
    if (min) {
        names[count] = HdExtentSchemaTokens->min;
        values[count++] = min;
    }

    if (max) {
        names[count] = HdExtentSchemaTokens->max;
        values[count++] = max;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdExtentSchema
HdExtentSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdExtentSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdExtentSchemaTokens->extent))
        : nullptr);
}

/*static*/
const TfToken &
HdExtentSchema::GetSchemaToken()
{
    return HdExtentSchemaTokens->extent;
} 
/*static*/
const HdDataSourceLocator &
HdExtentSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
        HdExtentSchemaTokens->extent
    );
    return locator;
} 
HdExtentSchema::Builder &
HdExtentSchema::Builder::SetMin(
    const HdVec3dDataSourceHandle &min)
{
    _min = min;
    return *this;
}

HdExtentSchema::Builder &
HdExtentSchema::Builder::SetMax(
    const HdVec3dDataSourceHandle &max)
{
    _max = max;
    return *this;
}

HdContainerDataSourceHandle
HdExtentSchema::Builder::Build()
{
    return HdExtentSchema::BuildRetained(
        _min,
        _max
    );
}


PXR_NAMESPACE_CLOSE_SCOPE
