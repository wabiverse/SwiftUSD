//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/nurbsCurvesAdapter.h"

#include "UsdImaging/dataSourceNurbsCurves.h"
#include "UsdImaging/delegate.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/primvarUtils.h"
#include "UsdImaging/tokens.h"

#include "Hd/basisCurves.h"
#include "Hd/perfLog.h"

#include "UsdGeom/nurbsCurves.h"
#include "UsdGeom/xformCache.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  typedef UsdImagingNurbsCurvesAdapter Adapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdImagingNurbsCurvesAdapter::~UsdImagingNurbsCurvesAdapter() = default;

bool UsdImagingNurbsCurvesAdapter::IsSupported(UsdImagingIndexProxy const *index) const
{
  return index->IsRprimTypeSupported(HdPrimTypeTokens->basisCurves);
}

SdfPath UsdImagingNurbsCurvesAdapter::Populate(UsdPrim const &prim,
                                               UsdImagingIndexProxy *index,
                                               UsdImagingInstancerContext const *instancerContext)
{
  return _AddRprim(
      HdPrimTypeTokens->basisCurves, prim, index, GetMaterialUsdPath(prim), instancerContext);
}

void UsdImagingNurbsCurvesAdapter::TrackVariability(
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

  // Discover time-varying topology.
  //
  // Do not check the time-varying NURBS curve attributes since we are
  // creating a Basis Curve and just drawing the linear segments between
  // the control points
  _IsVarying(prim,
             UsdGeomTokens->curveVertexCounts,
             HdChangeTracker::DirtyTopology,
             UsdImagingTokens->usdVaryingTopology,
             timeVaryingBits,
             /*isInherited*/ false);

  // Check for time-varying primvars:widths, and if that attribute
  // doesn't exist also check for time-varying widths.
  bool widthsExists = false;
  _IsVarying(prim,
             UsdImagingTokens->primvarsWidths,
             HdChangeTracker::DirtyWidths,
             UsdImagingTokens->usdVaryingWidths,
             timeVaryingBits,
             /*isInherited*/ false,
             &widthsExists);
  if (!widthsExists) {
    UsdGeomPrimvar pv = _GetInheritedPrimvar(prim, HdTokens->widths);
    if (pv && pv.ValueMightBeTimeVarying()) {
      *timeVaryingBits |= HdChangeTracker::DirtyWidths;
      HD_PERF_COUNTER_INCR(UsdImagingTokens->usdVaryingWidths);
      widthsExists = true;
    }
  }
  if (!widthsExists) {
    _IsVarying(prim,
               UsdGeomTokens->widths,
               HdChangeTracker::DirtyWidths,
               UsdImagingTokens->usdVaryingWidths,
               timeVaryingBits,
               /*isInherited*/ false);
  }

  // Check for time-varying primvars:normals, and if that attribute
  // doesn't exist also check for time-varying normals.
  bool normalsExists = false;
  _IsVarying(prim,
             UsdImagingTokens->primvarsNormals,
             HdChangeTracker::DirtyNormals,
             UsdImagingTokens->usdVaryingNormals,
             timeVaryingBits,
             /*isInherited*/ false,
             &normalsExists);
  if (!normalsExists) {
    UsdGeomPrimvar pv = _GetInheritedPrimvar(prim, HdTokens->normals);
    if (pv && pv.ValueMightBeTimeVarying()) {
      *timeVaryingBits |= HdChangeTracker::DirtyNormals;
      HD_PERF_COUNTER_INCR(UsdImagingTokens->usdVaryingNormals);
      normalsExists = true;
    }
  }
  if (!normalsExists) {
    _IsVarying(prim,
               UsdGeomTokens->normals,
               HdChangeTracker::DirtyNormals,
               UsdImagingTokens->usdVaryingNormals,
               timeVaryingBits,
               /*isInherited*/ false);
  }
}

bool UsdImagingNurbsCurvesAdapter::_IsBuiltinPrimvar(TfToken const &primvarName) const
{
  return (primvarName == HdTokens->normals || primvarName == HdTokens->widths) ||
         UsdImagingGprimAdapter::_IsBuiltinPrimvar(primvarName);
}

