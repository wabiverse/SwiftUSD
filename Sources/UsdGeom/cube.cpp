//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/cube.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomCube, TfType::Bases<UsdGeomGprim>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("Cube")
  // to find TfType<UsdGeomCube>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdGeomCube>("Cube");
}

/* virtual */
UsdGeomCube::~UsdGeomCube() {}

/* static */
UsdGeomCube UsdGeomCube::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomCube();
  }
  return UsdGeomCube(stage->GetPrimAtPath(path));
}

/* static */
UsdGeomCube UsdGeomCube::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("Cube");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomCube();
  }
  return UsdGeomCube(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdGeomCube::_GetSchemaKind() const
{
  return UsdGeomCube::schemaKind;
}

/* static */
const TfType &UsdGeomCube::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomCube>();
  return tfType;
}

/* static */
bool UsdGeomCube::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomCube::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdGeomCube::GetSizeAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->size);
}

UsdAttribute UsdGeomCube::CreateSizeAttr(VtValue const &defaultValue, bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->size,
                                    SdfValueTypeNames->Double,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomCube::GetExtentAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->extent);
}

UsdAttribute UsdGeomCube::CreateExtentAttr(VtValue const &defaultValue, bool writeSparsely) const
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
const TfTokenVector &UsdGeomCube::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdGeomTokens->size,
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

bool UsdGeomCube::ComputeExtent(double size, VtVec3fArray *extent)
{
  // Create Sized Extent
  extent->resize(2);

  (*extent)[0] = GfVec3f(size * -0.5);
  (*extent)[1] = GfVec3f(size * 0.5);

  return true;
}

bool UsdGeomCube::ComputeExtent(double size, const GfMatrix4d &transform, VtVec3fArray *extent)
{
  // Create Sized Extent
  extent->resize(2);

  GfBBox3d bbox = GfBBox3d(GfRange3d(GfVec3d(size * -0.5), GfVec3d(size * 0.5)), transform);
  GfRange3d range = bbox.ComputeAlignedRange();
  (*extent)[0] = GfVec3f(range.GetMin());
  (*extent)[1] = GfVec3f(range.GetMax());

  return true;
}

static bool _ComputeExtentForCube(const UsdGeomBoundable &boundable,
                                  const UsdTimeCode &time,
                                  const GfMatrix4d *transform,
                                  VtVec3fArray *extent)
{
  const UsdGeomCube cubeSchema(boundable);
  if (!TF_VERIFY(cubeSchema)) {
    return false;
  }

  double size;
  if (!cubeSchema.GetSizeAttr().Get(&size, time)) {
    return false;
  }

  if (transform) {
    return UsdGeomCube::ComputeExtent(size, *transform, extent);
  }
  else {
    return UsdGeomCube::ComputeExtent(size, extent);
  }
}

TF_REGISTRY_FUNCTION(UsdGeomBoundable)
{
  UsdGeomRegisterComputeExtentFunction<UsdGeomCube>(_ComputeExtentForCube);
}

PXR_NAMESPACE_CLOSE_SCOPE
