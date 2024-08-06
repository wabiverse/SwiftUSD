//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/tetMesh.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/assetPath.h"
#include "Sdf/types.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<UsdGeomTetMesh, TfType::Bases<UsdGeomPointBased>>();

  // Register the usd prim typename as an alias under UsdSchemaBase. This
  // enables one to call
  // TfType::Find<UsdSchemaBase>().FindDerivedByName("TetMesh")
  // to find TfType<UsdGeomTetMesh>, which is how IsA queries are
  // answered.
  TfType::AddAlias<UsdSchemaBase, UsdGeomTetMesh>("TetMesh");
}

/* virtual */
UsdGeomTetMesh::~UsdGeomTetMesh() {}

/* static */
UsdGeomTetMesh UsdGeomTetMesh::Get(const UsdStagePtr &stage, const SdfPath &path)
{
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomTetMesh();
  }
  return UsdGeomTetMesh(stage->GetPrimAtPath(path));
}

/* static */
UsdGeomTetMesh UsdGeomTetMesh::Define(const UsdStagePtr &stage, const SdfPath &path)
{
  static TfToken usdPrimTypeName("TetMesh");
  if (!stage) {
    TF_CODING_ERROR("Invalid stage");
    return UsdGeomTetMesh();
  }
  return UsdGeomTetMesh(stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdGeomTetMesh::_GetSchemaKind() const
{
  return UsdGeomTetMesh::schemaKind;
}

/* static */
const TfType &UsdGeomTetMesh::_GetStaticTfType()
{
  static TfType tfType = TfType::Find<UsdGeomTetMesh>();
  return tfType;
}

/* static */
bool UsdGeomTetMesh::_IsTypedSchema()
{
  static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
  return isTyped;
}

/* virtual */
const TfType &UsdGeomTetMesh::_GetTfType() const
{
  return _GetStaticTfType();
}

UsdAttribute UsdGeomTetMesh::GetTetVertexIndicesAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->tetVertexIndices);
}

UsdAttribute UsdGeomTetMesh::CreateTetVertexIndicesAttr(VtValue const &defaultValue,
                                                        bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->tetVertexIndices,
                                    SdfValueTypeNames->Int4Array,
                                    /* custom = */ false,
                                    SdfVariabilityVarying,
                                    defaultValue,
                                    writeSparsely);
}

UsdAttribute UsdGeomTetMesh::GetSurfaceFaceVertexIndicesAttr() const
{
  return GetPrim().GetAttribute(UsdGeomTokens->surfaceFaceVertexIndices);
}

