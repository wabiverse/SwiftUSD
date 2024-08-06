//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdProcImaging/generativeProceduralAdapter.h"
#include "UsdImaging/tokens.h"

#include "UsdProc/generativeProcedural.h"

#include "UsdImaging/dataSourcePrim.h"
#include "UsdImaging/gprimAdapter.h"
#include "UsdImaging/indexProxy.h"

#include "UsdImaging/tokens.h"

#include "Hd/primvarSchema.h"
#include "Hd/primvarsSchema.h"

#include "Usd/prim.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens, (inertGenerativeProcedural));

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdProcImagingGenerativeProceduralAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

// ----------------------------------------------------------------------------
// Scene index classes and methods
// ----------------------------------------------------------------------------

TfTokenVector UsdProcImagingGenerativeProceduralAdapter::GetImagingSubprims(UsdPrim const &prim)
{
  return {TfToken()};
}

TfToken UsdProcImagingGenerativeProceduralAdapter::GetImagingSubprimType(UsdPrim const &prim,
                                                                         TfToken const &subprim)
{
  if (subprim.IsEmpty()) {
    return _GetHydraPrimType(prim);
  }

  return TfToken();
}

HdContainerDataSourceHandle UsdProcImagingGenerativeProceduralAdapter::GetImagingSubprimData(
    UsdPrim const &prim,
    TfToken const &subprim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (subprim.IsEmpty()) {
    // return _PrimDataSource::New(
    return UsdImagingDataSourcePrim::New(prim.GetPath(), prim, stageGlobals);
  }
  return nullptr;
}

HdDataSourceLocatorSet UsdProcImagingGenerativeProceduralAdapter::InvalidateImagingSubprim(
    UsdPrim const &prim,
    TfToken const &subprim,
    TfTokenVector const &properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
  if (subprim.IsEmpty()) {
    for (const TfToken &name : properties) {
      if (name == UsdProcTokens->proceduralSystem) {
        // Return the locator convention which indicates that stage
        // scene index should do the equivalent of resync.
        return HdDataSourceLocatorSet(
            HdDataSourceLocator(UsdImagingTokens->stageSceneIndexRepopulate));
      }
    }

    HdDataSourceLocatorSet result = UsdImagingDataSourcePrim::Invalidate(
        prim, subprim, properties, invalidationType);

    return result;
  }

  return HdDataSourceLocatorSet();
}

// ----------------------------------------------------------------------------

SdfPath UsdProcImagingGenerativeProceduralAdapter::Populate(
    UsdPrim const &prim,
    UsdImagingIndexProxy *index,
    UsdImagingInstancerContext const *instancerContext)
{
  const SdfPath cachePath = ResolveCachePath(prim.GetPath(), instancerContext);
  UsdPrim proxyPrim = _GetPrim(ResolveProxyPrimPath(cachePath, instancerContext));

  index->InsertRprim(_GetHydraPrimType(prim),
                     cachePath,
                     proxyPrim,
                     instancerContext ? instancerContext->instancerAdapter :
                                        UsdImagingPrimAdapterSharedPtr());
  index->InsertRprim(_GetHydraPrimType(prim), prim.GetPath(), prim);
  return cachePath;
}

bool UsdProcImagingGenerativeProceduralAdapter::IsSupported(
    UsdImagingIndexProxy const *index) const
{
  return true;
}

void UsdProcImagingGenerativeProceduralAdapter::UpdateForTime(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    UsdTimeCode time,
    HdDirtyBits requestedBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  UsdImagingPrimvarDescCache *primvarDescCache = _GetPrimvarDescCache();
  HdPrimvarDescriptorVector &vPrimvars = primvarDescCache->GetPrimvars(cachePath);

  if (requestedBits & HdChangeTracker::DirtyPrimvar) {
    std::vector<UsdGeomPrimvar> primvars;

    UsdImaging_InheritedPrimvarStrategy::value_type inheritedPrimvarRecord = _GetInheritedPrimvars(
        prim.GetParent());
    if (inheritedPrimvarRecord) {
      primvars = inheritedPrimvarRecord->primvars;
    }

    UsdGeomPrimvarsAPI primvarsAPI(prim);
    std::vector<UsdGeomPrimvar> local = primvarsAPI.GetPrimvarsWithValues();
    primvars.insert(primvars.end(), local.begin(), local.end());

    for (auto const &pv : primvars) {
      _ComputeAndMergePrimvar(prim, pv, time, &vPrimvars);
    }

    for (UsdProperty prop : prim.GetAuthoredPropertiesInNamespace("primvars:")) {
      if (UsdRelationship rel = prop.As<UsdRelationship>()) {

        _MergePrimvar(
            &vPrimvars, rel.GetBaseName(), HdInterpolationConstant, HdPrimvarRoleTokens->none);
      }
    }
  }
}

