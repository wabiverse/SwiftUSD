//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/planeAdapter.h"

#include "UsdImaging/delegate.h"
#include "UsdImaging/implicitSurfaceMeshUtils.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/tokens.h"

#include "Hd/mesh.h"
#include "Hd/meshTopology.h"
#include "Hd/perfLog.h"
#include "Hd/tokens.h"

#include "UsdGeom/plane.h"
#include "UsdGeom/xformCache.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  typedef UsdImagingPlaneAdapter Adapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdImagingPlaneAdapter::~UsdImagingPlaneAdapter() {}

bool UsdImagingPlaneAdapter::IsSupported(UsdImagingIndexProxy const *index) const
{
  return index->IsRprimTypeSupported(HdPrimTypeTokens->mesh);
}

SdfPath UsdImagingPlaneAdapter::Populate(UsdPrim const &prim,
                                         UsdImagingIndexProxy *index,
                                         UsdImagingInstancerContext const *instancerContext)
{
  return _AddRprim(
      HdPrimTypeTokens->mesh, prim, index, GetMaterialUsdPath(prim), instancerContext);
}

void UsdImagingPlaneAdapter::TrackVariability(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    HdDirtyBits *timeVaryingBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  BaseAdapter::TrackVariability(prim, cachePath, timeVaryingBits, instancerContext);

  // Check DirtyPoints before doing variability checks, in case we can skip
  // any of them...
  if ((*timeVaryingBits & HdChangeTracker::DirtyPoints) == 0) {
    _IsVarying(prim,
               UsdGeomTokens->width,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               timeVaryingBits,
               /*inherited*/ false);
  }
  if ((*timeVaryingBits & HdChangeTracker::DirtyPoints) == 0) {
    _IsVarying(prim,
               UsdGeomTokens->length,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               timeVaryingBits,
               /*inherited*/ false);
  }
  if ((*timeVaryingBits & HdChangeTracker::DirtyPoints) == 0) {
    _IsVarying(prim,
               UsdGeomTokens->axis,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               timeVaryingBits,
               /*inherited*/ false);
  }
}

HdDirtyBits UsdImagingPlaneAdapter::ProcessPropertyChange(UsdPrim const &prim,
                                                          SdfPath const &cachePath,
                                                          TfToken const &propertyName)
{
  if (propertyName == UsdGeomTokens->width || propertyName == UsdGeomTokens->length ||
      propertyName == UsdGeomTokens->axis)
  {
    return HdChangeTracker::DirtyPoints;
  }

  // Allow base class to handle change processing.
  return BaseAdapter::ProcessPropertyChange(prim, cachePath, propertyName);
}

/*virtual*/
VtValue UsdImagingPlaneAdapter::GetPoints(UsdPrim const &prim, UsdTimeCode time) const
{
  return GetMeshPoints(prim, time);
}

/*static*/
VtValue UsdImagingPlaneAdapter::GetMeshPoints(UsdPrim const &prim, UsdTimeCode time)
{
  UsdGeomPlane plane(prim);
  double width = 2.0;
  double length = 2.0;
  TfToken axis = UsdGeomTokens->z;
  TF_VERIFY(plane.GetWidthAttr().Get(&width, time));
  TF_VERIFY(plane.GetLengthAttr().Get(&length, time));
  TF_VERIFY(plane.GetAxisAttr().Get(&axis, time));

  return VtValue(UsdImagingGeneratePlaneMeshPoints(width, length, axis));
}

/*static*/
VtValue UsdImagingPlaneAdapter::GetMeshTopology()
{
  // Topology is constant and identical for all planes.
  return VtValue(HdMeshTopology(UsdImagingGetPlaneTopology()));
}

/*virtual*/
VtValue UsdImagingPlaneAdapter::GetTopology(UsdPrim const &prim,
                                            SdfPath const &cachePath,
                                            UsdTimeCode time) const
{
  TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();
  return GetMeshTopology();
}

PXR_NAMESPACE_CLOSE_SCOPE
