//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/geometryLightAdapter.h"
#include "UsdImaging/delegate.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/tokens.h"

#include "Hd/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  typedef UsdImagingGeometryLightAdapter Adapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdImagingGeometryLightAdapter::~UsdImagingGeometryLightAdapter() {}

bool UsdImagingGeometryLightAdapter::IsSupported(UsdImagingIndexProxy const *index) const
{
  return false;
}

SdfPath UsdImagingGeometryLightAdapter::Populate(
    UsdPrim const &prim,
    UsdImagingIndexProxy *index,
    UsdImagingInstancerContext const *instancerContext)
{
  TF_CODING_ERROR("Geometry lights are not yet supported in USD imaging");
  return prim.GetPath();
}

void UsdImagingGeometryLightAdapter::_RemovePrim(SdfPath const &cachePath,
                                                 UsdImagingIndexProxy *index)
{
  TF_CODING_ERROR("Geometry lights are not yet supported in USD imaging");
}

PXR_NAMESPACE_CLOSE_SCOPE
