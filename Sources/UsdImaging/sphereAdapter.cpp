//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/sphereAdapter.h"

#include "UsdImaging/dataSourceImplicits-Impl.h"
#include "UsdImaging/delegate.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/tokens.h"

#include "GeomUtil/sphereMeshGenerator.h"
#include "Hd/mesh.h"
#include "Hd/meshTopology.h"
#include "Hd/perfLog.h"
#include "Hd/sphereSchema.h"
#include "Hd/tokens.h"

#include "UsdGeom/sphere.h"
#include "UsdGeom/xformCache.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {
using _PrimSource = UsdImagingDataSourceImplicitsPrim<UsdGeomSphere, HdSphereSchema>;
}

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdImagingSphereAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdImagingSphereAdapter::~UsdImagingSphereAdapter() = default;

TfTokenVector UsdImagingSphereAdapter::GetImagingSubprims(UsdPrim const &prim)
{
  return {TfToken()};
}

TfToken UsdImagingSphereAdapter::GetImagingSubprimType(UsdPrim const &prim, TfToken const &subprim)
{
  if (subprim.IsEmpty()) {
    return HdPrimTypeTokens->sphere;
  }
  return TfToken();
}

HdContainerDataSourceHandle UsdImagingSphereAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (subprim.IsEmpty()) {
    return _PrimSource::New(prim.GetPath(), prim, stageGlobals);
  }
  return nullptr;
}

HdDataSourceLocatorSet UsdImagingSphereAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfTokenVector const &properties,
    UsdImagingPropertyInvalidationType invalidationType)
{
  if (subprim.IsEmpty()) {
    return _PrimSource::Invalidate(prim, subprim, properties, invalidationType);
  }

  return HdDataSourceLocatorSet();
}

bool UsdImagingSphereAdapter::IsSupported(UsdImagingIndexProxy const *index) const
{
  return index->IsRprimTypeSupported(HdPrimTypeTokens->mesh);
}

SdfPath UsdImagingSphereAdapter::Populate(UsdPrim const &prim,
                                          UsdImagingIndexProxy *index,
                                          UsdImagingInstancerContext const *instancerContext)
{
  return _AddRprim(
      HdPrimTypeTokens->mesh, prim, index, GetMaterialUsdPath(prim), instancerContext);
}

void UsdImagingSphereAdapter::TrackVariability(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    HdDirtyBits *timeVaryingBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  BaseAdapter::TrackVariability(prim, cachePath, timeVaryingBits, instancerContext);

  // Check DirtyPoints before doing variability checks, to see if we can skip.
  if ((*timeVaryingBits & HdChangeTracker::DirtyPoints) == 0) {
    _IsVarying(prim,
               UsdGeomTokens->radius,
               HdChangeTracker::DirtyPoints,
               UsdImagingTokens->usdVaryingPrimvar,
               timeVaryingBits,
               /*inherited*/ false);
  }
}

HdDirtyBits UsdImagingSphereAdapter::ProcessPropertyChange(UsdPrim const &prim,
                                                           SdfPath const &cachePath,
                                                           TfToken const &propertyName)
{
  if (propertyName == UsdGeomTokens->radius) {
    return HdChangeTracker::DirtyPoints;
  }

  // Allow base class to handle change processing.
  return BaseAdapter::ProcessPropertyChange(prim, cachePath, propertyName);
}

/*virtual*/
VtValue UsdImagingSphereAdapter::GetPoints(UsdPrim const &prim, UsdTimeCode time) const
{
  UsdGeomSphere sphere(prim);
  double radius = 1.0;
  if (!sphere.GetRadiusAttr().Get(&radius, time)) {
    TF_WARN("Could not evaluate double-valued radius attribute on prim %s",
            prim.GetPath().GetText());
  }

  const size_t numPoints = GeomUtilSphereMeshGenerator::ComputeNumPoints(numRadial, numAxial);

  VtVec3fArray points(numPoints);

  GeomUtilSphereMeshGenerator::GeneratePoints(points.begin(), numRadial, numAxial, radius);

  return VtValue(points);
}

/*virtual*/
VtValue UsdImagingSphereAdapter::GetTopology(UsdPrim const &prim,
                                             SdfPath const &cachePath,
                                             UsdTimeCode time) const
{
  TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();

  // All spheres share the same topology.
  static const HdMeshTopology topology = HdMeshTopology(
      GeomUtilSphereMeshGenerator::GenerateTopology(numRadial, numAxial));

  return VtValue(topology);
}

PXR_NAMESPACE_CLOSE_SCOPE
