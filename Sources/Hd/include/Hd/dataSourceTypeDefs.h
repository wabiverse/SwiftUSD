//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_DATASOURCETYPEDEFS_H
#define PXR_IMAGING_HD_DATASOURCETYPEDEFS_H

#include "pxr/pxrns.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"
#include "Hd/types.h"

#include "Gf/matrix4d.h"
#include "Gf/vec2f.h"
#include "Tf/staticTokens.h"
#include "Vt/array.h"

#include "Ar/resolverContext.h"
#include "Sdf/assetPath.h"
#include "Sdf/path.h"
#include "Sdf/pathExpression.h"

PXR_NAMESPACE_OPEN_SCOPE

// Numeric
using HdIntDataSource = HdTypedSampledDataSource<int>;
using HdIntDataSourceHandle = HdIntDataSource::Handle;
using HdIntArrayDataSource = HdTypedSampledDataSource<VtArray<int>>;
using HdIntArrayDataSourceHandle = HdIntArrayDataSource::Handle;

using HdSizetDataSource = HdTypedSampledDataSource<size_t>;
using HdSizetDataSourceHandle = HdSizetDataSource::Handle;

using HdFloatDataSource = HdTypedSampledDataSource<float>;
using HdFloatDataSourceHandle = HdFloatDataSource::Handle;
using HdDoubleDataSource = HdTypedSampledDataSource<double>;
using HdDoubleDataSourceHandle = HdDoubleDataSource::Handle;
using HdFloatArrayDataSource = HdTypedSampledDataSource<VtArray<float>>;
using HdFloatArrayDataSourceHandle = HdFloatArrayDataSource::Handle;
using HdDoubleArrayDataSource = HdTypedSampledDataSource<VtArray<double>>;
using HdDoubleArrayDataSourceHandle = HdDoubleArrayDataSource::Handle;

// Bool
using HdBoolDataSource = HdTypedSampledDataSource<bool>;
using HdBoolDataSourceHandle = HdBoolDataSource::Handle;
using HdBoolArrayDataSource = HdTypedSampledDataSource<VtArray<bool>>;
using HdBoolArrayDataSourceHandle = HdBoolArrayDataSource::Handle;

// String
using HdTokenDataSource = HdTypedSampledDataSource<TfToken>;
using HdTokenDataSourceHandle = HdTokenDataSource::Handle;
using HdTokenArrayDataSource = HdTypedSampledDataSource<VtArray<TfToken>>;
using HdTokenArrayDataSourceHandle = HdTokenArrayDataSource::Handle;

using HdPathDataSource = HdTypedSampledDataSource<SdfPath>;
using HdPathDataSourceHandle = HdPathDataSource::Handle;
using HdPathArrayDataSource = HdTypedSampledDataSource<VtArray<SdfPath>>;
using HdPathArrayDataSourceHandle = HdPathArrayDataSource::Handle;

using HdStringDataSource = HdTypedSampledDataSource<std::string>;
using HdStringDataSourceHandle = HdStringDataSource::Handle;

using HdAssetPathDataSource = HdTypedSampledDataSource<SdfAssetPath>;
using HdAssetPathDataSourceHandle = HdAssetPathDataSource::Handle;

using HdPathExpressionDataSource = HdTypedSampledDataSource<SdfPathExpression>;
using HdPathExpressionDataSourceHandle = HdPathExpressionDataSource::Handle;

// Linear algebra
using HdVec2iDataSource = HdTypedSampledDataSource<GfVec2i>;
using HdVec2iDataSourceHandle = HdVec2iDataSource::Handle;
using HdVec2fDataSource = HdTypedSampledDataSource<GfVec2f>;
using HdVec2fDataSourceHandle = HdVec2fDataSource::Handle;
using HdVec2dDataSource = HdTypedSampledDataSource<GfVec2d>;
using HdVec2dDataSourceHandle = HdVec2dDataSource::Handle;
using HdVec2fArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec2f>>;
using HdVec2fArrayDataSourceHandle = HdVec2fArrayDataSource::Handle;
using HdVec2dArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec2d>>;
using HdVec2dArrayDataSourceHandle = HdVec2dArrayDataSource::Handle;

using HdVec3iDataSource = HdTypedSampledDataSource<GfVec3i>;
using HdVec3iDataSourceHandle = HdVec3iDataSource::Handle;
using HdVec3iArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec3i>>;
using HdVec3iArrayDataSourceHandle = HdVec3iArrayDataSource::Handle;
using HdVec3fDataSource = HdTypedSampledDataSource<GfVec3f>;
using HdVec3fDataSourceHandle = HdVec3fDataSource::Handle;
using HdVec3fArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec3f>>;
using HdVec3fArrayDataSourceHandle = HdVec3fArrayDataSource::Handle;
using HdVec3dDataSource = HdTypedSampledDataSource<GfVec3d>;
using HdVec3dDataSourceHandle = HdVec3dDataSource::Handle;
using HdVec3dArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec3d>>;
using HdVec3dArrayDataSourceHandle = HdVec3dArrayDataSource::Handle;

using HdVec4iDataSource = HdTypedSampledDataSource<GfVec4i>;
using HdVec4iDataSourceHandle = HdVec4iDataSource::Handle;
using HdVec4iArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec4i>>;
using HdVec4iArrayDataSourceHandle = HdVec4iArrayDataSource::Handle;
using HdVec4fDataSource = HdTypedSampledDataSource<GfVec4f>;
using HdVec4fDataSourceHandle = HdVec4fDataSource::Handle;
using HdVec4dArrayDataSource = HdTypedSampledDataSource<VtArray<GfVec4d>>;
using HdVec4dArrayDataSourceHandle = HdVec4dArrayDataSource::Handle;

using HdMatrixDataSource = HdTypedSampledDataSource<GfMatrix4d>;
using HdMatrixDataSourceHandle = HdMatrixDataSource::Handle;
using HdMatrixArrayDataSource = HdTypedSampledDataSource<VtArray<GfMatrix4d>>;
using HdMatrixArrayDataSourceHandle = HdMatrixArrayDataSource::Handle;

// Locator
using HdLocatorDataSource = HdTypedSampledDataSource<HdDataSourceLocator>;
using HdLocatorDataSourceHandle = HdLocatorDataSource::Handle;

// Enum
using HdFormatDataSource = HdTypedSampledDataSource<HdFormat>;
using HdFormatDataSourceHandle = HdFormatDataSource::Handle;

using HdTupleTypeDataSource = HdTypedSampledDataSource<HdTupleType>;
using HdTupleTypeDataSourceHandle = HdTupleTypeDataSource::Handle;

// ArResolverContext
using HdResolverContextDataSource = HdTypedSampledDataSource<ArResolverContext>;
using HdResolverContextDataSourceHandle = HdResolverContextDataSource::Handle;

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_DATASOURCETYPEDEFS_H
