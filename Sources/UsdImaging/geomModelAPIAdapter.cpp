//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/geomModelAPIAdapter.h"

#include "Hd/extentSchema.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/retainedDataSource.h"
#include "Hd/tokens.h"
#include "Kind/registry.h"
#include "Usd/modelAPI.h"
#include "UsdGeom/modelAPI.h"
#include "UsdImaging/dataSourceMapped.h"
#include "UsdImaging/geomModelSchema.h"
#include "UsdImaging/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

std::vector<UsdImagingDataSourceMapped::AttributeMapping> _GetAttributeMappings()
{
  std::vector<UsdImagingDataSourceMapped::AttributeMapping> result;

  for (const TfToken &usdName : UsdGeomModelAPI::GetSchemaAttributeNames(
           /* includeInherited = */ false))
  {

    const std::pair<std::string, bool> nameAndMatch = SdfPath::StripPrefixNamespace(
        usdName.GetString(), "model");
    if (nameAndMatch.second) {
      result.push_back({usdName, HdDataSourceLocator(TfToken(nameAndMatch.first))});
    }
  }

  return result;
}

const UsdImagingDataSourceMapped::AttributeMappings &_GetMappings()
{
  static const UsdImagingDataSourceMapped::AttributeMappings result(
      _GetAttributeMappings(), UsdImagingGeomModelSchema::GetDefaultLocator());
  return result;
}

}  // namespace

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdImagingGeomModelAPIAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingAPISchemaAdapterFactory<Adapter>>();
}

HdContainerDataSourceHandle UsdImagingGeomModelAPIAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfToken const &appliedInstanceName,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (!subprim.IsEmpty() || !appliedInstanceName.IsEmpty()) {
    return nullptr;
  }

  // Reflect UsdGeomModelAPI as UsdImagingGeomModelSchema.
  HdContainerDataSourceHandle geomModelDs = UsdImagingDataSourceMapped::New(
      prim, prim.GetPath(), _GetMappings(), stageGlobals);

  // For model components, overlay applyDrawMode=true.
  if (UsdModelAPI(prim).IsKind(KindTokens->component)) {
    static HdContainerDataSourceHandle const applyDrawModeDs =
        UsdImagingGeomModelSchema::Builder()
            .SetApplyDrawMode(HdRetainedTypedSampledDataSource<bool>::New(true))
            .Build();
    geomModelDs = HdOverlayContainerDataSource::OverlayedContainerDataSources(applyDrawModeDs,
                                                                              geomModelDs);
  }

  return HdRetainedContainerDataSource::New(UsdImagingGeomModelSchema::GetSchemaToken(),
                                            geomModelDs);
}

HdDataSourceLocatorSet UsdImagingGeomModelAPIAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfToken const &appliedInstanceName,
    TfTokenVector const &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  if (!subprim.IsEmpty() || !appliedInstanceName.IsEmpty()) {
    return HdDataSourceLocatorSet();
  }

  return UsdImagingDataSourceMapped::Invalidate(properties, _GetMappings());
}

PXR_NAMESPACE_CLOSE_SCOPE
