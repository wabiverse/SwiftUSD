//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_GENERATED_CYLINDER_H
#define USDGEOM_GENERATED_CYLINDER_H

/// \file usdGeom/cylinder.h

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
// CYLINDER                                                                   //
// -------------------------------------------------------------------------- //

/// \class UsdGeomCylinder
///
/// Defines a primitive cylinder with closed ends, centered at the
/// origin, whose spine is along the specified \em axis.
///
/// The fallback values for Cube, Sphere, Cone, and Cylinder are set so that
/// they all pack into the same volume/bounds.
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdGeomTokens.
/// So to set an attribute to the value "rightHanded", use UsdGeomTokens->rightHanded
/// as the value.
///
class UsdGeomCylinder : public UsdGeomGprim {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdGeomCylinder on UsdPrim \p prim .
  /// Equivalent to UsdGeomCylinder::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdGeomCylinder(const UsdPrim &prim = UsdPrim()) : UsdGeomGprim(prim) {}

  /// Construct a UsdGeomCylinder on the prim held by \p schemaObj .
  /// Should be preferred over UsdGeomCylinder(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdGeomCylinder(const UsdSchemaBase &schemaObj) : UsdGeomGprim(schemaObj) {}

  /// Destructor.
  USDGEOM_API
  virtual ~UsdGeomCylinder();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDGEOM_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdGeomCylinder holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdGeomCylinder(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDGEOM_API
  static UsdGeomCylinder Get(const UsdStagePtr &stage, const SdfPath &path);

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
  static UsdGeomCylinder Define(const UsdStagePtr &stage, const SdfPath &path);

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
  // HEIGHT
  // --------------------------------------------------------------------- //
  /// The size of the cylinder's spine along the specified
  /// \em axis.  If you author \em height you must also author \em extent.
  ///
  /// \sa GetExtentAttr()
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double height = 2` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDGEOM_API
  UsdAttribute GetHeightAttr() const;

  /// See GetHeightAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateHeightAttr(VtValue const &defaultValue = VtValue(),
                                bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // RADIUS
  // --------------------------------------------------------------------- //
  /// The radius of the cylinder. If you author \em radius
  /// you must also author \em extent.
  ///
  /// \sa GetExtentAttr()
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double radius = 1` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDGEOM_API
  UsdAttribute GetRadiusAttr() const;

  /// See GetRadiusAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateRadiusAttr(VtValue const &defaultValue = VtValue(),
                                bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // AXIS
  // --------------------------------------------------------------------- //
  /// The axis along which the spine of the cylinder is aligned
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `uniform token axis = "Z"` |
  /// | C++ Type | TfToken |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
  /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
  /// | \ref UsdGeomTokens "Allowed Values" | X, Y, Z |
  USDGEOM_API
  UsdAttribute GetAxisAttr() const;

  /// See GetAxisAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDGEOM_API
  UsdAttribute CreateAxisAttr(VtValue const &defaultValue = VtValue(),
                              bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // EXTENT
  // --------------------------------------------------------------------- //
  /// Extent is re-defined on Cylinder only to provide a fallback
  /// value. \sa UsdGeomGprim::GetExtentAttr().
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

  /// Compute the extent for the cylinder defined by the height, radius, and
  /// axis.
  ///
  /// \return true upon success, false if unable to calculate extent.
  ///
  /// On success, extent will contain an approximate axis-aligned bounding
  /// box of the cylinder defined by the height, radius, and axis.
  ///
  /// This function is to provide easy authoring of extent for usd authoring
  /// tools, hence it is static and acts outside a specific prim (as in
  /// attribute based methods).
  USDGEOM_API
  static bool ComputeExtent(double height,
                            double radius,
                            const TfToken &axis,
                            VtVec3fArray *extent);

  /// \overload
  /// Computes the extent as if the matrix \p transform was first applied.
  USDGEOM_API
  static bool ComputeExtent(double height,
                            double radius,
                            const TfToken &axis,
                            const GfMatrix4d &transform,
                            VtVec3fArray *extent);
};

#define USDGEOM_CYLINDER_API_VERSION 1

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // USDGEOM_GENERATED_CYLINDER_H
