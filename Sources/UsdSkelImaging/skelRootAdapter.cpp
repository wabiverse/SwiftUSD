//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkelImaging/skelRootAdapter.h"
#include "UsdSkelImaging/skeletonAdapter.h"

#include "UsdImaging/debugCodes.h"
#include "UsdImaging/delegate.h"
#include "UsdImaging/gprimAdapter.h"
#include "UsdImaging/indexProxy.h"
#include "UsdImaging/tokens.h"

#include "Hd/perfLog.h"

#include "Usd/primRange.h"
#include "UsdGeom/boundable.h"
#include "UsdSkel/cache.h"
#include "UsdSkel/root.h"

#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdSkelImagingSkelRootAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

UsdSkelImagingSkelRootAdapter::~UsdSkelImagingSkelRootAdapter() = default;

bool UsdSkelImagingSkelRootAdapter::ShouldIgnoreNativeInstanceSubtrees() const
{
  // XXX: Neither bind-state instancing or instancing of skinned prims
  // is possible under the current architecture.
  // For now, we instead ignore instancing beneath SkelRoot prims.
  // This means we can benefit from native instancing for sharing parts
  // of the scene graph, while still allowing USD imaging to work.
  return true;
}

/*virtual*/
SdfPath UsdSkelImagingSkelRootAdapter::Populate(const UsdPrim &prim,
                                                UsdImagingIndexProxy *index,
                                                const UsdImagingInstancerContext *instancerContext)
{
  if (!TF_VERIFY(prim.IsA<UsdSkelRoot>())) {
    return {};
  }

  const auto predicate = UsdTraverseInstanceProxies(_GetDisplayPredicate());

  // Find skeletons and skinned prims under this skel root.
  UsdSkelRoot skelRoot(prim);
  UsdSkelCache skelCache;
  skelCache.Populate(skelRoot, predicate);

  std::vector<UsdSkelBinding> bindings;
  if (!skelCache.ComputeSkelBindings(skelRoot, &bindings, predicate)) {
    return {};
  }
  if (bindings.empty()) {
    return {};
  }

  // Use the skeleton adapter to inject hydra computation prims for each
  // target of a skeleton.
  for (const auto &binding : bindings) {
    const UsdSkelSkeleton &skel = binding.GetSkeleton();

    UsdImagingPrimAdapterSharedPtr adapter = _GetPrimAdapter(skel.GetPrim(),
                                                             /*ignoreInstancing*/ true);
    TF_VERIFY(adapter);

    auto skelAdapter = std::dynamic_pointer_cast<UsdSkelImagingSkeletonAdapter>(adapter);
    TF_VERIFY(skelAdapter);

    // Define a new binding that only contains skinnable prims
    // that have a bound prim adapter.
    VtArray<UsdSkelSkinningQuery> skinningQueries;
    skinningQueries.reserve(binding.GetSkinningTargets().size());

    for (const auto &skinningQuery : binding.GetSkinningTargets()) {

      if (!skinningQuery.HasBlendShapes() && !skinningQuery.HasJointInfluences()) {
        continue;
      }

      UsdPrim const &skinnedPrim = skinningQuery.GetPrim();

      // Register the SkeletonAdapter for each skinned prim, effectively
      // hijacking all processing to go via it.
      UsdImagingPrimAdapterSharedPtr skinnedPrimAdapter = _GetPrimAdapter(
          skinnedPrim, /*ignoreInstancing*/ true);
      if (!skinnedPrimAdapter) {
        // This prim is technically considered skinnable,
        // but an adapter may not be registered for the prim type.
        continue;
      }

      UsdImagingInstancerContext hijackContext;
      if (instancerContext) {
        hijackContext = *instancerContext;
      }
      hijackContext.instancerAdapter = skelAdapter;
      skinnedPrimAdapter->Populate(skinnedPrim, index, &hijackContext);

      skinningQueries.push_back(skinningQuery);
    }
    // We don't have a way to figure out all the skinned prims that are
    // bound to a skeleton when processing it (in the SkeletonAdapter).
    // We can do this with the SkelRoot and let the SkeletonAdapter know
    // about it.
    skelAdapter->RegisterSkelBinding(UsdSkelBinding(skel, skinningQueries));
  }

  return SdfPath();
}

/*virtual*/
void UsdSkelImagingSkelRootAdapter::TrackVariability(
    const UsdPrim &prim,
    const SdfPath &cachePath,
    HdDirtyBits *timeVaryingBits,
    const UsdImagingInstancerContext *instancerContext) const
{
  // The SkeletonAdapter is registered for skeletons and skinned prims, so
  // there's no work to be done here.
}

/*virtual*/
void UsdSkelImagingSkelRootAdapter::UpdateForTime(
    const UsdPrim &prim,
    const SdfPath &cachePath,
    UsdTimeCode time,
    HdDirtyBits requestedBits,
    const UsdImagingInstancerContext *instancerContext) const
{
  // The SkeletonAdapter is registered for skeletons and skinned prims, so
  // there's no work to be done here.
}

/*virtual*/
HdDirtyBits UsdSkelImagingSkelRootAdapter::ProcessPropertyChange(const UsdPrim &prim,
                                                                 const SdfPath &cachePath,
                                                                 const TfToken &propertyName)
{
  // The SkeletonAdapter is registered for skeletons and skinned prims, so
  // there's no work to be done here.
  // Note: Subtree visibility is handled by the delegate.
  return HdChangeTracker::Clean;
}

/*virtual*/
void UsdSkelImagingSkelRootAdapter::MarkDirty(const UsdPrim &prim,
                                              const SdfPath &cachePath,
                                              HdDirtyBits dirty,
                                              UsdImagingIndexProxy *index)
{
  // The SkeletonAdapter is registered for skeletons and skinned prims, so
  // there's no work to be done here.
}

/*virtual*/
void UsdSkelImagingSkelRootAdapter::_RemovePrim(const SdfPath &cachePath,
                                                UsdImagingIndexProxy *index)
{
  // The SkeletonAdapter is registered for skeletons and skinned prims, so
  // there's no work to be done here.
}

PXR_NAMESPACE_CLOSE_SCOPE
