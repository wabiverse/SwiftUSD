//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/coordSysAPIAdapter.h"

#include "Hd/coordSysBindingSchema.h"
#include "Hd/coordSysSchema.h"
#include "Hd/dependenciesSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/tokens.h"
#include "Hd/xformSchema.h"
#include "UsdImaging/dataSourcePrim.h"
#include "UsdShade/coordSysAPI.h"

#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdImagingCoordSysAPIAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingAPISchemaAdapterFactory<Adapter>>();
}

// ----------------------------------------------------------------------------

HdContainerDataSourceHandle UsdImagingCoordSysAPIAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfToken const &appliedInstanceName,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (appliedInstanceName.IsEmpty()) {
    return nullptr;
  }

  if (subprim.IsEmpty()) {
    UsdShadeCoordSysAPI::Binding binding =
        UsdShadeCoordSysAPI(prim, appliedInstanceName).GetLocalBinding();
    if (binding.name.IsEmpty()) {
      return nullptr;
    }

    return HdRetainedContainerDataSource::New(
        HdCoordSysBindingSchemaTokens->coordSysBinding,
        HdRetainedContainerDataSource::New(
            appliedInstanceName,
            HdRetainedTypedSampledDataSource<SdfPath>::New(binding.coordSysPrimPath)));
  }

  return nullptr;
}

HdDataSourceLocatorSet UsdImagingCoordSysAPIAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfToken const &appliedInstanceName,
    TfTokenVector const &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  if (appliedInstanceName.IsEmpty()) {
    return HdDataSourceLocatorSet();
  }

  if (subprim.IsEmpty()) {
    for (const TfToken &propertyName : properties) {
      // Could use coord sys name for more targeted invalidation
      // to improve performance.
      if (UsdShadeCoordSysAPI::CanContainPropertyName(propertyName)) {
        return HdCoordSysBindingSchema::GetDefaultLocator();
      }
    }
  }

  return HdDataSourceLocatorSet();
}

PXR_NAMESPACE_CLOSE_SCOPE