UsdAttribute UsdGeomTetMesh::CreateSurfaceFaceVertexIndicesAttr(VtValue const &defaultValue,
                                                                bool writeSparsely) const
{
  return UsdSchemaBase::_CreateAttr(UsdGeomTokens->surfaceFaceVertexIndices,
                                    SdfValueTypeNames->Int3Array,
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
const TfTokenVector &UsdGeomTetMesh::GetSchemaAttributeNames(bool includeInherited)
{
  static TfTokenVector localNames = {
      UsdGeomTokens->tetVertexIndices,
      UsdGeomTokens->surfaceFaceVertexIndices,
  };
  static TfTokenVector allNames = _ConcatenateAttributeNames(
      UsdGeomPointBased::GetSchemaAttributeNames(true), localNames);

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

namespace {

GfVec3i _Sorted(GfVec3i v)
{
  if (v[0] > v[1]) {
    std::swap(v[0], v[1]);
  }
  if (v[0] > v[2]) {
    std::swap(v[0], v[2]);
  }
  if (v[1] > v[2]) {
    std::swap(v[1], v[2]);
  }
  return v;
}

struct _Vec3iHash {
  size_t operator()(const GfVec3i &v) const
  {
    return static_cast<size_t>(v[0]) << 42 ^ static_cast<size_t>(v[1]) << 21 ^
           static_cast<size_t>(v[2]);
  }
};

struct _Vec3iCmp {
  // Comparator function
  bool operator()(const GfVec3i &f1, const GfVec3i &f2)
  {
    if (f1[0] == f2[0]) {
      if (f1[1] == f2[1]) {
        return f1[2] < f2[2];
      }

      return f1[1] < f2[1];
    }

    return f1[0] < f2[0];
  }
};

VtVec3iArray _ComputeSurfaceFaces(const VtVec4iArray &tetVertexIndices)
{

  // The surface faces are made of triangles that are not shared between
  // tetrahedra and only occur once. We use a hashmap from triangles
  // to counting information to see whether a triangle occurs in the
  // hashmap just and thus is not shared. We then sweep the hashmap
  // to find all triangles.
  //
  // Recall that a triangle is a triple of indices. But two triangles are
  // shared if these two triples are related by a permutation. Thus, the
  // key into the hashmap is the sorted triple which we call the signature.
  //
  // The value of the hashmap is a pair of (count, triple). The triple
  // is stored next to the count so that we do not loose the orientation
  // information that was lost when sorting the triple.
  //
  using SigToCountAndTriangle = TfHashMap<GfVec3i, std::pair<size_t, GfVec3i>, _Vec3iHash>;

  SigToCountAndTriangle sigToCountAndTriangle;

  for (size_t t = 0; t < tetVertexIndices.size(); t++) {

    const GfVec4i &tet = tetVertexIndices[t];

    // The four triangles of a tetrahedron
    static int tetFaceIndices[4][3] = {{1, 2, 3}, {0, 3, 2}, {0, 1, 3}, {0, 2, 1}};

    for (int tFace = 0; tFace < 4; tFace++) {

      // A triangle of this tetrahedron.
      const GfVec3i triangle(tet[tetFaceIndices[tFace][0]],
                             tet[tetFaceIndices[tFace][1]],
                             tet[tetFaceIndices[tFace][2]]);

      std::pair<size_t, GfVec3i> &item = sigToCountAndTriangle[_Sorted(triangle)];
      item.first++;
      item.second = triangle;
    }
  }

  VtVec3iArray result;
  // Reserve one surface face per tetrahedron.
  // A tetrahedron can contribute up to 4 faces, but typically,
  // most faces of tet mesh are shared. So this is really just
  // a guess.
  result.reserve(tetVertexIndices.size());

  for (auto &&[sig, countAndTriangle] : sigToCountAndTriangle) {
    if (countAndTriangle.first == 1) {
      result.push_back(countAndTriangle.second);
    }
  }
  // Need to sort results for deterministic behavior across different
  // compiler/OS versions
  std::sort(result.begin(), result.end(), _Vec3iCmp());

  return result;
}

}  // namespace

bool UsdGeomTetMesh::ComputeSurfaceFaces(const UsdGeomTetMesh &tetMesh,
                                         VtVec3iArray *surfaceFaceIndices,
                                         const UsdTimeCode timeCode)
{

  if (surfaceFaceIndices == nullptr) {
    return false;
  }

  const UsdAttribute &tetVertexIndicesAttr = tetMesh.GetTetVertexIndicesAttr();
  VtVec4iArray tetVertexIndices;
  tetVertexIndicesAttr.Get(&tetVertexIndices, timeCode);

  *surfaceFaceIndices = _ComputeSurfaceFaces(tetVertexIndices);
  return true;
}

VtIntArray _FindInvertedElements(const VtVec3fArray &tetMeshPoints,
                                 const VtVec4iArray &tetVertexIndices,
                                 const TfToken &orientation)
{
  VtIntArray invertedElements;
  invertedElements.reserve(tetVertexIndices.size());
  GfVec3f elemPoints[4];

  const float sign = (orientation == UsdGeomTokens->leftHanded) ? -1.0f : 1.0f;

  for (size_t t = 0; t < tetVertexIndices.size(); t++) {
    for (uint_fast8_t p = 0; p < 4; p++) {
      elemPoints[p] = tetMeshPoints[tetVertexIndices[t][p]];
    }

    const float tripleProduct = sign * GfDot(elemPoints[3] - elemPoints[0],
                                             GfCross(elemPoints[1] - elemPoints[0],
                                                     elemPoints[2] - elemPoints[0]));

    if (tripleProduct < 0.0f) {
      invertedElements.push_back(t);
    }
  }

  return invertedElements;
}

bool UsdGeomTetMesh::FindInvertedElements(const UsdGeomTetMesh &tetMesh,
                                          VtIntArray *invertedElements,
                                          const UsdTimeCode timeCode)
{
  if (invertedElements == nullptr) {
    return false;
  }

  const UsdAttribute &tetPointsAttr = tetMesh.GetPointsAttr();
  VtVec3fArray tetMeshPoints;
  tetPointsAttr.Get(&tetMeshPoints, timeCode);

  if (tetMeshPoints.size() < 4) {
    return false;
  }

  const UsdAttribute &tetVertexIndicesAttr = tetMesh.GetTetVertexIndicesAttr();
  VtVec4iArray tetVertexIndices;
  tetVertexIndicesAttr.Get(&tetVertexIndices, timeCode);

  if (tetVertexIndices.size() < 1) {
    return false;
  }

  const UsdAttribute &orientationAttr = tetMesh.GetOrientationAttr();
  TfToken orientation;
  orientationAttr.Get(&orientation);

  *invertedElements = _FindInvertedElements(tetMeshPoints, tetVertexIndices, orientation);
  return true;
}

PXR_NAMESPACE_CLOSE_SCOPE
