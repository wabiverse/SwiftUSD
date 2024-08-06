//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/bindingAPI.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdSkelBindingAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdSkelBindingAPI::~UsdSkelBindingAPI() {}

/* static */
UsdSkelBindingAPI UsdSkelBindingAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdSkelBindingAPI();
  }
  return UsdSkelBindingAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdSkelBindingAPI::_GetSchemaKind() const
{
  return UsdSkelBindingAPI::schemaKind;
}

/* static */
bool UsdSkelBindingAPI::CanApply(const UsdPrim &prim, std::string *whyNot)
{
  return prim.CanApplyAPI<UsdSkelBindingAPI>(whyNot);
}

/* static */
UsdSkelBindingAPI UsdSkelBindingAPI::Apply(const UsdPrim &prim)
{
  if (prim.ApplyAPI<UsdSkelBindingAPI>()) {
    return UsdSkelBindingAPI(prim);
  }
  return UsdSkelBindingAPI();
}

/* static */
const TfType &UsdSkelBindingAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdSkelBindingAPI>();
  return tfType;
}

/* static */
bool UsdSkelBindingAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdSkelBindingAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdSkelBindingAPI::GetSkinningMethodAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->primvarsSkelSkinningMethod);
}

UsdAttribute UsdSkelBindingAPI::CreateSkinningMethodAttr(VtValue const &defaultValue,
                                                         bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->primvarsSkelSkinningMethod,
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelBindingAPI::GetGeomBindTransformAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->primvarsSkelGeomBindTransform);
}

UsdAttribute UsdSkelBindingAPI::CreateGeomBindTransformAttr(VtValue const &defaultValue,
                                                            bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->primvarsSkelGeomBindTransform,
                                    SdfValueTypeNames->Matrix4d,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelBindingAPI::GetJointsAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->skelJoints);
}

UsdAttribute UsdSkelBindingAPI::CreateJointsAttr(VtValue const &defaultValue,
                                                 bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->skelJoints,
                                    SdfValueTypeNames->TokenArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelBindingAPI::GetJointIndicesAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->primvarsSkelJointIndices);
}

UsdAttribute UsdSkelBindingAPI::CreateJointIndicesAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->primvarsSkelJointIndices,
                                    SdfValueTypeNames->IntArray,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelBindingAPI::GetJointWeightsAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->primvarsSkelJointWeights);
}

UsdAttribute UsdSkelBindingAPI::CreateJointWeightsAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->primvarsSkelJointWeights,
                                    SdfValueTypeNames->FloatArray,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdSkelBindingAPI::GetBlendShapesAttr() const
{
  return GetPrim().GetAttribute(UsdSkelTokens->skelBlendShapes);
}

