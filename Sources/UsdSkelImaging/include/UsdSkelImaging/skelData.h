//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_SKEL_IMAGING_SKEL_DATA_H
#define PXR_USD_IMAGING_USD_SKEL_IMAGING_SKEL_DATA_H

#include "UsdSkelImaging/api.h"

#include "UsdSkelImaging/animationSchema.h"
#include "UsdSkelImaging/skeletonSchema.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceTypeDefs.h"

#include "Sdf/path.h"
#include "UsdSkel/animMapper.h"
#include "UsdSkel/topology.h"

#include "Vt/array.h"

#include "Tf/declarePtrs.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DECLARE_REF_PTRS(HdSceneIndexBase);

/// Some of the data necessary to compute the skinning transforms of a skeleton.
/// These data come from the skeleton and the skelAnimation's joints.
struct UsdSkelImagingSkelData
{
    /// Path of deformable prim. Used only for warnings/error messages.
    SdfPath primPath;

    UsdSkelImagingSkeletonSchema skeletonSchema;

    /// From skeleton's joints.
    UsdSkelTopology topology;

    /// From skeleton.
    VtArray<GfMatrix4f> bindTransforms;
    VtArray<GfMatrix4f> inverseBindTransforms;

    UsdSkelImagingSkelData(const SdfPath& path, 
        const UsdSkelImagingSkeletonSchema& schema);
};

/// Compute data for prim in scene index.
USDSKELIMAGING_API
UsdSkelImagingSkelData
UsdSkelImagingComputeSkelData(
    HdSceneIndexBaseRefPtr const &sceneIndex,
    const SdfPath &primPath);

/// Compute skinning transforms for extComputation.
USDSKELIMAGING_API
VtArray<GfMatrix4f>
UsdSkelImagingComputeSkinningTransforms(
    const UsdSkelImagingSkelData &data,
    /// From skeleton (might not be needed).
    HdMatrix4fArrayDataSourceHandle const &restTransforms,
    const VtArray<UsdSkelImagingAnimationSchema>& animationSchemas,
    const VtArray<SdfPath>& animationSources,
    const HdSampledDataSource::Time& shutterOffset);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
