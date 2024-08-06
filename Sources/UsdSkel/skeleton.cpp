//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/skeleton.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdSkelSkeleton, TfType::Bases<UsdGeomBoundable>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("Skeleton")
  // to find TfType<UsdSkelSkeleton>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdSkelSkeleton>("Skeleton");
}

/* virtual */
UsdSkelSkeleton::~UsdSkelSkeleton() {}

/* static */
UsdSkelSkeleton UsdSkelSkeleton::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdSkelSkeleton();
  }
  return UsdSkelSkeleton(stage->GetPrimAtPath(path));
}

/* static */
UsdSkelSkeleton UsdSkelSkeleton::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("Skeleton");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdSkelSkeleton();
  }
  return UsdSkelSkeleton(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdSkelSkeleton::_GetSchemaKind() const
{
  return UsdSkelSkeleton::schemaKind;
}

/* static */
const TfType &UsdSkelSkeleton::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdSkelSkeleton>();
  return tfType;
}

/* static */
bool UsdSkelSkeleton::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdSkelSkeleton::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdSkelSkeleton::GetJointsAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->joints);
}

UsdAttribute UsdSkelSkeleton::CreateJointsAttr(VtValue const &defaultValue,
                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->joints,
                                    SdfValueTypeNames->TokenArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelSkeleton::GetJointNamesAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->jointNames);
}

UsdAttribute UsdSkelSkeleton::CreateJointNamesAttr(VtValue const &defaultValue,
                                                   bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->jointNames,
                                    SdfValueTypeNames->TokenArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelSkeleton::GetBindTransformsAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->bindTransforms);
}

UsdAttribute UsdSkelSkeleton::CreateBindTransformsAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->bindTransforms,
                                    SdfValueTypeNames->Matrix4dArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelSkeleton::GetRestTransformsAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->restTransforms);
}

UsdAttribute UsdSkelSkeleton::CreateRestTransformsAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->restTransforms,
                                    SdfValueTypeNames->Matrix4dArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

namespace {
static inline TfTokenVector _ConcatenateAttributeNames(const TfTokenVector &left,
                                                       const TfTokenVector &right)
{
  TfTokenVector result;
  result.reserve(left.size() + right.size());
  result.insert(result.end(), left.begin(), left.end());
  result.insert(result.end(), right.begin(), right.end());
  return result;
}
}  // namespace

/*static*/
const TfTokenVector &UsdSkelSkeleton::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdSkelTokens->joints,
      UsdSkelTokens->jointNames,
      UsdSkelTokens->bindTransforms,
      UsdSkelTokens->restTransforms,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdGeomBoundable::GetSchemaAttributeNames(true), localNames);

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
#include "UsdSkel/cache.h"
#include "UsdSkel/skeletonQuery.h"
#include "UsdSkel/skinningQuery.h"
#include "UsdSkel/utils.h"

PXR_NAMESPACE_OPEN_SCOPE

/// Plugin extent method.
static bool _ComputeExtent(const UsdGeomBoundable &boundable,
                           const UsdTimeCode &time,
                           const GfMatrix4d *transform,
                           VtVec3fArray *extent)
{
  UsdSkelSkeleton skel(boundable);
  if (!TF_VERIFY(skel)) {
    return false;
  }

  UsdSkelCache skelCache;

  UsdSkelSkeletonQuery skelQuery = skelCache.GetSkelQuery(UsdSkelSkeleton(boundable.GetPrim()));

  if (TF_VERIFY(skelQuery)) {
    // Compute skel-space joint transforms.
    // The extent for this skel is based on the pivots of all joints.
    VtMatrix4dArray skelXforms;
    if (skelQuery.ComputeJointSkelTransforms(&skelXforms, time)) {
      return UsdSkelComputeJointsExtent(skelXforms,
                                        extent,
                                        /*padding*/ 0,
                                        transform);
    }
  }
  return true;
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
  UsdGeomRegisterComputeExtentFunction<UsdSkelSkeleton>(_ComputeExtent);
}

PXR_NAMESPACE_CLOSE_SCOPE