UsdAttribute UsdSkelBindingAPI::CreateBlendShapesAttr(VtValue const &defaultValue,
                                                      bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdSkelTokens->skelBlendShapes,
                                    SdfValueTypeNames->TokenArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdRelationship UsdSkelBindingAPI::GetAnimationSourceRel() const
{
  return GetPrim().GetRelationship(UsdSkelTokens->skelAnimationSource);
}

UsdRelationship UsdSkelBindingAPI::CreateAnimationSourceRel() const
{
  return GetPrim().CreateRelationship(UsdSkelTokens->skelAnimationSource,
                                      /* custom = */ false);
}

UsdRelationship UsdSkelBindingAPI::GetSkeletonRel() const
{
  return GetPrim().GetRelationship(UsdSkelTokens->skelSkeleton);
}

UsdRelationship UsdSkelBindingAPI::CreateSkeletonRel() const
{
  return GetPrim().CreateRelationship(UsdSkelTokens->skelSkeleton,
                                      /* custom = */ false);
}

UsdRelationship UsdSkelBindingAPI::GetBlendShapeTargetsRel() const
{
  return GetPrim().GetRelationship(UsdSkelTokens->skelBlendShapeTargets);
}

UsdRelationship UsdSkelBindingAPI::CreateBlendShapeTargetsRel() const
{
  return GetPrim().CreateRelationship(UsdSkelTokens->skelBlendShapeTargets,
                                      /* custom = */ false);
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
const TfTokenVector &UsdSkelBindingAPI::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdSkelTokens->primvarsSkelSkinningMethod,
      UsdSkelTokens->primvarsSkelGeomBindTransform,
      UsdSkelTokens->skelJoints,
      UsdSkelTokens->primvarsSkelJointIndices,
      UsdSkelTokens->primvarsSkelJointWeights,
      UsdSkelTokens->skelBlendShapes,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdAPISchemaBase::GetSchemaAttributeNames(true), localNames);

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

#include "UsdGeom/boundable.h"
#include "UsdGeom/primvarsAPI.h"
#include "UsdGeom/tokens.h"

#include "UsdSkel/skeleton.h"
#include "UsdSkel/utils.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdGeomPrimvar UsdSkelBindingAPI::GetJointIndicesPrimvar() const
{
  return UsdGeomPrimvar(GetJointIndicesAttr());
}

UsdGeomPrimvar UsdSkelBindingAPI::CreateJointIndicesPrimvar(bool constant, int elementSize) const
{
  return UsdGeomPrimvarsAPI(GetPrim()).CreatePrimvar(UsdSkelTokens->primvarsSkelJointIndices,
                                                     SdfValueTypeNames->IntArray,
                                                     constant ? UsdGeomTokens->constant :
                                                                UsdGeomTokens->vertex,
                                                     elementSize);
}

UsdGeomPrimvar UsdSkelBindingAPI::GetJointWeightsPrimvar() const
{
  return UsdGeomPrimvar(GetJointWeightsAttr());
}

UsdGeomPrimvar UsdSkelBindingAPI::CreateJointWeightsPrimvar(bool constant, int elementSize) const
{
  return UsdGeomPrimvarsAPI(GetPrim()).CreatePrimvar(UsdSkelTokens->primvarsSkelJointWeights,
                                                     SdfValueTypeNames->FloatArray,
                                                     constant ? UsdGeomTokens->constant :
                                                                UsdGeomTokens->vertex,
                                                     elementSize);
}

bool UsdSkelBindingAPI::SetRigidJointInfluence(int jointIndex, float weight) const
{
  UsdGeomPrimvar jointIndicesPv = CreateJointIndicesPrimvar(/*constant*/ true, /*elementSize*/ 1);
  UsdGeomPrimvar jointWeightsPv = CreateJointWeightsPrimvar(/*constant*/ true, /*elementSize*/ 1);

  if (jointIndex < 0) {
    TF_WARN("Invalid jointIndex '%d'", jointIndex);
    return false;
  }

  return jointIndicesPv.Set(VtIntArray(1, jointIndex)) &&
         jointWeightsPv.Set(VtFloatArray(1, weight));
}

namespace {

bool _HasInactiveAncestor(const UsdStagePtr &stage, const SdfPath &path)
{
  if (path.IsAbsolutePath() && path.IsPrimPath()) {
    for (SdfPath p = path.GetParentPath(); p != SdfPath::AbsoluteRootPath(); p = p.GetParentPath())
    {
      if (UsdPrim prim = stage->GetPrimAtPath(p)) {
        return !prim.IsActive();
      }
    }
  }
  return false;
}

/// Return the a resolved prim for a target in \p targets.
UsdPrim _GetFirstTargetPrimForRel(const UsdRelationship &rel, const SdfPathVector &targets)
{
  if (targets.size() > 0) {
    if (targets.size() > 1) {
      TF_WARN(
          "%s -- relationship has more than one target. "
          "Only the first will be used.",
          rel.GetPath().GetText());
    }
    const SdfPath &target = targets.front();
    if (UsdPrim prim = rel.GetStage()->GetPrimAtPath(target))
      return prim;

    // Should throw a warning about an invalid target.
    // However, we may not be able to access the prim because one of its
    // ancestors may be inactive. If so, failing to retrieve the prim is
    // expected, so we should avoid warning spam.
    if (!_HasInactiveAncestor(rel.GetStage(), target)) {
      TF_WARN("%s -- Invalid target <%s>.", rel.GetPath().GetText(), target.GetText());
    }
  }
  return UsdPrim();
}

}  // namespace

bool UsdSkelBindingAPI::GetSkeleton(UsdSkelSkeleton *skel) const
{
  if (!skel) {
    TF_CODING_ERROR("'skel' pointer is null.");
    return false;
  }

  if (UsdRelationship rel = GetSkeletonRel()) {

    SdfPathVector targets;
    if (rel.GetForwardedTargets(&targets)) {
      if (!targets.empty() || rel.HasAuthoredTargets()) {
        UsdPrim prim = _GetFirstTargetPrimForRel(rel, targets);
        *skel = UsdSkelSkeleton(prim);

        if (prim && !*skel) {
          TF_WARN(
              "%s -- target (<%s>) of relationship is not "
              "a Skeleton.",
              rel.GetPath().GetText(),
              prim.GetPath().GetText());
        }
        return true;
      }
    }
  }
  *skel = UsdSkelSkeleton();
  return false;
}

UsdSkelSkeleton UsdSkelBindingAPI::GetInheritedSkeleton() const
{
  UsdSkelSkeleton skel;

  if (UsdPrim p = GetPrim()) {
    for (; !p.IsPseudoRoot(); p = p.GetParent()) {
      if (p.HasAPI<UsdSkelBindingAPI>() && UsdSkelBindingAPI(p).GetSkeleton(&skel)) {
        return skel;
      }
    }
  }
  return skel;
}

bool UsdSkelBindingAPI::GetAnimationSource(UsdPrim *prim) const
{
  if (!prim) {
    TF_CODING_ERROR("'prim' pointer is null.");
    return false;
  }

  if (UsdRelationship rel = GetAnimationSourceRel()) {

    SdfPathVector targets;
    if (rel.GetForwardedTargets(&targets)) {
      if (!targets.empty() || rel.HasAuthoredTargets()) {
        *prim = _GetFirstTargetPrimForRel(rel, targets);

        if (*prim && !UsdSkelIsSkelAnimationPrim(*prim)) {
          TF_WARN(
              "%s -- target (<%s>) of relationship is not a valid "
              "skel animation source.",
              rel.GetPath().GetText(),
              prim->GetPath().GetText());
          *prim = UsdPrim();
        }
        return true;
      }
    }
  }
  *prim = UsdPrim();
  return false;
}

UsdPrim UsdSkelBindingAPI::GetInheritedAnimationSource() const
{
  UsdPrim animPrim;

  if (UsdPrim p = GetPrim()) {
    for (; !p.IsPseudoRoot(); p = p.GetParent()) {
      if (p.HasAPI<UsdSkelBindingAPI>() && UsdSkelBindingAPI(p).GetAnimationSource(&animPrim)) {
        return animPrim;
      }
    }
  }
  return animPrim;
}

bool UsdSkelBindingAPI::ValidateJointIndices(TfSpan<const int> indices,
                                             size_t numJoints,
                                             std::string *reason)
{
  for (size_t i = 0; i < indices.size(); ++i) {
    const int jointIndex = indices[i];
    if (jointIndex < 0 || static_cast<size_t>(jointIndex) >= numJoints) {
      if (reason) {
        *reason = TfStringPrintf(
            "Index [%d] at element %td is not in the range [0,%zu)", jointIndex, i, numJoints);
      }
      return false;
    }
  }
  return true;
}

PXR_NAMESPACE_CLOSE_SCOPE
