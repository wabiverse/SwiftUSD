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
#include "UsdPhysics/distanceJoint.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/types.h"
#include "Sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdPhysicsDistanceJoint,
                 TfType::Bases<UsdPhysicsJoint>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("PhysicsDistanceJoint")
  // to find TfType<UsdPhysicsDistanceJoint>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdPhysicsDistanceJoint>("PhysicsDistanceJoint");
}

/* virtual */
UsdPhysicsDistanceJoint::~UsdPhysicsDistanceJoint()
{
}

/* static */
UsdPhysicsDistanceJoint
UsdPhysicsDistanceJoint::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage)
  {
    TF_CODING_ERROR("Invalid stage");
    return UsdPhysicsDistanceJoint();
  }
  return UsdPhysicsDistanceJoint(stage->GetPrimAtPath(path));
}

/* static */
UsdPhysicsDistanceJoint
UsdPhysicsDistanceJoint::Define(
    const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("PhysicsDistanceJoint");
  if (!stage)
  {
    TF_CODING_ERROR("Invalid stage");
    return UsdPhysicsDistanceJoint();
  }
  return UsdPhysicsDistanceJoint(
      stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdPhysicsDistanceJoint::_GetSchemaKind() const
{
  return UsdPhysicsDistanceJoint::schemaKind;
}

/* static */
const TfType &
UsdPhysicsDistanceJoint::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdPhysicsDistanceJoint>();
  return tfType;
}

/* static */
bool UsdPhysicsDistanceJoint::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &
UsdPhysicsDistanceJoint::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute
UsdPhysicsDistanceJoint::GetMinDistanceAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsMinDistance);
}

UsdAttribute
UsdPhysicsDistanceJoint::CreateMinDistanceAttr(VtValue const &defaultValue, bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsMinDistance,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute
UsdPhysicsDistanceJoint::GetMaxDistanceAttr() const
{
  return GetPrim().GetAttribute(UsdPhysicsTokens->physicsMaxDistance);
}

UsdAttribute
UsdPhysicsDistanceJoint::CreateMaxDistanceAttr(VtValue const &defaultValue, bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdPhysicsTokens->physicsMaxDistance,
                                    SdfValueTypeNames->Float,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

namespace
{
  static inline TfTokenVector
  _ConcatenateAttributeNames(const TfTokenVector &left, const TfTokenVector &right)
  {
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
  }
}

/*static*/
const TfTokenVector &
UsdPhysicsDistanceJoint::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdPhysicsTokens->physicsMinDistance,
      UsdPhysicsTokens->physicsMaxDistance,
  };
  static TfTokenVector allNames =
      _ConcatenateAttributeNames(
          UsdPhysicsJoint::GetSchemaAttributeNames(true),
          localNames);

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
