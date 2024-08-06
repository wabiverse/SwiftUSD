//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
#include "UsdImaging/tetMeshAdapter.h"

#include "UsdImaging/dataSourceTetMesh.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/tokens.h"

#include "Hd/mesh.h"
#include "Hd/tokens.h"

#include "PxOsd/meshTopology.h"
#include "PxOsd/tokens.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdImagingTetMeshAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdImagingTetMeshAdapter::~UsdImagingTetMeshAdapter() = default;

TfTokenVector UsdImagingTetMeshAdapter::GetImagingSubprims(UsdPrim const &prim)
{
  return {TfToken()};
}

TfToken UsdImagingTetMeshAdapter::GetImagingSubprimType(UsdPrim const &prim,
                                                        TfToken const &subprim)
{
  if (subprim.IsEmpty()) {
    return HdPrimTypeTokens->tetMesh;
  }
  return TfToken();
}

HdContainerDataSourceHandle UsdImagingTetMeshAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (subprim.IsEmpty()) {
    return UsdImagingDataSourceTetMeshPrim::New(prim.GetPath(), prim, stageGlobals);
  }
  return nullptr;
}

HdDataSourceLocatorSet UsdImagingTetMeshAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfTokenVector const &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  return UsdImagingDataSourceTetMeshPrim::Invalidate(prim, subprim, properties, invalidationType);
}

SdfPath UsdImagingTetMeshAdapter::Populate(UsdPrim const &prim,
                                           UsdImagingIndexProxy *index,
                                           UsdImagingInstancerContext const *instancerContext)
{
  return _AddRprim(
      HdPrimTypeTokens->mesh, prim, index, GetMaterialUsdPath(prim), instancerContext);
}

bool UsdImagingTetMeshAdapter::IsSupported(UsdImagingIndexProxy const *index) const
{
  return index->IsRprimTypeSupported(HdPrimTypeTokens->mesh);
}

void UsdImagingTetMeshAdapter::TrackVariability(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    HdDirtyBits *timeVaryingBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  BaseAdapter::TrackVariability(prim, cachePath, timeVaryingBits, instancerContext);

  // Discover time-varying points.
  _IsVarying(prim,
             UsdGeomTokens->points,
             HdChangeTracker::DirtyPoints,
             UsdImagingTokens->usdVaryingPrimvar,
             timeVaryingBits,
             /*isInherited*/ false);

  _IsVarying(prim,
             UsdGeomTokens->tetVertexIndices,
             HdChangeTracker::DirtyTopology,
             UsdImagingTokens->usdVaryingTopology,
             timeVaryingBits,
             /*isInherited*/ false);
}

HdDirtyBits UsdImagingTetMeshAdapter::ProcessPropertyChange(UsdPrim const &prim,
                                                            SdfPath const &cachePath,
                                                            TfToken const &propertyName)
{
  if (propertyName == UsdGeomTokens->points)
    return HdChangeTracker::DirtyPoints;

  if (propertyName == UsdGeomTokens->tetVertexIndices ||
      propertyName == UsdGeomTokens->orientation)
  {
    return HdChangeTracker::DirtyTopology;
  }

  // Allow base class to handle change processing.
  return BaseAdapter::ProcessPropertyChange(prim, cachePath, propertyName);
}
/*virtual*/
VtValue UsdImagingTetMeshAdapter::GetTopology(UsdPrim const &prim,
                                              SdfPath const &cachePath,
                                              UsdTimeCode time) const
{
  TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();

  // Get the surfaceFaceIndices attribute for the Tet Mesh
  const UsdAttribute &surfaceFaceVertexIndicesAttr =
      UsdGeomTetMesh(prim).GetSurfaceFaceVertexIndicesAttr();
  VtVec3iArray surfaceFaceIndices;
  surfaceFaceVertexIndicesAttr.Get(&surfaceFaceIndices, time);

  // Compute faceVertexIndices and faceVertexCounts for the HdMeshTopology
  const size_t numCounts = surfaceFaceIndices.size();
  VtIntArray faceVertexIndices;
  VtIntArray faceVertexCounts(numCounts);
  for (size_t i = 0; i < numCounts; ++i) {
    faceVertexIndices.push_back(surfaceFaceIndices[i][0]);
    faceVertexIndices.push_back(surfaceFaceIndices[i][1]);
    faceVertexIndices.push_back(surfaceFaceIndices[i][2]);
    faceVertexCounts[i] = 3;
  }

  // Create and return the HdMeshTopology
  HdMeshTopology tetMeshTopology(PxOsdOpenSubdivTokens->catmullClark,
                                 _Get<TfToken>(prim, UsdGeomTokens->orientation, time),
                                 faceVertexCounts,
                                 faceVertexIndices);

  return VtValue(tetMeshTopology);
}

PXR_NAMESPACE_CLOSE_SCOPE
