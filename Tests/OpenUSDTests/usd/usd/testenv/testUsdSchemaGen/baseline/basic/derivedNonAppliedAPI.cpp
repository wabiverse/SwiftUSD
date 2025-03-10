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
#include "pxr/usd/usdContrived/derivedNonAppliedAPI.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/assetPath.h"
#include "pxr/usd/sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdContrivedDerivedNonAppliedAPI, TfType::Bases<UsdContrivedNonAppliedAPI>>();
}

/* virtual */
UsdContrivedDerivedNonAppliedAPI::~UsdContrivedDerivedNonAppliedAPI() {}

/* static */
UsdContrivedDerivedNonAppliedAPI UsdContrivedDerivedNonAppliedAPI::Get(const UsdStagePtr &stage,
                                                                       const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdContrivedDerivedNonAppliedAPI();
  }
  return UsdContrivedDerivedNonAppliedAPI(stage->GetPrimAtPath(path));
}

/* virtual */
UsdSchemaKind UsdContrivedDerivedNonAppliedAPI::_GetSchemaKind() const
{
  return UsdContrivedDerivedNonAppliedAPI::schemaKind;
}

/* static */
const TfType &UsdContrivedDerivedNonAppliedAPI::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdContrivedDerivedNonAppliedAPI>();
  return tfType;
}

/* static */
bool UsdContrivedDerivedNonAppliedAPI::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdContrivedDerivedNonAppliedAPI::_GetTfType() const
{
  return _GetStaticTfType();
}

/*static*/
const TfTokenVector &UsdContrivedDerivedNonAppliedAPI::GetSchemaAttributeNames(
    bool includeInherited)
{
  static TfTokenVector localNames;
  static TfTokenVector allNames = UsdContrivedNonAppliedAPI::GetSchemaAttributeNames(true);

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
