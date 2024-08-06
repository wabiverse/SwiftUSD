//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/dataSourcePoints.h"
#include "UsdImaging/dataSourcePrimvars.h"

#include "UsdGeom/points.h"

#include "Hd/overlayContainerDataSource.h"
#include "Hd/primvarsSchema.h"
#include "Hd/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdImagingDataSourcePointsPrim::UsdImagingDataSourcePointsPrim(
    const SdfPath &sceneIndexPath,
    UsdPrim usdPrim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
    : UsdImagingDataSourceGprim(sceneIndexPath, usdPrim, stageGlobals)
{
}

static const UsdImagingDataSourceCustomPrimvars::Mappings &_GetCustomPrimvarMappings(
    const UsdPrim &usdPrim)
{
  static const UsdImagingDataSourceCustomPrimvars::Mappings mappings = {
      {HdPrimvarsSchemaTokens->widths, UsdGeomTokens->widths},
  };

  return mappings;
}

HdDataSourceBaseHandle UsdImagingDataSourcePointsPrim::Get(const TfToken &name)
{
  HdDataSourceBaseHandle const result = UsdImagingDataSourceGprim::Get(name);

  if (name == HdPrimvarsSchema::GetSchemaToken()) {
    return HdOverlayContainerDataSource::New(
        HdContainerDataSource::Cast(result),
        UsdImagingDataSourceCustomPrimvars::New(_GetSceneIndexPath(),
                                                _GetUsdPrim(),
                                                _GetCustomPrimvarMappings(_GetUsdPrim()),
                                                _GetStageGlobals()));
  }

  return result;
}

/*static*/
HdDataSourceLocatorSet UsdImagingDataSourcePointsPrim::Invalidate(
    UsdPrim const &prim,
    const TfToken &subprim,
    const TfTokenVector &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  HdDataSourceLocatorSet result = UsdImagingDataSourceGprim::Invalidate(
      prim, subprim, properties, invalidationType);

  if (subprim.IsEmpty()) {
    result.insert(UsdImagingDataSourceCustomPrimvars::Invalidate(properties,
                                                                 _GetCustomPrimvarMappings(prim)));
  }

  return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
