//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/usd/usdContrived/singleApplyAPI.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/assetPath.h"
#include "pxr/usd/sdf/types.h"

namespace foo {

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdContrivedSingleApplyAPI, TfType::Bases<UsdAPISchemaBase>>();
}

/* virtual */
UsdContrivedSingleApplyAPI::~UsdContrivedSingleApplyAPI() {}

/* static */
UsdContrivedSingleApplyAPI UsdContrivedSingleApplyAPI::Get(const UsdStagePtr &stage,
                                                           const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdContrivedSingleApplyAPI();
  }
  return UsdContrivedSingleApplyAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdContrivedSingleApplyAPI::_GetSchemaKind() const
{
  return UsdContrivedSingleApplyAPI::schemaKind;
}

/* static */
bool UsdContrivedSingleApplyAPI::CanApply(const UsdPrim &prim, std::string *whyNot)
{
  return prim.CanApplyAPI<UsdContrivedSingleApplyAPI>(whyNot);
}

/* static */
UsdContrivedSingleApplyAPI UsdContrivedSingleApplyAPI::Apply(const UsdPrim &prim)
{
  if (prim.ApplyAPI<UsdContrivedSingleApplyAPI>()) {
    return UsdContrivedSingleApplyAPI(prim);
  }
  return UsdContrivedSingleApplyAPI();
}

/* static */
const TfType &UsdContrivedSingleApplyAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdContrivedSingleApplyAPI>();
  return tfType;
}

/* static */
bool UsdContrivedSingleApplyAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdContrivedSingleApplyAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdContrivedSingleApplyAPI::GetTestAttrOneAttr() const
{
  return GetPrim().GetAttribute(UsdContrivedTokens->testAttrOne);
}

UsdAttribute UsdContrivedSingleApplyAPI::CreateTestAttrOneAttr(VtValue const &defaultValue,
                                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdContrivedTokens->testAttrOne,
                                    SdfValueTypeNames->Int,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdContrivedSingleApplyAPI::GetTestAttrTwoAttr() const
{
  return GetPrim().GetAttribute(UsdContrivedTokens->testAttrTwo);
}

UsdAttribute UsdContrivedSingleApplyAPI::CreateTestAttrTwoAttr(VtValue const &defaultValue,
                                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdContrivedTokens->testAttrTwo,
                                    SdfValueTypeNames->Double,
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
const TfTokenVector &UsdContrivedSingleApplyAPI::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdContrivedTokens->testAttrOne,
      UsdContrivedTokens->testAttrTwo,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdAPISchemaBase::GetSchemaAttributeNames(true), localNames);

  if (includeInherited)
    return allNames;
  else
    return localNames;
}

}  // namespace foo

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'namespace foo {', '}'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--
