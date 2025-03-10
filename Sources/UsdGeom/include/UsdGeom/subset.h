//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_GENERATED_SUBSET_H
#define USDGEOM_GENERATED_SUBSET_H

/// \file usdGeom/subset.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "Usd/typed.h"
#include "UsdGeom/api.h"
#include "UsdGeom/tokens.h"
#include "pxr/pxrns.h"

#include "Tf/token.h"
#include "UsdGeom/imageable.h"
#include "UsdGeom/mesh.h"
#include "UsdGeom/tetMesh.h"

#include "Vt/value.h"

#include "Gf/matrix4d.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// GEOMSUBSET                                                                 //
// -------------------------------------------------------------------------- //

/// \class UsdGeomSubset
///
/// Encodes a subset of a piece of geometry (i.e. a UsdGeomImageable)
/// as a set of indices. Currently supports encoding subsets of faces,
/// points, edges, and tetrahedrons.
///
/// To apply to a geometric prim, a GeomSubset prim must be the prim's direct
/// child in namespace, and possess a concrete defining specifier (i.e. def).
/// This restriction makes it easy and efficient to discover subsets of a prim.
/// We might want to relax this restriction if it's common to have multiple
/// <b>families</b> of subsets on a gprim and if it's useful to be able to
/// organize subsets belonging to a <b>family</b> under a common scope. See
/// 'familyName' attribute for more info on defining a family of subsets.
///
/// Note that a GeomSubset isn't an imageable (i.e. doesn't derive from
/// UsdGeomImageable). So, you can't author <b>visibility</b> for it or
/// override its <b>purpose</b>.
///
/// Materials are bound to GeomSubsets just as they are for regular
/// geometry using API available in UsdShade (UsdShadeMaterial::Bind).
///
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdGeomTokens.
/// So to set an attribute to the value "rightHanded", use UsdGeomTokens->rightHanded
/// as the value.
///
class UsdGeomSubset : public UsdTyped {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdGeomSubset on UsdPrim \p prim .
  /// Equivalent to UsdGeomSubset::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdGeomSubset(const UsdPrim &prim = UsdPrim()) : UsdTyped(prim) {}

  /// Construct a UsdGeomSubset on the prim held by \p schemaObj .
  /// Should be preferred over UsdGeomSubset(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdGeomSubset(const UsdSchemaBase &schemaObj) : UsdTyped(schemaObj) {}

