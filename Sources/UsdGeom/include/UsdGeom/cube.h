//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_GENERATED_CUBE_H
#define USDGEOM_GENERATED_CUBE_H

/// \file usdGeom/cube.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdGeom/api.h"
#include "UsdGeom/gprim.h"
#include "UsdGeom/tokens.h"
#include "pxr/pxrns.h"

#include "Vt/value.h"

#include "Gf/matrix4d.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// CUBE                                                                       //
// -------------------------------------------------------------------------- //

/// \class UsdGeomCube
///
/// Defines a primitive rectilinear cube centered at the origin.
///
/// The fallback values for Cube, Sphere, Cone, and Cylinder are set so that
/// they all pack into the same volume/bounds.
///
class UsdGeomCube : public UsdGeomGprim {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdGeomCube on UsdPrim \p prim .
  /// Equivalent to UsdGeomCube::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdGeomCube(const UsdPrim &prim = UsdPrim()) : UsdGeomGprim(prim) {}

  /// Construct a UsdGeomCube on the prim held by \p schemaObj .
  /// Should be preferred over UsdGeomCube(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdGeomCube(const UsdSchemaBase &schemaObj) : UsdGeomGprim(schemaObj) {}

  /// Destructor.
  USDGEOM_API
  virtual ~UsdGeomCube();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDGEOM_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdGeomCube holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdGeomCube(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDGEOM_API
  static UsdGeomCube Get(const UsdStagePtr &stage, const SdfPath &path);

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
  static UsdGeomCube Define(const UsdStagePtr &stage, const SdfPath &path);

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
  // SIZE
  // --------------------------------------------------------------------- //
  /// Indicates the length of each edge of the cube.  If you
  /// author \em size you must also author \em extent.
  ///
  /// \sa GetExtentAttr()
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double size = 2` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDGEOM_API
  UsdAttribute GetSizeAttr() const;

  /// See GetSizeAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateSizeAttr(VtValue const &defaultValue = VtValue(),
                              bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // EXTENT
  // --------------------------------------------------------------------- //
  /// Extent is re-defined on Cube only to provide a fallback value.
  /// \sa UsdGeomGprim::GetExtentAttr().
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `float3[] extent = [(-1, -1, -1), (1, 1, 1)]` |
  /// | C++ Type | VtArray<GfVec3f> |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float3Array |
  USDGEOM_API
  UsdAttribute GetExtentAttr() const;

  /// See GetExtentAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateExtentAttr(VtValue const &defaultValue = VtValue(),
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

  /// Compute the extent for the cube defined by the size of each dimension.
  ///
  /// \return true upon success, false if unable to calculate extent.
  ///
  /// On success, extent will contain an approximate axis-aligned bounding
  /// box of the cube defined by the size of each dimension.
  ///
  /// This function is to provide easy authoring of extent for usd authoring
  /// tools, hence it is static and acts outside a specific prim (as in
  /// attribute based methods).
  USDGEOM_API
  static bool ComputeExtent(double size, VtVec3fArray *extent);

  /// \overload
  /// Computes the extent as if the matrix \p transform was first applied.
  USDGEOM_API
  static bool ComputeExtent(double size, const GfMatrix4d &transform, VtVec3fArray *extent);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
