//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdRender/pass.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdRenderPass, TfType::Bases<UsdTyped>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("RenderPass")
  // to find TfType<UsdRenderPass>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdRenderPass>("RenderPass");
}

/* virtual */
UsdRenderPass::~UsdRenderPass() {}

/* static */
UsdRenderPass UsdRenderPass::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdRenderPass();
  }
  return UsdRenderPass(stage->GetPrimAtPath(path));
}

/* static */
UsdRenderPass UsdRenderPass::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("RenderPass");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdRenderPass();
  }
  return UsdRenderPass(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdRenderPass::_GetSchemaKind() const
{
  return UsdRenderPass::schemaKind;
}

/* static */
const TfType &UsdRenderPass::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdRenderPass>();
  return tfType;
}

/* static */
bool UsdRenderPass::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdRenderPass::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdRenderPass::GetPassTypeAttr() const
{
  return GetPrim().GetAttribute(UsdRenderTokens->passType);
}

UsdAttribute UsdRenderPass::CreatePassTypeAttr(VtValue const &defaultValue,
                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdRenderTokens->passType,
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdRenderPass::GetCommandAttr() const
{
  return GetPrim().GetAttribute(UsdRenderTokens->command);
}

UsdAttribute UsdRenderPass::CreateCommandAttr(VtValue const &defaultValue,
                                              bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdRenderTokens->command,
                                    SdfValueTypeNames->StringArray,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdRenderPass::GetFileNameAttr() const
{
  return GetPrim().GetAttribute(UsdRenderTokens->fileName);
}

UsdAttribute UsdRenderPass::CreateFileNameAttr(VtValue const &defaultValue,
                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdRenderTokens->fileName,
                                    SdfValueTypeNames->Asset,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdRenderPass::GetDenoiseEnableAttr() const
{
  return GetPrim().GetAttribute(UsdRenderTokens->denoiseEnable);
}

UsdAttribute UsdRenderPass::CreateDenoiseEnableAttr(VtValue const &defaultValue,
                                                    bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdRenderTokens->denoiseEnable,
                                    SdfValueTypeNames->Bool,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdRelationship UsdRenderPass::GetRenderSourceRel() const
{
  return GetPrim().GetRelationship(UsdRenderTokens->renderSource);
}

UsdRelationship UsdRenderPass::CreateRenderSourceRel() const
{
  return GetPrim().CreateRelationship(UsdRenderTokens->renderSource,
                                      /* custom = */ false);
}

UsdRelationship UsdRenderPass::GetInputPassesRel() const
{
  return GetPrim().GetRelationship(UsdRenderTokens->inputPasses);
}

UsdRelationship UsdRenderPass::CreateInputPassesRel() const
{
  return GetPrim().CreateRelationship(UsdRenderTokens->inputPasses,
                                      /* custom = */ false);
}

UsdRelationship UsdRenderPass::GetDenoisePassRel() const
{
  return GetPrim().GetRelationship(UsdRenderTokens->denoisePass);
}

UsdRelationship UsdRenderPass::CreateDenoisePassRel() const
{
  return GetPrim().CreateRelationship(UsdRenderTokens->denoisePass,
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
const TfTokenVector &UsdRenderPass::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdRenderTokens->passType,
      UsdRenderTokens->command,
      UsdRenderTokens->fileName,
      UsdRenderTokens->denoiseEnable,
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
PXR_NAMESPACE_OPEN_SCOPE

UsdCollectionAPI UsdRenderPass::GetRenderVisibilityCollectionAPI() const
{
  return UsdCollectionAPI(GetPrim(), UsdRenderTokens->renderVisibility);
}

PXR_NAMESPACE_CLOSE_SCOPE
