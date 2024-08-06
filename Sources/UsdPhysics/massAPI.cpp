//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdPhysics/massAPI.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdPhysicsMassAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdPhysicsMassAPI::~UsdPhysicsMassAPI() {}

/* static */
UsdPhysicsMassAPI UsdPhysicsMassAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdPhysicsMassAPI();
  }
  return UsdPhysicsMassAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdPhysicsMassAPI::_GetSchemaKind() const
{
  return UsdPhysicsMassAPI::schemaKind;
}

/* static */
bool UsdPhysicsMassAPI::CanApply(const UsdPrim &prim, std::string *whyNot)
{
  return prim.CanApplyAPI<UsdPhysicsMassAPI>(whyNot);
}

/* static */
UsdPhysicsMassAPI UsdPhysicsMassAPI::Apply(const UsdPrim &prim)
{
  if (prim.ApplyAPI<UsdPhysicsMassAPI>()) {
    return UsdPhysicsMassAPI(prim);
  }
  return UsdPhysicsMassAPI();
}

/* static */
const TfType &UsdPhysicsMassAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdPhysicsMassAPI>();
  return tfType;
}

/* static */
bool UsdPhysicsMassAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdPhysicsMassAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdPhysicsMassAPI::GetMassAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsMass);
}

UsdAttribute UsdPhysicsMassAPI::CreateMassAttr(VtValue const &defaultValue,
                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsMass,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdPhysicsMassAPI::GetDensityAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsDensity);
}

UsdAttribute UsdPhysicsMassAPI::CreateDensityAttr(VtValue const &defaultValue,
                                                  bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsDensity,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdPhysicsMassAPI::GetCenterOfMassAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsCenterOfMass);
}

UsdAttribute UsdPhysicsMassAPI::CreateCenterOfMassAttr(VtValue const &defaultValue,
                                                       bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsCenterOfMass,
                                    SdfValueTypeNames->Point3f,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdPhysicsMassAPI::GetDiagonalInertiaAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsDiagonalInertia);
}

UsdAttribute UsdPhysicsMassAPI::CreateDiagonalInertiaAttr(VtValue const &defaultValue,
                                                          bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsDiagonalInertia,
                                    SdfValueTypeNames->Float3,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdPhysicsMassAPI::GetPrincipalAxesAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsPrincipalAxes);
}

UsdAttribute UsdPhysicsMassAPI::CreatePrincipalAxesAttr(VtValue const &defaultValue,
                                                        bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsPrincipalAxes,
                                    SdfValueTypeNames->Quatf,
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
const TfTokenVector &UsdPhysicsMassAPI::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdPhysicsTokens->physicsMass,
      UsdPhysicsTokens->physicsDensity,
      UsdPhysicsTokens->physicsCenterOfMass,
      UsdPhysicsTokens->physicsDiagonalInertia,
      UsdPhysicsTokens->physicsPrincipalAxes,
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
