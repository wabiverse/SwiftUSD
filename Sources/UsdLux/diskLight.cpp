//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdLux/diskLight.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdLuxDiskLight, TfType::Bases<UsdLuxBoundableLightBase>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("DiskLight")
  // to find TfType<UsdLuxDiskLight>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdLuxDiskLight>("DiskLight");
}

/* virtual */
UsdLuxDiskLight::~UsdLuxDiskLight() {}

/* static */
UsdLuxDiskLight UsdLuxDiskLight::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxDiskLight();
  }
  return UsdLuxDiskLight(stage->GetPrimAtPath(path));
}

/* static */
UsdLuxDiskLight UsdLuxDiskLight::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("DiskLight");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdLuxDiskLight();
  }
  return UsdLuxDiskLight(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdLuxDiskLight::_GetSchemaKind() const
{
  return UsdLuxDiskLight::schemaKind;
}

/* static */
const TfType &UsdLuxDiskLight::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdLuxDiskLight>();
  return tfType;
}

/* static */
bool UsdLuxDiskLight::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdLuxDiskLight::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdLuxDiskLight::GetRadiusAttr() const
{
  return GetPrim().GetAttribute(UsdLuxTokens->inputsRadius);
}

UsdAttribute UsdLuxDiskLight::CreateRadiusAttr(VtValue const &defaultValue,
                                               bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdLuxTokens->inputsRadius,
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
const TfTokenVector &UsdLuxDiskLight::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdLuxTokens->inputsRadius,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdLuxBoundableLightBase::GetSchemaAttributeNames(true), localNames);

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

#include "UsdGeom/boundableComputeExtent.h"

PXR_NAMESPACE_OPEN_SCOPE

static bool _ComputeLocalExtent(const float radius, VtVec3fArray *extent)
{
  extent->resize(2);
  (*extent)[1] = GfVec3f(radius, radius, 0.0f);
  (*extent)[0] = -(*extent)[1];
  return true;
}

static bool _ComputeExtent(const UsdGeomBoundable &boundable,
                           const UsdTimeCode &time,
                           const GfMatrix4d *transform,
                           VtVec3fArray *extent)
{
  const UsdLuxDiskLight light(boundable);
  if (!TF_VERIFY(light)) {
    return false;
  }

  float radius;
  if (!light.GetRadiusAttr().Get(&radius, time)) {
    return false;
  }

  if (!_ComputeLocalExtent(radius, extent)) {
    return false;
  }

  if (transform) {
    GfBBox3d bbox(GfRange3d((*extent)[0], (*extent)[1]), *transform);
    GfRange3d range = bbox.ComputeAlignedRange();
    (*extent)[0] = GfVec3f(range.GetMin());
    (*extent)[1] = GfVec3f(range.GetMax());
  }

  return true;
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
  UsdGeomRegisterComputeExtentFunction<UsdLuxDiskLight>(_ComputeExtent);
}

PXR_NAMESPACE_CLOSE_SCOPE
