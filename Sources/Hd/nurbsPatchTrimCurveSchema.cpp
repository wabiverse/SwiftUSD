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

#include "Hd/nurbsPatchTrimCurveSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/nurbsPatchSchema.h"

#include "Trace/traceImpl.h"


PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PUBLIC_TOKENS(HdNurbsPatchTrimCurveSchemaTokens,
    HDNURBSPATCHTRIMCURVE_SCHEMA_TOKENS);



HdIntArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetCounts()
{
    return _GetTypedDataSource<HdIntArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->counts);
}

HdIntArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetOrders()
{
    return _GetTypedDataSource<HdIntArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->orders);
}

HdIntArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetVertexCounts()
{
    return _GetTypedDataSource<HdIntArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->vertexCounts);
}

HdDoubleArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetKnots()
{
    return _GetTypedDataSource<HdDoubleArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->knots);
}

HdVec2dArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetRanges()
{
    return _GetTypedDataSource<HdVec2dArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->ranges);
}

HdVec3dArrayDataSourceHandle
HdNurbsPatchTrimCurveSchema::GetPoints()
{
    return _GetTypedDataSource<HdVec3dArrayDataSource>(
        HdNurbsPatchTrimCurveSchemaTokens->points);
}

/*static*/
HdContainerDataSourceHandle
HdNurbsPatchTrimCurveSchema::BuildRetained(
        const HdIntArrayDataSourceHandle &counts,
        const HdIntArrayDataSourceHandle &orders,
        const HdIntArrayDataSourceHandle &vertexCounts,
        const HdDoubleArrayDataSourceHandle &knots,
        const HdVec2dArrayDataSourceHandle &ranges,
        const HdVec3dArrayDataSourceHandle &points
)
{
    TfToken names[6];
    HdDataSourceBaseHandle values[6];

    size_t count = 0;
    if (counts) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->counts;
        values[count++] = counts;
    }

    if (orders) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->orders;
        values[count++] = orders;
    }

    if (vertexCounts) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->vertexCounts;
        values[count++] = vertexCounts;
    }

    if (knots) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->knots;
        values[count++] = knots;
    }

    if (ranges) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->ranges;
        values[count++] = ranges;
    }

    if (points) {
        names[count] = HdNurbsPatchTrimCurveSchemaTokens->points;
        values[count++] = points;
    }

    return HdRetainedContainerDataSource::New(count, names, values);
}

/*static*/
HdNurbsPatchTrimCurveSchema
HdNurbsPatchTrimCurveSchema::GetFromParent(
        const HdContainerDataSourceHandle &fromParentContainer)
{
    return HdNurbsPatchTrimCurveSchema(
        fromParentContainer
        ? HdContainerDataSource::Cast(fromParentContainer->Get(
                HdNurbsPatchTrimCurveSchemaTokens->trimCurve))
        : nullptr);
}

/*static*/
const TfToken &
HdNurbsPatchTrimCurveSchema::GetSchemaToken()
{
    return HdNurbsPatchTrimCurveSchemaTokens->trimCurve;
} 
/*static*/
const HdDataSourceLocator &
HdNurbsPatchTrimCurveSchema::GetDefaultLocator()
{
    static const HdDataSourceLocator locator(
        HdNurbsPatchSchemaTokens->nurbsPatch,
        HdNurbsPatchTrimCurveSchemaTokens->trimCurve
    );
    return locator;
} 
HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetCounts(
    const HdIntArrayDataSourceHandle &counts)
{
    _counts = counts;
    return *this;
}

HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetOrders(
    const HdIntArrayDataSourceHandle &orders)
{
    _orders = orders;
    return *this;
}

HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetVertexCounts(
    const HdIntArrayDataSourceHandle &vertexCounts)
{
    _vertexCounts = vertexCounts;
    return *this;
}

HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetKnots(
    const HdDoubleArrayDataSourceHandle &knots)
{
    _knots = knots;
    return *this;
}

HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetRanges(
    const HdVec2dArrayDataSourceHandle &ranges)
{
    _ranges = ranges;
    return *this;
}

HdNurbsPatchTrimCurveSchema::Builder &
HdNurbsPatchTrimCurveSchema::Builder::SetPoints(
    const HdVec3dArrayDataSourceHandle &points)
{
    _points = points;
    return *this;
}

HdContainerDataSourceHandle
HdNurbsPatchTrimCurveSchema::Builder::Build()
{
    return HdNurbsPatchTrimCurveSchema::BuildRetained(
        _counts,
        _orders,
        _vertexCounts,
        _knots,
        _ranges,
        _points
    );
}


PXR_NAMESPACE_CLOSE_SCOPE