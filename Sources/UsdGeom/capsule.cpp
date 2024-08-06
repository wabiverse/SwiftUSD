//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/capsule.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomCapsule, TfType::Bases<UsdGeomGprim>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("Capsule")
  // to find TfType<UsdGeomCapsule>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdGeomCapsule>("Capsule");
}

/* virtual */
UsdGeomCapsule::~UsdGeomCapsule() {}

/* static */
UsdGeomCapsule UsdGeomCapsule::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomCapsule();
  }
  return UsdGeomCapsule(stage->GetPrimAtPath(path));
}

/* static */
UsdGeomCapsule UsdGeomCapsule::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("Capsule");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomCapsule();
  }
  return UsdGeomCapsule(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdGeomCapsule::_GetSchemaKind() const
{
  return UsdGeomCapsule::schemaKind;
}

/* static */
const TfType &UsdGeomCapsule::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomCapsule>();
  return tfType;
}

/* static */
bool UsdGeomCapsule::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomCapsule::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdGeomCapsule::GetHeightAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->height);
}

UsdAttribute UsdGeomCapsule::CreateHeightAttr(VtValue const &defaultValue,
                                              bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->height,
                                    SdfValueTypeNames->Double,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomCapsule::GetRadiusAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->radius);
}

UsdAttribute UsdGeomCapsule::CreateRadiusAttr(VtValue const &defaultValue,
                                              bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->radius,
                                    SdfValueTypeNames->Double,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomCapsule::GetAxisAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->axis);
}

UsdAttribute UsdGeomCapsule::CreateAxisAttr(VtValue const &defaultValue, bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->axis,
                                    SdfValueTypeNames->Token,
                                    /* custom = */ false,
                                    SdfVariabilityUniform,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomCapsule::GetExtentAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->extent);
}

UsdAttribute UsdGeomCapsule::CreateExtentAttr(VtValue const &defaultValue,
                                              bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->extent,
                                    SdfValueTypeNames->Float3Array,
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
const TfTokenVector &UsdGeomCapsule::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdGeomTokens->height,
      UsdGeomTokens->radius,
      UsdGeomTokens->axis,
      UsdGeomTokens->extent,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdGeomGprim::GetSchemaAttributeNames(true), localNames);

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

#include "Tf/registryManager.h"
#include "UsdGeom/boundableComputeExtent.h"

PXR_NAMESPACE_OPEN_SCOPE

static bool _ComputeExtentMax(double height, double radius, const TfToken &axis, GfVec3f *max)
{
  // The height is increased by the capsule's radius from the hemispheres on
  // either side of the capsule.
  float halfHeightWithCap = height * 0.5 + radius;

  if (axis == UsdGeomTokens->x) {
    *max = GfVec3f(halfHeightWithCap, radius, radius);
  }
  else if (axis == UsdGeomTokens->y) {
    *max = GfVec3f(radius, halfHeightWithCap, radius);
  }
  else if (axis == UsdGeomTokens->z) {
    *max = GfVec3f(radius, radius, halfHeightWithCap);
  }
  else {
    return false;  // invalid axis
  }

  return true;
}

bool UsdGeomCapsule::ComputeExtent(double height,
                                   double radius,
                                   const TfToken &axis,
                                   VtVec3fArray *extent)
{
  // Create Sized Extent
  extent->resize(2);

  GfVec3f max;
  if (!_ComputeExtentMax(height, radius, axis, &max)) {
    return false;
  }

  (*extent)[0] = -max;
  (*extent)[1] = max;

  return true;
}

bool UsdGeomCapsule::ComputeExtent(double height,
                                   double radius,
                                   const TfToken &axis,
                                   const GfMatrix4d &transform,
                                   VtVec3fArray *extent)
{
  // Create Sized Extent
  extent->resize(2);

  GfVec3f max;
  if (!_ComputeExtentMax(height, radius, axis, &max)) {
    return false;
  }

  GfBBox3d bbox = GfBBox3d(GfRange3d(-max, max), transform);
  GfRange3d range = bbox.ComputeAlignedRange();
  (*extent)[0] = GfVec3f(range.GetMin());
  (*extent)[1] = GfVec3f(range.GetMax());

  return true;
}

static bool _ComputeExtentForCapsule(const UsdGeomBoundable &boundable,
                                     const UsdTimeCode &time,
                                     const GfMatrix4d *transform,
                                     VtVec3fArray *extent)
{
  const UsdGeomCapsule capsuleSchema(boundable);
  if (!TF_VERIFY(capsuleSchema)) {
    return false;
  }

  double height;
  if (!capsuleSchema.GetHeightAttr().Get(&height, time)) {
    return false;
  }

  double radius;
  if (!capsuleSchema.GetRadiusAttr().Get(&radius, time)) {
    return false;
  }

  TfToken axis;
  if (!capsuleSchema.GetAxisAttr().Get(&axis, time)) {
    return false;
  }

  if (transform) {
    return UsdGeomCapsule::ComputeExtent(height, radius, axis, *transform, extent);
  }
  else {
    return UsdGeomCapsule::ComputeExtent(height, radius, axis, extent);
  }
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
  UsdGeomRegisterComputeExtentFunction<UsdGeomCapsule>(_ComputeExtentForCapsule);
}

PXR_NAMESPACE_CLOSE_SCOPE