  /// Destructor.
  USDGEOM_API
  virtual ~UsdGeomSubset();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDGEOM_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdGeomSubset holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdGeomSubset(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDGEOM_API
  static UsdGeomSubset Get(const UsdStagePtr &stage, const SdfPath &path);

  /// Attempt to ensure a \a UsdPrim adhering to this schema at \p path
  /// is defined (according to UsdPrim::IsDefined()) on this stage.
  ///
  /// If a prim adhering to this schema at \p path is already defined on this
  /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
  /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
  /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
  /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
  /// current EditTarget for any nonexistent, or existing but not \a Defined
  /// ancestors.
  ///
  /// The given \a path must be an absolute prim path that does not contain
  /// any variant selections.
  ///
  /// If it is impossible to author any of the necessary PrimSpecs, (for
  /// example, in case \a path cannot map to the current UsdEditTarget's
  /// namespace) issue an error and return an invalid \a UsdPrim.
  ///
  /// Note that this method may return a defined prim whose typeName does not
  /// specify this schema class, in case a stronger typeName opinion overrides
  /// the opinion at the current EditTarget.
  ///
  USDGEOM_API
  static UsdGeomSubset Define(const UsdStagePtr &stage, const SdfPath &path);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDGEOM_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDGEOM_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDGEOM_API
  const TfType &_GetTfType() const override;

 public:
  // --------------------------------------------------------------------- //
  // ELEMENTTYPE
  // --------------------------------------------------------------------- //
  /// The type of element that the indices target. "elementType" can
  /// have one of the following values:
  /// <ul><li><b>face</b>: Identifies faces on a Gprim's surface. For a
  /// UsdGeomMesh, each element of the _indices_ attribute would refer to
  /// an element of the Mesh's _faceCounts_ attribute. For a UsdGeomTetMesh,
  /// each element of the _indices_ attribute would refer to an element of
  /// the Mesh's _surfaceFaceVertexIndices_ attribute.</li>
  /// <li><b>point</b>: for any UsdGeomPointBased, each
  /// element of the _indices_ attribute would refer to an element of the
  /// Mesh's _points_ attribute</li>
  /// <li><b>edge</b>: for any UsdGeomMesh, each pair of elements
  /// in the _indices_ attribute would refer to a pair of points of the
  /// Mesh's _points_ attribute that are connected as an implicit edge on the
  /// Mesh. These edges are derived from the Mesh's _faceVertexIndices_
  /// attribute. Edges are not currently defined for a UsdGeomTetMesh, but
  /// could be derived from all tetrahedron edges or surface face edges only
  /// if a specific use-case arises.</li>
  /// <li><b>tetrahedron</b>: for any UsdGeomTetMesh, each element of the
  /// _indices_ attribute would refer to an element of the TetMesh's
  /// _tetVertexIndices_ attribute.
  /// </li></ul>
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `uniform token elementType = "face"` |
  /// | C++ Type | TfToken |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
  /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
  /// | \ref UsdGeomTokens "Allowed Values" | face, point, edge, tetrahedron |
  USDGEOM_API
  UsdAttribute GetElementTypeAttr() const;

  /// See GetElementTypeAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateElementTypeAttr(VtValue const &defaultValue = VtValue(),
                                     bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // INDICES
  // --------------------------------------------------------------------- //
  /// The set of indices included in this subset. The indices need not
  /// be sorted, but the same index should not appear more than once. Indices
  /// are invalid if outside the range [0, elementCount) for the given time on
  /// the parent geometric prim.
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `int[] indices = []` |
  /// | C++ Type | VtArray<int> |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->IntArray |
  USDGEOM_API
  UsdAttribute GetIndicesAttr() const;

  /// See GetIndicesAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateIndicesAttr(VtValue const &defaultValue = VtValue(),
                                 bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // FAMILYNAME
  // --------------------------------------------------------------------- //
  /// The name of the family of subsets that this subset belongs to.
  /// This is optional and is primarily useful when there are multiple
  /// families of subsets under a geometric prim. In some cases, this could
  /// also be used for achieving proper roundtripping of subset data between
  /// DCC apps.
  /// When multiple subsets belonging to a prim have the same familyName, they
  /// are said to belong to the family. A <i>familyType</i> value can be
  /// encoded on the owner of a family of subsets as a token using the static
  /// method UsdGeomSubset::SetFamilyType(). "familyType" can have one of the
  /// following values:
  /// <ul><li><b>UsdGeomTokens->partition</b>: implies that every element of
  /// the whole geometry appears exactly once in only one of the subsets
  /// belonging to the family.</li>
  /// <li><b>UsdGeomTokens->nonOverlapping</b>: an element that appears in one
  /// subset may not appear in any other subset belonging to the family, and
  /// appears only once in the subset in which it appears.</li>
  /// <li><b>UsdGeomTokens->unrestricted</b>: implies that there are no
  /// restrictions w.r.t. the membership of elements in the subsets. They
  /// could be overlapping and the union of all subsets in the family may
  /// not represent the whole.</li>
  /// </ul>
  /// \note The validity of subset data is not enforced by the authoring
  /// APIs, however they can be checked using UsdGeomSubset::ValidateFamily().
  ///
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `uniform token familyName = ""` |
  /// | C++ Type | TfToken |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
  /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
  USDGEOM_API
  UsdAttribute GetFamilyNameAttr() const;

  /// See GetFamilyNameAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateFamilyNameAttr(VtValue const &defaultValue = VtValue(),
                                    bool writeSparsely = false) const;