void UsdImagingNurbsCurvesAdapter::UpdateForTime(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    UsdTimeCode time,
    HdDirtyBits requestedBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  BaseAdapter::UpdateForTime(prim, cachePath, time, requestedBits, instancerContext);

  UsdImagingPrimvarDescCache *primvarDescCache = _GetPrimvarDescCache();
  HdPrimvarDescriptorVector &primvars = primvarDescCache->GetPrimvars(cachePath);

  if (requestedBits & HdChangeTracker::DirtyWidths) {
    // First check for "primvars:widths"
    UsdGeomPrimvarsAPI primvarsApi(prim);
    UsdGeomPrimvar pv = primvarsApi.GetPrimvar(UsdImagingTokens->primvarsWidths);
    if (!pv) {
      // If it's not found locally, see if it's inherited
      pv = _GetInheritedPrimvar(prim, HdTokens->widths);
    }

    if (pv) {
      _ComputeAndMergePrimvar(prim, pv, time, &primvars);
    }
    else {
      UsdGeomNurbsCurves curves(prim);
      HdInterpolation interpolation;
      VtFloatArray widths;
      if (curves.GetWidthsAttr().Get(&widths, time)) {
        interpolation = UsdImagingUsdToHdInterpolation(curves.GetWidthsInterpolation());
      }
      else {
        interpolation = HdInterpolationConstant;
      }
      _MergePrimvar(&primvars, UsdGeomTokens->widths, interpolation);
    }
  }

  if (requestedBits & HdChangeTracker::DirtyNormals) {
    // First check for "primvars:normals"
    UsdGeomPrimvarsAPI primvarsApi(prim);
    UsdGeomPrimvar pv = primvarsApi.GetPrimvar(UsdImagingTokens->primvarsNormals);
    if (!pv) {
      // If it's not found locally, see if it's inherited
      pv = _GetInheritedPrimvar(prim, HdTokens->normals);
    }

    if (pv) {
      _ComputeAndMergePrimvar(prim, pv, time, &primvars);
    }
    else {
      UsdGeomNurbsCurves curves(prim);
      VtVec3fArray normals;
      if (curves.GetNormalsAttr().Get(&normals, time)) {
        _MergePrimvar(&primvars,
                      UsdGeomTokens->normals,
                      UsdImagingUsdToHdInterpolation(curves.GetNormalsInterpolation()),
                      HdPrimvarRoleTokens->normal);
      }
      else {
        _RemovePrimvar(&primvars, UsdGeomTokens->normals);
      }
    }
  }
}

HdDirtyBits UsdImagingNurbsCurvesAdapter::ProcessPropertyChange(UsdPrim const &prim,
                                                                SdfPath const &cachePath,
                                                                TfToken const &propertyName)
{
  if (propertyName == UsdGeomTokens->points) {
    return HdChangeTracker::DirtyPoints;
  }
  else if (propertyName == UsdGeomTokens->curveVertexCounts) {
    return HdChangeTracker::DirtyTopology;
  }
  // Handle attributes that are treated as "built-in" primvars.
  else if (propertyName == UsdGeomTokens->widths) {
    UsdGeomCurves curves(prim);
    return UsdImagingPrimAdapter::_ProcessNonPrefixedPrimvarPropertyChange(
        prim,
        cachePath,
        propertyName,
        HdTokens->widths,
        UsdImagingUsdToHdInterpolation(curves.GetWidthsInterpolation()),
        HdChangeTracker::DirtyWidths);
  }
  else if (propertyName == UsdGeomTokens->normals) {
    UsdGeomPointBased pb(prim);
    return UsdImagingPrimAdapter::_ProcessNonPrefixedPrimvarPropertyChange(
        prim,
        cachePath,
        propertyName,
        HdTokens->normals,
        UsdImagingUsdToHdInterpolation(pb.GetNormalsInterpolation()),
        HdChangeTracker::DirtyNormals);
  }
  // Handle prefixed primvars that use special dirty bits.
  else if (propertyName == UsdImagingTokens->primvarsWidths) {
    return UsdImagingPrimAdapter::_ProcessPrefixedPrimvarPropertyChange(
        prim, cachePath, propertyName, HdChangeTracker::DirtyWidths);
  }
  else if (propertyName == UsdImagingTokens->primvarsNormals) {
    return UsdImagingPrimAdapter::_ProcessPrefixedPrimvarPropertyChange(
        prim, cachePath, propertyName, HdChangeTracker::DirtyNormals);
  }

  // Allow base class to handle change processing.
  return BaseAdapter::ProcessPropertyChange(prim, cachePath, propertyName);
}

