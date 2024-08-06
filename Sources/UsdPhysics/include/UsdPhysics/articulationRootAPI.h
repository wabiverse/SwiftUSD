//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDPHYSICS_GENERATED_ARTICULATIONROOTAPI_H
#define USDPHYSICS_GENERATED_ARTICULATIONROOTAPI_H

/// \file usdPhysics/articulationRootAPI.h

#include "Usd/apiSchemaBase.h"
#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdPhysics/api.h"
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
// PHYSICSARTICULATIONROOTAPI                                                 //
// -------------------------------------------------------------------------- //

/// \class UsdPhysicsArticulationRootAPI
///
/// PhysicsArticulationRootAPI can be applied to a scene graph node,
/// and marks the subtree rooted here for inclusion in one or more reduced
/// coordinate articulations. For floating articulations, this should be on
/// the root body. For fixed articulations (robotics jargon for e.g. a robot
/// arm for welding that is bolted to the floor), this API can be on a direct
/// or indirect parent of the root joint which is connected to the world, or
/// on the joint itself..
///
class UsdPhysicsArticulationRootAPI : public UsdAPISchemaBase {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

  /// Construct a UsdPhysicsArticulationRootAPI on UsdPrim \p prim .
  /// Equivalent to UsdPhysicsArticulationRootAPI::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdPhysicsArticulationRootAPI(const UsdPrim &prim = UsdPrim()) : UsdAPISchemaBase(prim)
  {
  }

  /// Construct a UsdPhysicsArticulationRootAPI on the prim held by \p schemaObj .
  /// Should be preferred over UsdPhysicsArticulationRootAPI(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdPhysicsArticulationRootAPI(const UsdSchemaBase &schemaObj)
      : UsdAPISchemaBase(schemaObj)
  {
  }

  /// Destructor.
  USDPHYSICS_API
  virtual ~UsdPhysicsArticulationRootAPI();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDPHYSICS_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdPhysicsArticulationRootAPI holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdPhysicsArticulationRootAPI(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDPHYSICS_API
  static UsdPhysicsArticulationRootAPI Get(const UsdStagePtr &stage, const SdfPath &path);

  /// Returns true if this <b>single-apply</b> API schema can be applied to
  /// the given \p prim. If this schema can not be a applied to the prim,
  /// this returns false and, if provided, populates \p whyNot with the
  /// reason it can not be applied.
  ///
  /// Note that if CanApply returns false, that does not necessarily imply
  /// that calling Apply will fail. Callers are expected to call CanApply
  /// before calling Apply if they want to ensure that it is valid to
  /// apply a schema.
  ///
  /// \sa UsdPrim::GetAppliedSchemas()
  /// \sa UsdPrim::HasAPI()
  /// \sa UsdPrim::CanApplyAPI()
  /// \sa UsdPrim::ApplyAPI()
  /// \sa UsdPrim::RemoveAPI()
  ///
  USDPHYSICS_API
  static bool CanApply(const UsdPrim &prim, std::string *whyNot = nullptr);

  /// Applies this <b>single-apply</b> API schema to the given \p prim.
  /// This information is stored by adding "PhysicsArticulationRootAPI" to the
  /// token-valued, listOp metadata \em apiSchemas on the prim.
  ///
  /// \return A valid UsdPhysicsArticulationRootAPI object is returned upon success.
  /// An invalid (or empty) UsdPhysicsArticulationRootAPI object is returned upon
  /// failure. See \ref UsdPrim::ApplyAPI() for conditions
  /// resulting in failure.
  ///
  /// \sa UsdPrim::GetAppliedSchemas()
  /// \sa UsdPrim::HasAPI()
  /// \sa UsdPrim::CanApplyAPI()
  /// \sa UsdPrim::ApplyAPI()
  /// \sa UsdPrim::RemoveAPI()
  ///
  USDPHYSICS_API
  static UsdPhysicsArticulationRootAPI Apply(const UsdPrim &prim);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDPHYSICS_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDPHYSICS_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDPHYSICS_API
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
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
