//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdLux/domeLight.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdLuxDomeLight, TfType::Bases<UsdLuxNonboundableLightBase>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("DomeLight")
  // to find TfType<UsdLuxDomeLight>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdLuxDomeLight>("DomeLight");
}

/* virtual */
UsdLuxDomeLight::~UsdLuxDomeLight() {}

/* static */
UsdLuxDomeLight UsdLuxDomeLight::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxDomeLight();
  }
  return UsdLuxDomeLight(stage->GetPrimAtPath(path));
}

/* static */
UsdLuxDomeLight UsdLuxDomeLight::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("DomeLight");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxDomeLight();
  }
  return UsdLuxDomeLight(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdLuxDomeLight::_GetSchemaKind() const
{
  return UsdLuxDomeLight::schemaKind;
}

/* static */
const TfType &UsdLuxDomeLight::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdLuxDomeLight>();
  return tfType;
}

/* static */
bool UsdLuxDomeLight::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdLuxDomeLight::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdLuxDomeLight::GetTextureFileAttr() const
{
  return GetPrim().GetAttribute(UsdLuxTokens->inputsTextureFile);
}

UsdAttribute UsdLuxDomeLight::CreateTextureFileAttr(VtValue const &defaultValue,
                                                    bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdLuxTokens->inputsTextureFile,
                                    SdfValueTypeNames->Asset,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdLuxDomeLight::GetTextureFormatAttr() const
{
  return GetPrim().GetAttribute(UsdLuxTokens->inputsTextureFormat);
}

UsdAttribute UsdLuxDomeLight::CreateTextureFormatAttr(VtValue const &defaultValue,
                                                      bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdLuxTokens->inputsTextureFormat,
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdLuxDomeLight::GetGuideRadiusAttr() const
{
  return GetPrim().GetAttribute(UsdLuxTokens->guideRadius);
}

UsdAttribute UsdLuxDomeLight::CreateGuideRadiusAttr(VtValue const &defaultValue,
                                                    bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdLuxTokens->guideRadius,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdRelationship UsdLuxDomeLight::GetPortalsRel() const
{
  return GetPrim().GetRelationship(UsdLuxTokens->portals);
}

UsdRelationship UsdLuxDomeLight::CreatePortalsRel() const
{
  return GetPrim().CreateRelationship(UsdLuxTokens->portals,
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
const TfTokenVector &UsdLuxDomeLight::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdLuxTokens->inputsTextureFile,
      UsdLuxTokens->inputsTextureFormat,
      UsdLuxTokens->guideRadius,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdLuxNonboundableLightBase::GetSchemaAttributeNames(true), localNames);

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

#include "UsdGeom/metrics.h"
#include "UsdGeom/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

void UsdLuxDomeLight::OrientToStageUpAxis() const
{
  if (UsdGeomGetStageUpAxis(GetPrim().GetStage()) == UsdGeomTokens->z) {
    UsdGeomXformOp::Type const opType = UsdGeomXformOp::Type::TypeRotateX;
    TfToken const &opSuffix = UsdLuxTokens->orientToStageUpAxis;
    TfToken const opName = UsdGeomXformOp::GetOpName(opType, opSuffix);
    bool resetsXformStack;
    for (UsdGeomXformOp const &op : GetOrderedXformOps(&resetsXformStack)) {
      if (op.GetName() == opName) {
        // Op already exists.
        return;
      }
    }
    AddXformOp(opType, UsdGeomXformOp::Precision::PrecisionFloat, opSuffix).Set(90.0f);
  }
}

PXR_NAMESPACE_CLOSE_SCOPE
