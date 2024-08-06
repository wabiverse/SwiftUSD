//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDRI_GENERATED_RENDERPASSAPI_H
#define USDRI_GENERATED_RENDERPASSAPI_H

/// \file usdRi/renderPassAPI.h

#include "Usd/apiSchemaBase.h"
#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdRi/api.h"
#include "UsdRi/tokens.h"
#include "pxr/pxrns.h"

#include "Usd/collectionAPI.h"

#include "Vt/value.h"

#include "Gf/matrix4d.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// RIRENDERPASSAPI                                                            //
// -------------------------------------------------------------------------- //

/// \class UsdRiRenderPassAPI
///
///
/// RiRenderPassAPI is an API schema that provides a mechanism
/// to set certain Ri statements on each prim in a collection,
/// for a given RenderPass prim.
///
/// \anchor usdRi_cameraVisibility
/// The objects that are relevant to the render is specified via the
/// cameraVisibility collection (UsdCollectionAPI) and can be accessed via
/// GetCameraVisibilityCollectionAPI(). Each prim in the collection will have
/// ri:visible:camera set to 1.  By default everything in the scene should be
/// visible to camera, so this collection sets includeRoot to 1.
///
/// \anchor usdRi_matte
/// The objects that are relevant to the render is specified via the
/// matte collection (UsdCollectionAPI) and can be accessed via
/// GetMatteCollectionAPI().  Each prim in the collection will have
/// ri:matte set to 1.  By default everything in the scene should render
/// normally, so this collection sets includeRoot to 0.
///
///
class UsdRiRenderPassAPI : public UsdAPISchemaBase {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

  /// Construct a UsdRiRenderPassAPI on UsdPrim \p prim .
  /// Equivalent to UsdRiRenderPassAPI::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdRiRenderPassAPI(const UsdPrim &prim = UsdPrim()) : UsdAPISchemaBase(prim) {}

  /// Construct a UsdRiRenderPassAPI on the prim held by \p schemaObj .
  /// Should be preferred over UsdRiRenderPassAPI(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdRiRenderPassAPI(const UsdSchemaBase &schemaObj) : UsdAPISchemaBase(schemaObj) {}

  /// Destructor.
  USDRI_API
  virtual ~UsdRiRenderPassAPI();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDRI_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdRiRenderPassAPI holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdRiRenderPassAPI(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDRI_API
  static UsdRiRenderPassAPI Get(const UsdStagePtr &stage, const SdfPath &path);

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
  USDRI_API
  static bool CanApply(const UsdPrim &prim, std::string *whyNot = nullptr);

  /// Applies this <b>single-apply</b> API schema to the given \p prim.
  /// This information is stored by adding "RiRenderPassAPI" to the
  /// token-valued, listOp metadata \em apiSchemas on the prim.
  ///
  /// \return A valid UsdRiRenderPassAPI object is returned upon success.
  /// An invalid (or empty) UsdRiRenderPassAPI object is returned upon
  /// failure. See \ref UsdPrim::ApplyAPI() for conditions
  /// resulting in failure.
  ///
  /// \sa UsdPrim::GetAppliedSchemas()
  /// \sa UsdPrim::HasAPI()
  /// \sa UsdPrim::CanApplyAPI()
  /// \sa UsdPrim::ApplyAPI()
  /// \sa UsdPrim::RemoveAPI()
  ///
  USDRI_API
  static UsdRiRenderPassAPI Apply(const UsdPrim &prim);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDRI_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDRI_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDRI_API
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

  /// Return the UsdCollectionAPI interface used for examining and
  /// modifying the camera visibility collection of this prim.
  // For more information, see
  // \\ref usdRi_cameraVisibility "Camera Visibility"
  USDRI_API
  UsdCollectionAPI GetCameraVisibilityCollectionAPI() const;

  /// Return the UsdCollectionAPI interface used for examining and
  /// modifying the matte collection of this prim.
  // For more information, see
  // \\ref usdRi_matte "Matte"
  USDRI_API
  UsdCollectionAPI GetMatteCollectionAPI() const;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