 public:
  // ===================================================================== //
  // Feel free to add custom code below this line, it will be preserved by
  // the code generator.
  //
  // Just remember to:
  //  - Close the class declaration with };
  //  - Close the namespace with PXR_NAMESPACE_CLOSE_SCOPE
  //  - Close the include guard with #endif
  // ===================================================================== //
  // --(BEGIN CUSTOM CODE)--

  /// Creates a new GeomSubset below the given \p geom with the given
  /// name, \p subsetName, element type, \p elementType and \p indices.
  ///
  /// If a subset named \p subsetName already exists below \p geom, then
  /// this updates its attributes with the values of the provided arguments
  /// (indices value at time 'default' will be updated) and returns it.
  ///
  /// The family type is set / updated on \p geom only if a non-empty value
  /// is passed in for \p familyType and \p familyName.
  USDGEOM_API
  static UsdGeomSubset CreateGeomSubset(const UsdGeomImageable &geom,
                                        const TfToken &subsetName,
                                        const TfToken &elementType,
                                        const VtIntArray &indices,
                                        const TfToken &familyName = TfToken(),
                                        const TfToken &familyType = TfToken());

  /// Creates a new GeomSubset below the given imageable, \p geom with the
  /// given name, \p subsetName, element type, \p elementType and \p indices.
  ///
  /// If a subset named \p subsetName already exists below \p geom, then
  /// this creates a new subset by appending a suitable index as suffix to
  /// \p subsetName (eg, subsetName_1) to avoid name collisions.
  ///
  /// The family type is set / updated on \p geom only if a non-empty value
  /// is passed in for \p familyType and \p familyName.
  USDGEOM_API
  static UsdGeomSubset CreateUniqueGeomSubset(const UsdGeomImageable &geom,
                                              const TfToken &subsetName,
                                              const TfToken &elementType,
                                              const VtIntArray &indices,
                                              const TfToken &familyName = TfToken(),
                                              const TfToken &familyType = TfToken());

  /// Returns all the GeomSubsets defined on the given imageable, \p geom.
  USDGEOM_API
  static std::vector<UsdGeomSubset> GetAllGeomSubsets(const UsdGeomImageable &geom);

  /// Returns all the GeomSubsets of the given \p elementType belonging to
  /// the specified family, \p familyName on the given imageable, \p geom.
  /// If \p elementType is empty, then subsets containing all element types
  /// are returned.
  /// If \p familyName is left empty, then all subsets of the specified
  /// \p elementType will be returned.
  USDGEOM_API
  static std::vector<UsdGeomSubset> GetGeomSubsets(const UsdGeomImageable &geom,
                                                   const TfToken &elementType = TfToken(),
                                                   const TfToken &familyName = TfToken());

  /// Returns the names of all the families of GeomSubsets defined on the given
  /// imageable, \p geom.
  USDGEOM_API
  static TfToken::Set GetAllGeomSubsetFamilyNames(const UsdGeomImageable &geom);

  /// This method is used to encode the type of family that the GeomSubsets
  /// on the given geometric prim \p geom, with the given family name,
  /// \p familyName belong to.
  ///
  /// See \ref UsdGeomSubset::GetFamilyNameAttr for the possible values for
  /// \p familyType.
  ///
  /// When a family of GeomSubsets is tagged as a UsdGeomTokens->partition or
  /// UsdGeomTokens->nonOverlapping, the validity of the data (i.e.
  /// mutual exclusivity and/or wholeness) is not enforced by the authoring
  /// APIs. Use ValidateFamily() to validate the data in a family of
  /// GeomSubsets.
  ///
  /// \return Returns false upon failure to create or set the appropriate
  /// attribute on \p geom.
  USDGEOM_API
  static bool SetFamilyType(const UsdGeomImageable &geom,
                            const TfToken &familyName,
                            const TfToken &familyType);

