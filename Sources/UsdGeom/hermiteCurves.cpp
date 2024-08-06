//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/hermiteCurves.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomHermiteCurves, TfType::Bases<UsdGeomCurves>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("HermiteCurves")
  // to find TfType<UsdGeomHermiteCurves>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdGeomHermiteCurves>("HermiteCurves");
}

/* virtual */
UsdGeomHermiteCurves::~UsdGeomHermiteCurves() {}

/* static */
UsdGeomHermiteCurves UsdGeomHermiteCurves::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomHermiteCurves();
  }
  return UsdGeomHermiteCurves(stage->GetPrimAtPath(path));
}

/* static */
UsdGeomHermiteCurves UsdGeomHermiteCurves::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("HermiteCurves");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomHermiteCurves();
  }
  return UsdGeomHermiteCurves(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdGeomHermiteCurves::_GetSchemaKind() const
{
  return UsdGeomHermiteCurves::schemaKind;
}

/* static */
const TfType &UsdGeomHermiteCurves::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomHermiteCurves>();
  return tfType;
}

/* static */
bool UsdGeomHermiteCurves::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomHermiteCurves::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdGeomHermiteCurves::GetTangentsAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->tangents);
}

UsdAttribute UsdGeomHermiteCurves::CreateTangentsAttr(VtValue const &defaultValue,
                                                      bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->tangents,
                                    SdfValueTypeNames->Vector3fArray,
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
const TfTokenVector &UsdGeomHermiteCurves::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdGeomTokens->tangents,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdGeomCurves::GetSchemaAttributeNames(true), localNames);

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

UsdGeomHermiteCurves::PointAndTangentArrays::PointAndTangentArrays(
    const VtArray<GfVec3f> &interleaved)
{
  if (interleaved.empty()) {
    return;
  }
  if (interleaved.size() % 2 != 0) {
    TF_CODING_ERROR(
        "Cannot separate odd-shaped interleaved points and tangents "
        "data.");
    return;
  }
  _points.resize(interleaved.size() / 2);
  _tangents.resize(interleaved.size() / 2);
  auto interleavedIt = interleaved.cbegin();
  auto pointsIt = _points.begin();
  auto tangentsIt = _tangents.begin();
  while (interleavedIt != interleaved.end()) {
    *pointsIt = *interleavedIt;
    std::advance(pointsIt, 1);
    std::advance(interleavedIt, 1);
    *tangentsIt = *interleavedIt;
    std::advance(tangentsIt, 1);
    std::advance(interleavedIt, 1);
  }
  TF_VERIFY(pointsIt == _points.end());
  TF_VERIFY(tangentsIt == _tangents.end());
}

VtVec3fArray UsdGeomHermiteCurves::PointAndTangentArrays::Interleave() const
{
  if (IsEmpty()) {
    return VtVec3fArray();
  }
  VtVec3fArray interleaved(GetPoints().size() * 2);
  auto interleavedIt = interleaved.begin();
  auto pointsIt = GetPoints().cbegin();
  auto tangentsIt = GetTangents().cbegin();
  while (interleavedIt != interleaved.end()) {
    *interleavedIt = *pointsIt;
    std::advance(pointsIt, 1);
    std::advance(interleavedIt, 1);
    *interleavedIt = *tangentsIt;
    std::advance(tangentsIt, 1);
    std::advance(interleavedIt, 1);
  }
  TF_VERIFY(pointsIt == GetPoints().cend());
  TF_VERIFY(tangentsIt == GetTangents().cend());
  return interleaved;
}

PXR_NAMESPACE_CLOSE_SCOPE
