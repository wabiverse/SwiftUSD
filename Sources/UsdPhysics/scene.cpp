//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdPhysics/scene.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdPhysicsScene, TfType::Bases<UsdTyped>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("PhysicsScene")
  // to find TfType<UsdPhysicsScene>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdPhysicsScene>("PhysicsScene");
}

/* virtual */
UsdPhysicsScene::~UsdPhysicsScene() {}

/* static */
UsdPhysicsScene UsdPhysicsScene::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdPhysicsScene();
  }
  return UsdPhysicsScene(stage->GetPrimAtPath(path));
}

/* static */
UsdPhysicsScene UsdPhysicsScene::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("PhysicsScene");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdPhysicsScene();
  }
  return UsdPhysicsScene(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdPhysicsScene::_GetSchemaKind() const
{
  return UsdPhysicsScene::schemaKind;
}

/* static */
const TfType &UsdPhysicsScene::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdPhysicsScene>();
  return tfType;
}

/* static */
bool UsdPhysicsScene::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdPhysicsScene::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdPhysicsScene::GetGravityDirectionAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsGravityDirection);
}

UsdAttribute UsdPhysicsScene::CreateGravityDirectionAttr(VtValue const &defaultValue,
                                                         bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsGravityDirection,
                                    SdfValueTypeNames->Vector3f,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdPhysicsScene::GetGravityMagnitudeAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsGravityMagnitude);
}

UsdAttribute UsdPhysicsScene::CreateGravityMagnitudeAttr(VtValue const &defaultValue,
                                                         bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsGravityMagnitude,
                                    SdfValueTypeNames->Float,
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
const TfTokenVector &UsdPhysicsScene::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdPhysicsTokens->physicsGravityDirection,
      UsdPhysicsTokens->physicsGravityMagnitude,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdTyped::GetSchemaAttributeNames(true), localNames);

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
