//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/root.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdSkelRoot, TfType::Bases<UsdGeomBoundable>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("SkelRoot")
  // to find TfType<UsdSkelRoot>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdSkelRoot>("SkelRoot");
}

/* virtual */
UsdSkelRoot::~UsdSkelRoot() {}

/* static */
UsdSkelRoot UsdSkelRoot::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdSkelRoot();
  }
  return UsdSkelRoot(stage->GetPrimAtPath(path));
}

/* static */
UsdSkelRoot UsdSkelRoot::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("SkelRoot");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdSkelRoot();
  }
  return UsdSkelRoot(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdSkelRoot::_GetSchemaKind() const
{
  return UsdSkelRoot::schemaKind;
}

/* static */
const TfType &UsdSkelRoot::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdSkelRoot>();
  return tfType;
}

/* static */
bool UsdSkelRoot::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdSkelRoot::_GetTfType() const
{
  return _GetStaticTfType();
}

/*static*/
const TfTokenVector &UsdSkelRoot::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames;
  static TfTokenVector allNames = UsdGeomBoundable::GetSchemaAttributeNames(true);

  if (includeInherited)
    return allNames;
  else
    return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

#include "Usd/primRange.h"
#include "UsdGeom/boundableComputeExtent.h"
#include "UsdGeom/xformCache.h"
#include "UsdSkel/binding.h"
#include "UsdSkel/cache.h"
#include "UsdSkel/skeleton.h"
#include "UsdSkel/skeletonQuery.h"
#include "UsdSkel/skinningQuery.h"
#include "UsdSkel/utils.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdSkelRoot UsdSkelRoot::Find(const UsdPrim &prim)
{
  for (UsdPrim p = prim; p; p = p.GetParent()) {
    if (p.IsA<UsdSkelRoot>()) {
      return UsdSkelRoot(p);
    }
  }
  return UsdSkelRoot();
}

/// Plugin extent method.
static bool _ComputeExtent(const UsdGeomBoundable &boundable,
                           const UsdTimeCode &time,
                           const GfMatrix4d *transform,
                           VtVec3fArray *extent)
{
  const UsdSkelRoot skelRoot(boundable);
  if (!TF_VERIFY(skelRoot)) {
    return false;
  }

  UsdSkelCache skelCache;
  skelCache.Populate(skelRoot, UsdTraverseInstanceProxies());

  UsdGeomXformCache xfCache;
  GfRange3d bbox;
  VtVec3fArray skelExtent;

  auto processSkeleton = [&](UsdSkelSkeleton const &skeleton,
                             UsdSkelBinding const &binding = UsdSkelBinding()) {
    UsdSkelSkeletonQuery skelQuery = skelCache.GetSkelQuery(skeleton);

    if (!TF_VERIFY(skelQuery)) {
      return false;
    }

    // Compute skel-space joint transforms.
    // The extent for this skel is based on the pivots of all bones,
    // with some additional padding.
    VtMatrix4dArray skelXforms;
    if (!skelQuery.ComputeJointSkelTransforms(&skelXforms, time)) {
      return true;
    }

    // Pre-compute a constant padding metric across all prims
    // skinned by this skeleton.
    float padding = 0;
    VtMatrix4dArray skelRestXforms;
    if (skelQuery.ComputeJointSkelTransforms(&skelRestXforms, time, /*atRest*/ true)) {

      for (const auto &skinningQuery : binding.GetSkinningTargets()) {

        const UsdPrim &skinnedPrim = skinningQuery.GetPrim();

        float skelPadding = skinningQuery.ComputeExtentsPadding(skelRestXforms,
                                                                UsdGeomBoundable(skinnedPrim));
        padding = (std::max)(padding, skelPadding);
      }
    }

    // Compute the final, padded extents from the skel-space
    // transforms, in the space of the SkelRoot prim.
    bool resetXformStack = false;
    GfMatrix4d skelRootXform = xfCache.ComputeRelativeTransform(
        skeleton.GetPrim(), skelRoot.GetPrim(), &resetXformStack);
    if (!resetXformStack && transform) {
      skelRootXform *= *transform;
    }
    UsdSkelComputeJointsExtent(skelXforms, &skelExtent, padding, &skelRootXform);

    for (const auto &p : skelExtent) {
      bbox.UnionWith(p);
    }

    return true;
  };

  std::vector<UsdSkelBinding> bindings;
  if (!skelCache.ComputeSkelBindings(skelRoot, &bindings, UsdTraverseInstanceProxies()) ||
      bindings.size() == 0)
  {

    // If we don't have any bindings, we visualize the skeletons themselves,
    // so simply traverse the subtree and process any descendant skeletons
    // to produce our extent.

    for (UsdPrim prim : UsdPrimRange(skelRoot.GetPrim(), UsdTraverseInstanceProxies())) {
      UsdSkelSkeleton skeleton(prim);
      if (skeleton) {
        if (!processSkeleton(skeleton)) {
          return false;
        }
      }
    }
  }
  else {
    // Normal case -- process all the bindings.
    for (const UsdSkelBinding &binding : bindings) {
      if (!processSkeleton(binding.GetSkeleton(), binding)) {
        return false;
      }
    }
  }

  extent->resize(2);
  (*extent)[0] = GfVec3f(bbox.GetMin());
  (*extent)[1] = GfVec3f(bbox.GetMax());

  return true;
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
  UsdGeomRegisterComputeExtentFunction<UsdSkelRoot>(_ComputeExtent);
}

PXR_NAMESPACE_CLOSE_SCOPE