/*virtual*/
VtValue UsdImagingNurbsCurvesAdapter::GetTopology(UsdPrim const &prim,
                                                  SdfPath const &cachePath,
                                                  UsdTimeCode time) const
{
  // Currently drawing the cage for NURBS curves so this creates
  // a Basis Curves Topology with the following parameters:
  //      linear, linear, and nonperiodic
  const TfToken &topoCurveBasis = HdTokens->linear;
  const TfToken &topoCurveType = HdTokens->linear;
  const TfToken &topoCurveWrap = HdTokens->nonperiodic;

  HdBasisCurvesTopology topology(topoCurveType,
                                 topoCurveBasis,
                                 topoCurveWrap,
                                 _Get<VtIntArray>(prim, UsdGeomTokens->curveVertexCounts, time),
                                 VtIntArray());
  return VtValue(topology);
}

/*virtual*/
VtValue UsdImagingNurbsCurvesAdapter::Get(UsdPrim const &prim,
                                          SdfPath const &cachePath,
                                          TfToken const &key,
                                          UsdTimeCode time,
                                          VtIntArray *outIndices) const
{
  TRACE_FUNCTION();
  HF_MALLOC_TAG_FUNCTION();

  if (key == HdTokens->normals) {
    // First check for "primvars:normals"
    UsdGeomPrimvarsAPI primvarsApi(prim);
    UsdGeomPrimvar pv = primvarsApi.GetPrimvar(UsdImagingTokens->primvarsNormals);
    if (!pv) {
      // If it's not found locally, see if it's inherited
      pv = _GetInheritedPrimvar(prim, HdTokens->normals);
    }

    VtValue value;

    if (outIndices) {
      if (pv && pv.Get(&value, time)) {
        pv.GetIndices(outIndices, time);
        return value;
      }
    }
    else if (pv && pv.ComputeFlattened(&value, time)) {
      return value;
    }

    // If there's no "primvars:normals",
    // fall back to UsdGeomNurbsCurves' "normals" attribute.
    UsdGeomNurbsCurves curves(prim);
    VtVec3fArray normals;
    if (curves && curves.GetNormalsAttr().Get(&normals, time)) {
      value = normals;
      return value;
    }
  }
  else if (key == HdTokens->widths) {
    // First check for "primvars:widths"
    UsdGeomPrimvarsAPI primvarsApi(prim);
    UsdGeomPrimvar pv = primvarsApi.GetPrimvar(UsdImagingTokens->primvarsWidths);
    if (!pv) {
      // If it's not found locally, see if it's inherited
      pv = _GetInheritedPrimvar(prim, HdTokens->widths);
    }

    VtValue value;

    if (outIndices) {
      if (pv && pv.Get(&value, time)) {
        pv.GetIndices(outIndices, time);
        return value;
      }
    }
    else if (pv && pv.ComputeFlattened(&value, time)) {
      return value;
    }

    // Fall back to UsdGeomNurbsCurves' "normals" attribute.
    UsdGeomNurbsCurves curves(prim);
    VtFloatArray widths;
    if (curves && curves.GetWidthsAttr().Get(&widths, time)) {
      value = widths;
      return value;
    }
  }

  return BaseAdapter::Get(prim, cachePath, key, time, outIndices);
}

TfTokenVector UsdImagingNurbsCurvesAdapter::GetImagingSubprims(UsdPrim const &prim)
{
  return {TfToken()};
}

TfToken UsdImagingNurbsCurvesAdapter::GetImagingSubprimType(UsdPrim const &prim,
                                                            TfToken const &subprim)
{
  if (subprim.IsEmpty()) {
    return HdPrimTypeTokens->nurbsCurves;
  }
  return TfToken();
}

HdContainerDataSourceHandle UsdImagingNurbsCurvesAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (subprim.IsEmpty()) {
    return UsdImagingDataSourceNurbsCurvesPrim::New(prim.GetPath(), prim, stageGlobals);
  }
  return nullptr;
}

HdDataSourceLocatorSet UsdImagingNurbsCurvesAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfTokenVector const &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  if (subprim.IsEmpty()) {
    return UsdImagingDataSourceNurbsCurvesPrim::Invalidate(
        prim, subprim, properties, invalidationType);
  }

  return HdDataSourceLocatorSet();
}

PXR_NAMESPACE_CLOSE_SCOPE
