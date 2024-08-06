//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/dataSourceNurbsPatch.h"

#include "UsdImaging/dataSourceMapped.h"

#include "UsdGeom/nurbsPatch.h"

#include "Hd/nurbsPatchSchema.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/primvarsSchema.h"
#include "Hd/retainedDataSource.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

HdDataSourceLocator _ToLocator(const TfToken &name)
{
  const TfTokenVector tokens = SdfPath::TokenizeIdentifierAsTokens(name);
  return HdDataSourceLocator(tokens.size(), tokens.data());
}

std::vector<UsdImagingDataSourceMapped::AttributeMapping> _GetAttributeMappings()
{
  std::vector<UsdImagingDataSourceMapped::AttributeMapping> result;

  // Pick up from UsdGeomGprim
  result.push_back(
      {UsdGeomTokens->doubleSided, HdDataSourceLocator(HdNurbsPatchSchemaTokens->doubleSided)});
  result.push_back(
      {UsdGeomTokens->orientation, HdDataSourceLocator(HdNurbsPatchSchemaTokens->orientation)});

  for (const TfToken &usdName : UsdGeomNurbsPatch::GetSchemaAttributeNames(
           /* includeInherited = */ false))
  {
    if (usdName == UsdGeomTokens->pointWeights) {
      // Suppress pointWeights from UsdGeomNurbsCurves (which is a custom
      // primvar we process in the prim source below).
      continue;
    }

    result.push_back({usdName, _ToLocator(usdName)});
  }

  return result;
}

const UsdImagingDataSourceMapped::AttributeMappings &_GetMappings()
{
  static const UsdImagingDataSourceMapped::AttributeMappings result(
      _GetAttributeMappings(), HdNurbsPatchSchema::GetDefaultLocator());
  return result;
}

const UsdImagingDataSourceCustomPrimvars::Mappings &_GetCustomPrimvarMappings(
    const UsdPrim &usdPrim)
{
  static const TfToken &hdPrimvarName = UsdGeomTokens->pointWeights;

  static const UsdImagingDataSourceCustomPrimvars::Mappings mappings = {
      {hdPrimvarName, UsdGeomTokens->pointWeights},
  };

  return mappings;
}

}  // namespace

// ----------------------------------------------------------------------------

UsdImagingDataSourceNurbsPatchPrim::UsdImagingDataSourceNurbsPatchPrim(
    const SdfPath &sceneIndexPath,
    UsdPrim usdPrim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
    : UsdImagingDataSourceGprim(sceneIndexPath, usdPrim, stageGlobals)
{
}

TfTokenVector UsdImagingDataSourceNurbsPatchPrim::GetNames()
{
  TfTokenVector result = UsdImagingDataSourceGprim::GetNames();
  result.push_back(HdNurbsPatchSchema::GetSchemaToken());
  return result;
}

HdDataSourceBaseHandle UsdImagingDataSourceNurbsPatchPrim::Get(const TfToken &name)
{
  if (name == HdNurbsPatchSchema::GetSchemaToken()) {
    return UsdImagingDataSourceMapped::New(
        _GetUsdPrim(), _GetSceneIndexPath(), _GetMappings(), _GetStageGlobals());
  }
  if (name == HdPrimvarsSchema::GetSchemaToken()) {
    return HdOverlayContainerDataSource::New(
        HdContainerDataSource::Cast(UsdImagingDataSourceGprim::Get(name)),
        UsdImagingDataSourceCustomPrimvars::New(_GetSceneIndexPath(),
                                                _GetUsdPrim(),
                                                _GetCustomPrimvarMappings(_GetUsdPrim()),
                                                _GetStageGlobals()));
  }

  return UsdImagingDataSourceGprim::Get(name);
}

HdDataSourceLocatorSet UsdImagingDataSourceNurbsPatchPrim::Invalidate(
    UsdPrim const &prim,
    const TfToken &subprim,
    const TfTokenVector &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  TRACE_FUNCTION();

  HdDataSourceLocatorSet locators = UsdImagingDataSourceMapped::Invalidate(properties,
                                                                           _GetMappings());

  locators.insert(
      UsdImagingDataSourceGprim::Invalidate(prim, subprim, properties, invalidationType));

  locators.insert(
      UsdImagingDataSourceCustomPrimvars::Invalidate(properties, _GetCustomPrimvarMappings(prim)));

  return locators;
}

PXR_NAMESPACE_CLOSE_SCOPE