VtValue UsdProcImagingGenerativeProceduralAdapter::Get(UsdPrim const &prim,
                                                       SdfPath const &cachePath,
                                                       TfToken const &key,
                                                       UsdTimeCode time,
                                                       VtIntArray *outIndices) const
{
  VtValue value;
  if (UsdGeomPrimvar pv = UsdGeomPrimvarsAPI(prim).GetPrimvar(key)) {

    if (outIndices) {
      if (pv && pv.Get(&value, time)) {
        pv.GetIndices(outIndices, time);
        return value;
      }
    }
    else if (pv && pv.ComputeFlattened(&value, time)) {
      return value;
    }
  }
  else if (UsdGeomPrimvar pv = _GetInheritedPrimvar(prim, key)) {
    if (outIndices) {
      if (pv && pv.Get(&value, time)) {
        pv.GetIndices(outIndices, time);
        return value;
      }
    }
    else if (pv && pv.ComputeFlattened(&value, time)) {
      return value;
    }
  }

  // no primvar result? Try for a primvar relationship
  TfToken prefixedName(("primvars:" + key.GetString()).c_str());
  if (UsdRelationship rel = prim.GetRelationship(prefixedName)) {
    SdfPathVector targets;
    rel.GetTargets(&targets);

    return VtValue(VtArray<SdfPath>(targets.begin(), targets.end()));
  }

  return value;
}

HdDirtyBits UsdProcImagingGenerativeProceduralAdapter::ProcessPropertyChange(
    UsdPrim const &prim, SdfPath const &cachePath, TfToken const &propertyName)
{
  // if "proceduralSystem" changes, our hydra type will change and we
  // indicate that via AllDirty
  if (propertyName == UsdProcTokens->proceduralSystem) {
    return HdChangeTracker::AllDirty;
  }

  HdDirtyBits result = HdChangeTracker::Clean;

  if (UsdGeomPrimvarsAPI::CanContainPropertyName(propertyName)) {
    result |= HdChangeTracker::DirtyPrimvar;
  }

  return result;
}

void UsdProcImagingGenerativeProceduralAdapter::_RemovePrim(SdfPath const &cachePath,
                                                            UsdImagingIndexProxy *index)
{
  index->RemoveRprim(cachePath);
}

void UsdProcImagingGenerativeProceduralAdapter::TrackVariability(
    UsdPrim const &prim,
    SdfPath const &cachePath,
    HdDirtyBits *timeVaryingBits,
    UsdImagingInstancerContext const *instancerContext) const
{
  // XXX copied/pared from UsdImagingGprimAdapter
  if (!(*timeVaryingBits & HdChangeTracker::DirtyPrimvar)) {
    // See if any local primvars are time-dependent.
    UsdGeomPrimvarsAPI primvarsAPI(prim);
    std::vector<UsdGeomPrimvar> primvars = primvarsAPI.GetPrimvarsWithValues();
    for (UsdGeomPrimvar const &pv : primvars) {
      if (pv.ValueMightBeTimeVarying()) {
        *timeVaryingBits |= HdChangeTracker::DirtyPrimvar;
        HD_PERF_COUNTER_INCR(UsdImagingTokens->usdVaryingPrimvar);
        break;
      }
    }
  }

  // Discover time-varying extent.
  _IsVarying(prim,
             UsdGeomTokens->extent,
             HdChangeTracker::DirtyExtent,
             UsdImagingTokens->usdVaryingExtent,
             timeVaryingBits,
             false);

  // Discover time-varying transforms.
  _IsTransformVarying(
      prim, HdChangeTracker::DirtyTransform, UsdImagingTokens->usdVaryingXform, timeVaryingBits);

  // Discover time-varying visibility.
  _IsVarying(prim,
             UsdGeomTokens->visibility,
             HdChangeTracker::DirtyVisibility,
             UsdImagingTokens->usdVaryingVisibility,
             timeVaryingBits,
             true);
}

void UsdProcImagingGenerativeProceduralAdapter::MarkDirty(UsdPrim const &prim,
                                                          SdfPath const &cachePath,
                                                          HdDirtyBits dirty,
                                                          UsdImagingIndexProxy *index)
{
  index->MarkRprimDirty(cachePath, dirty);

  // On DirtyPrimvar, we need to re-run UpdateForTime to check for new
  // primvars that may have been added by an edit.
  if (dirty & HdChangeTracker::DirtyPrimvar) {
    index->RequestUpdateForTime(cachePath);
  }
}

void UsdProcImagingGenerativeProceduralAdapter::MarkTransformDirty(UsdPrim const &prim,
                                                                   SdfPath const &cachePath,
                                                                   UsdImagingIndexProxy *index)
{
  index->MarkRprimDirty(cachePath, HdChangeTracker::DirtyTransform);
}

void UsdProcImagingGenerativeProceduralAdapter::MarkVisibilityDirty(UsdPrim const &prim,
                                                                    SdfPath const &cachePath,
                                                                    UsdImagingIndexProxy *index)
{
  index->MarkRprimDirty(cachePath, HdChangeTracker::DirtyVisibility);
}

TfToken UsdProcImagingGenerativeProceduralAdapter::_GetHydraPrimType(UsdPrim const &prim)
{
  TfToken rprimType;
  UsdProcGenerativeProcedural genProc(prim);

  VtValue procSysValue;

  if (UsdAttribute procSysAttr = genProc.GetProceduralSystemAttr()) {
    procSysAttr.Get(&procSysValue);
  }

  if (procSysValue.IsHolding<TfToken>()) {
    rprimType = procSysValue.UncheckedGet<TfToken>();
  }

  if (rprimType.IsEmpty()) {
    rprimType = _tokens->inertGenerativeProcedural;
  }

  return rprimType;
}

PXR_NAMESPACE_CLOSE_SCOPE
