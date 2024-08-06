//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDSKEL_GENERATED_ROOT_H
#define USDSKEL_GENERATED_ROOT_H

/// \file usdSkel/root.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdGeom/boundable.h"
#include "UsdSkel/api.h"
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
// SKELROOT                                                                   //
// -------------------------------------------------------------------------- //

/// \class UsdSkelRoot
///
/// Boundable prim type used to identify a scope beneath which
/// skeletally-posed primitives are defined.
///
/// A SkelRoot must be defined at or above a skinned primitive for any skinning
/// behaviors in UsdSkel.
///
/// See the extended \ref UsdSkel_SkelRoot "Skel Root Schema" documentation for
/// more information.
///
class UsdSkelRoot : public UsdGeomBoundable {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdSkelRoot on UsdPrim \p prim .
  /// Equivalent to UsdSkelRoot::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdSkelRoot(const UsdPrim &prim = UsdPrim()) : UsdGeomBoundable(prim) {}

  /// Construct a UsdSkelRoot on the prim held by \p schemaObj .
  /// Should be preferred over UsdSkelRoot(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdSkelRoot(const UsdSchemaBase &schemaObj) : UsdGeomBoundable(schemaObj) {}

  /// Destructor.
  USDSKEL_API
  virtual ~UsdSkelRoot();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDSKEL_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdSkelRoot holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdSkelRoot(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDSKEL_API
  static UsdSkelRoot Get(const UsdStagePtr &stage, const SdfPath &path);

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
  USDSKEL_API
  static UsdSkelRoot Define(const UsdStagePtr &stage, const SdfPath &path);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDSKEL_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDSKEL_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDSKEL_API
  const TfType &_GetTfType() const override;

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

  /// Returns the skel root at or above \p prim, or an invalid schema object
  /// if no ancestor prim is defined as a skel root.
  USDSKEL_API
  static UsdSkelRoot Find(const UsdPrim &prim);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
