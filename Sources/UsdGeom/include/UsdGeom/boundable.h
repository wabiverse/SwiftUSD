//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_GENERATED_BOUNDABLE_H
#define USDGEOM_GENERATED_BOUNDABLE_H

/// \file usdGeom/boundable.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdGeom/api.h"
#include "UsdGeom/tokens.h"
#include "UsdGeom/xformable.h"
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
// BOUNDABLE                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdGeomBoundable
///
/// Boundable introduces the ability for a prim to persistently
/// cache a rectilinear, local-space, extent.
///
/// \section UsdGeom_Boundable_Extent Why Extent and not Bounds ?
/// Boundable introduces the notion of "extent", which is a cached computation
/// of a prim's local-space 3D range for its resolved attributes <b>at the
/// layer and time in which extent is authored</b>.  We have found that with
/// composed scene description, attempting to cache pre-computed bounds at
/// interior prims in a scene graph is very fragile, given the ease with which
/// one can author a single attribute in a stronger layer that can invalidate
/// many authored caches - or with which a re-published, referenced asset can
/// do the same.
///
/// Therefore, we limit to precomputing (generally) leaf-prim extent, which
/// avoids the need to read in large point arrays to compute bounds, and
/// provides UsdGeomBBoxCache the means to efficiently compute and
/// (session-only) cache intermediate bounds.  You are free to compute and
/// author intermediate bounds into your scenes, of course, which may work
/// well if you have sufficient locks on your pipeline to guarantee that once
/// authored, the geometry and transforms upon which they are based will
/// remain unchanged, or if accuracy of the bounds is not an ironclad
/// requisite.
///
/// When intermediate bounds are authored on Boundable parents, the child prims
/// will be pruned from BBox computation; the authored extent is expected to
/// incorporate all child bounds.
///
class UsdGeomBoundable : public UsdGeomXformable {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractTyped;

  /// Construct a UsdGeomBoundable on UsdPrim \p prim .
  /// Equivalent to UsdGeomBoundable::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdGeomBoundable(const UsdPrim &prim = UsdPrim()) : UsdGeomXformable(prim) {}

  /// Construct a UsdGeomBoundable on the prim held by \p schemaObj .
  /// Should be preferred over UsdGeomBoundable(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdGeomBoundable(const UsdSchemaBase &schemaObj) : UsdGeomXformable(schemaObj) {}

  /// Destructor.
  USDGEOM_API
  virtual ~UsdGeomBoundable();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDGEOM_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdGeomBoundable holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdGeomBoundable(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDGEOM_API
  static UsdGeomBoundable Get(const UsdStagePtr &stage, const SdfPath &path);

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
  // EXTENT
  // --------------------------------------------------------------------- //
  /// Extent is a three dimensional range measuring the geometric
  /// extent of the authored gprim in its own local space (i.e. its own
  /// transform not applied), \em without accounting for any shader-induced
  /// displacement. If __any__ extent value has been authored for a given
  /// Boundable, then it should be authored at every timeSample at which
  /// geometry-affecting properties are authored, to ensure correct
  /// evaluation via ComputeExtent(). If __no__ extent value has been
  /// authored, then ComputeExtent() will call the Boundable's registered
  /// ComputeExtentFunction(), which may be expensive, which is why we
  /// strongly encourage proper authoring of extent.
  /// \sa ComputeExtent()
  /// \sa \ref UsdGeom_Boundable_Extent.
  ///
  /// An authored extent on a prim which has children is expected to include
  /// the extent of all children, as they will be pruned from BBox computation
  /// during traversal.
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `float3[] extent` |
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

  /// If an extent is authored on this boundable, it queries the \p extent
  /// from the extent attribute, otherwise if ComputeExtentFunction is
  /// registered for the boundable's type, it computes the \p extent at
  /// \p time. Returns true when extent is successfully populated, false
  /// otherwise.
  ///
  /// \sa ComputeExtentFromPlugins
  /// \sa UsdGeomRegisterComputeExtentFunction
  USDGEOM_API
  bool ComputeExtent(const UsdTimeCode &time, VtVec3fArray *extent) const;

  /// Compute the extent for the Boundable prim \p boundable at time
  /// \p time.  If successful, populates \p extent with the result and
  /// returns \c true, otherwise returns \c false.
  ///
  /// The extent computation is based on the concrete type of the prim
  /// represented by \p boundable.  Plugins that provide a Boundable
  /// prim type may implement and register an extent computation for that
  /// type using #UsdGeomRegisterComputeExtentFunction.
  /// ComputeExtentFromPlugins will use this function to compute extents
  /// for all prims of that type.  If no function has been registered for
  /// a prim type, but a function has been registered for one of its
  /// base types, that function will be used instead.
  ///
  /// \note This function may load plugins in order to access the extent
  /// computation for a prim type.
  USDGEOM_API
  static bool ComputeExtentFromPlugins(const UsdGeomBoundable &boundable,
                                       const UsdTimeCode &time,
                                       VtVec3fArray *extent);

  /// \overload
  /// Computes the extent as if the matrix \p transform was first applied.
  USDGEOM_API
  static bool ComputeExtentFromPlugins(const UsdGeomBoundable &boundable,
                                       const UsdTimeCode &time,
                                       const GfMatrix4d &transform,
                                       VtVec3fArray *extent);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
