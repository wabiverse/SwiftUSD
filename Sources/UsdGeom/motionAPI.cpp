//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/motionAPI.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomMotionAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdGeomMotionAPI::~UsdGeomMotionAPI() {}

/* static */
UsdGeomMotionAPI UsdGeomMotionAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomMotionAPI();
  }
  return UsdGeomMotionAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdGeomMotionAPI::_GetSchemaKind() const
{
  return UsdGeomMotionAPI::schemaKind;
}

/* static */
bool UsdGeomMotionAPI::CanApply(const UsdPrim &prim, std::string *whyNot)
{
  return prim.CanApplyAPI<UsdGeomMotionAPI>(whyNot);
}

/* static */
UsdGeomMotionAPI UsdGeomMotionAPI::Apply(const UsdPrim &prim)
{
  if (prim.ApplyAPI<UsdGeomMotionAPI>()) {
    return UsdGeomMotionAPI(prim);
  }
  return UsdGeomMotionAPI();
}

/* static */
const TfType &UsdGeomMotionAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomMotionAPI>();
  return tfType;
}

/* static */
bool UsdGeomMotionAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomMotionAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdGeomMotionAPI::GetMotionBlurScaleAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->motionBlurScale);
}

UsdAttribute UsdGeomMotionAPI::CreateMotionBlurScaleAttr(VtValue const &defaultValue,
                                                         bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->motionBlurScale,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomMotionAPI::GetVelocityScaleAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->motionVelocityScale);
}

UsdAttribute UsdGeomMotionAPI::CreateVelocityScaleAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->motionVelocityScale,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomMotionAPI::GetNonlinearSampleCountAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->motionNonlinearSampleCount);
}

UsdAttribute UsdGeomMotionAPI::CreateNonlinearSampleCountAttr(VtValue const &defaultValue,
                                                              bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->motionNonlinearSampleCount,
                                    SdfValueTypeNames->Int,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
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
const TfTokenVector &UsdGeomMotionAPI::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdGeomTokens->motionBlurScale,
      UsdGeomTokens->motionVelocityScale,
      UsdGeomTokens->motionNonlinearSampleCount,
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

PXR_NAMESPACE_OPEN_SCOPE

template<class T>
static T _ComputeInheritedMotionAttr(UsdPrim const &queriedPrim,
                                     TfToken const &attrName,
                                     T const &fallbackValue,
                                     UsdTimeCode time)
{
  UsdPrim prim(queriedPrim);
  UsdPrim pseudoRoot = prim.GetStage()->GetPseudoRoot();
  T val = fallbackValue;

  while (prim != pseudoRoot) {
    if (prim.HasAPI<UsdGeomMotionAPI>()) {
      UsdAttribute attr = prim.GetAttribute(attrName);
      if (attr.HasAuthoredValue() && attr.Get(&val, time)) {
        return val;
      }
    }
    prim = prim.GetParent();
  }

  return val;
}

float UsdGeomMotionAPI::ComputeVelocityScale(UsdTimeCode time) const
{
  return _ComputeInheritedMotionAttr<float>(
      GetPrim(), UsdGeomTokens->motionVelocityScale, 1.0, time);
}

int UsdGeomMotionAPI::ComputeNonlinearSampleCount(UsdTimeCode time) const
{
  return _ComputeInheritedMotionAttr<int>(
      GetPrim(), UsdGeomTokens->motionNonlinearSampleCount, 3, time);
}

float UsdGeomMotionAPI::ComputeMotionBlurScale(UsdTimeCode time) const
{
  return _ComputeInheritedMotionAttr<float>(GetPrim(), UsdGeomTokens->motionBlurScale, 1.0, time);
}

PXR_NAMESPACE_CLOSE_SCOPE
