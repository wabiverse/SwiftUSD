//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/motionAPIAdapter.h"

#include "UsdImaging/apiSchemaAdapter.h"
#include "UsdImaging/dataSourcePrimvars.h"
#include "UsdImaging/dataSourceStageGlobals.h"
#include "UsdImaging/types.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"
#include "Hd/primvarSchema.h"
#include "Hd/primvarsSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/tokens.h"

#include "Usd/prim.h"
#include "UsdGeom/tokens.h"

#include "Tf/registryManager.h"
#include "Tf/token.h"
#include "Tf/type.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    using Adapter = UsdImagingMotionAPIAdapter;
    TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
    t.SetFactory<UsdImagingAPISchemaAdapterFactory<Adapter>>();
}

namespace {

const UsdImagingDataSourceCustomPrimvars::Mappings &
_GetMotionPrimvarMappings()
{
    static const UsdImagingDataSourceCustomPrimvars::Mappings mappings = {
        { HdTokens->blurScale,
          UsdGeomTokens->motionBlurScale,
          HdPrimvarSchemaTokens->constant },
        { HdTokens->nonlinearSampleCount,
          UsdGeomTokens->motionNonlinearSampleCount,
          HdPrimvarSchemaTokens->constant },
    };
    return mappings;
}

} // anonymous namespace

HdContainerDataSourceHandle
UsdImagingMotionAPIAdapter::GetImagingSubprimData(
    UsdPrim const& prim,
    TfToken const& subprim,
    TfToken const& appliedInstanceName,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
    // MotionAPI is not a multi-apply schema.
    if (!appliedInstanceName.IsEmpty()) {
        return nullptr;
    }

    // This adapter only contributes to the primary prim, not subprims.
    if (!subprim.IsEmpty()) {
        return nullptr;
    }

    return HdRetainedContainerDataSource::New(
        HdPrimvarsSchema::GetSchemaToken(),
        UsdImagingDataSourceCustomPrimvars::New(
            prim.GetPath(),
            prim,
            _GetMotionPrimvarMappings(),
            stageGlobals));
}

HdDataSourceLocatorSet
UsdImagingMotionAPIAdapter::InvalidateImagingSubprim(
    UsdPrim const& prim,
    TfToken const& subprim,
    TfToken const& appliedInstanceName,
    TfTokenVector const& properties,
    UsdImagingPropertyInvalidationType invalidationType)
{
    if (!appliedInstanceName.IsEmpty() || !subprim.IsEmpty()) {
        return HdDataSourceLocatorSet();
    }

    return UsdImagingDataSourceCustomPrimvars::Invalidate(
        properties, _GetMotionPrimvarMappings());
}

PXR_NAMESPACE_CLOSE_SCOPE