  /// Returns the type of family that the GeomSubsets on the given geometric
  /// prim \p geom, with the given family name, \p familyName belong to.
  ///
  /// This only returns the token that's encoded on \p geom and does not perform
  /// any actual validation on the family of GeomSubsets. Please use
  /// ValidateFamily() for such validation.
  ///
  /// When familyType is not set on \p geom, the fallback value
  /// UsdTokens->unrestricted is returned.
  USDGEOM_API
  static TfToken GetFamilyType(const UsdGeomImageable &geom, const TfToken &familyName);

  /// Utility for getting the list of indices that are not assigned to any of
  /// the GeomSubsets in the \p familyName family on the given \p geom at the
  /// timeCode, \p time, given the element count (total number of indices in
  /// the array being subdivided).
  ///
  /// For \p elementType UsdGeomTokens->edge, the output array of indices
  /// should be interpreted in pairs, as each sequential pair of indices
  /// corresponds to an edge between the two points. Each edge will be in
  /// the order (lowIndex, highIndex).
  ///
  /// If the \p elementType is not applicable to the given \p geom, an empty
  /// array is returned and a coding error is issued.
  USDGEOM_API
  static VtIntArray GetUnassignedIndices(const UsdGeomImageable &geom,
                                         const TfToken &elementType,
                                         const TfToken &familyName,
                                         const UsdTimeCode &time = UsdTimeCode::EarliestTime());

  /// \deprecated Please use GetUnassignedIndices(geom, elementType,
  /// familyName, time) instead.
  /// Utility for getting the list of indices that are not assigned to any of
  /// the GeomSubsets in \p subsets at the timeCode, \p time, given the
  /// element count (total number of indices in the array being subdivided),
  /// \p elementCount.
  USDGEOM_API
  static VtIntArray GetUnassignedIndices(const std::vector<UsdGeomSubset> &subsets,
                                         const size_t elementCount,
                                         const UsdTimeCode &time = UsdTimeCode::EarliestTime());

  /// \deprecated Please use UsdGeomSubset::ValidateFamily instead.
  /// Validates the data in the given set of GeomSubsets, \p subsets, given
  /// the total number of elements in the array being subdivided,
  /// \p elementCount and the \p familyType that the subsets belong to.
  ///
  /// For proper validation of indices in \p subsets, all of the GeomSubsets
  /// must have the same 'elementType'.
  ///
  /// If one or more subsets contain invalid data, then false is returned and
  /// \p reason is populated with a string explaining the reason why it is
  /// invalid.
  ///
  /// The python version of this method returns a tuple containing
  /// a (bool, string), where the bool has the validity of the subsets and
  /// the string contains the reason (if they're invalid).
  ///
  USDGEOM_API
  static bool ValidateSubsets(const std::vector<UsdGeomSubset> &subsets,
                              const size_t elementCount,
                              const TfToken &familyType,
                              std::string *const reason);

  /// Validates whether the family of subsets identified by the given
  /// \p familyName and \p elementType on the given imageable, \p geom contain
  /// valid data. If the family is designated as a partition or as
  /// non-overlapping using SetFamilyType(), then the validity of the data
  /// is checked. If the familyType is "unrestricted", then this performs only
  /// bounds checking of the values in the "indices" arrays.
  ///
  /// If \p reason is not NULL, then it is populated with a string explaining
  /// why the family is invalid, if it is invalid.
  ///
  /// The python version of this method returns a tuple containing
  /// a (bool, string), where the bool has the validity of the family and
  /// the string contains the reason (if it's invalid).
  ///
  USDGEOM_API
  static bool ValidateFamily(const UsdGeomImageable &geom,
                             const TfToken &elementType,
                             const TfToken &familyName,
                             std::string *const reason);

 private:
  /// Utility to get edges at time \p t from the indices attribute
  /// where every sequential pair of indices is interpreted as an edge.
  /// Returned edges are stored in the order (lowIndex, highIndex).
  /// Assumes the elementType is edge.
  VtVec2iArray _GetEdges(const UsdTimeCode t) const;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
