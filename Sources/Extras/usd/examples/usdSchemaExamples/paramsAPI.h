//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef USDSCHEMAEXAMPLES_GENERATED_PARAMSAPI_H
#define USDSCHEMAEXAMPLES_GENERATED_PARAMSAPI_H

/// \file usdSchemaExamples/paramsAPI.h

#include "./api.h"
#include "./tokens.h"
#include "Usd/apiSchemaBase.h"
#include "Usd/prim.h"
#include "Usd/stage.h"
#include <pxr/pxrns.h>

#include "Vt/value.h"

#include "Gf/matrix4d.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"

#include "Tf/token.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// PARAMSAPI                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdSchemaExamplesParamsAPI
///
///
class UsdSchemaExamplesParamsAPI : public UsdAPISchemaBase {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

  /// Construct a UsdSchemaExamplesParamsAPI on UsdPrim \p prim .
  /// Equivalent to UsdSchemaExamplesParamsAPI::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdSchemaExamplesParamsAPI(const UsdPrim &prim = UsdPrim()) : UsdAPISchemaBase(prim) {}

  /// Construct a UsdSchemaExamplesParamsAPI on the prim held by \p schemaObj .
  /// Should be preferred over UsdSchemaExamplesParamsAPI(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdSchemaExamplesParamsAPI(const UsdSchemaBase &schemaObj) : UsdAPISchemaBase(schemaObj)
  {
  }

  /// Destructor.
  USDSCHEMAEXAMPLES_API
  virtual ~UsdSchemaExamplesParamsAPI();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDSCHEMAEXAMPLES_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdSchemaExamplesParamsAPI holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdSchemaExamplesParamsAPI(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDSCHEMAEXAMPLES_API
  static UsdSchemaExamplesParamsAPI Get(const UsdStagePtr &stage, const SdfPath &path);

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
  USDSCHEMAEXAMPLES_API
  static bool CanApply(const UsdPrim &prim, std::string *whyNot = nullptr);

  /// Applies this <b>single-apply</b> API schema to the given \p prim.
  /// This information is stored by adding "ParamsAPI" to the
  /// token-valued, listOp metadata \em apiSchemas on the prim.
  ///
  /// \return A valid UsdSchemaExamplesParamsAPI object is returned upon success.
  /// An invalid (or empty) UsdSchemaExamplesParamsAPI object is returned upon
  /// failure. See \ref UsdPrim::ApplyAPI() for conditions
  /// resulting in failure.
  ///
  /// \sa UsdPrim::GetAppliedSchemas()
  /// \sa UsdPrim::HasAPI()
  /// \sa UsdPrim::CanApplyAPI()
  /// \sa UsdPrim::ApplyAPI()
  /// \sa UsdPrim::RemoveAPI()
  ///
  USDSCHEMAEXAMPLES_API
  static UsdSchemaExamplesParamsAPI Apply(const UsdPrim &prim);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDSCHEMAEXAMPLES_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDSCHEMAEXAMPLES_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDSCHEMAEXAMPLES_API
  const TfType &_GetTfType() const override;

 public:
  // --------------------------------------------------------------------- //
  // MASS
  // --------------------------------------------------------------------- //
  /// Double value denoting mass
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double params:mass` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDSCHEMAEXAMPLES_API
  UsdAttribute GetMassAttr() const;

  /// See GetMassAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDSCHEMAEXAMPLES_API
  UsdAttribute CreateMassAttr(VtValue const &defaultValue = VtValue(),
                              bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // VELOCITY
  // --------------------------------------------------------------------- //
  /// Double value denoting velocity
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double params:velocity` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDSCHEMAEXAMPLES_API
  UsdAttribute GetVelocityAttr() const;

  /// See GetVelocityAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDSCHEMAEXAMPLES_API
  UsdAttribute CreateVelocityAttr(VtValue const &defaultValue = VtValue(),
                                  bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // VOLUME
  // --------------------------------------------------------------------- //
  /// Double value denoting volume
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `double params:volume` |
  /// | C++ Type | double |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
  USDSCHEMAEXAMPLES_API
  UsdAttribute GetVolumeAttr() const;

  /// See GetVolumeAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDSCHEMAEXAMPLES_API
  UsdAttribute CreateVolumeAttr(VtValue const &defaultValue = VtValue(),
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
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
