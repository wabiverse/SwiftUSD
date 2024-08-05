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
#ifndef USDVOL_GENERATED_FIELDBASE_H
#define USDVOL_GENERATED_FIELDBASE_H

/// \file usdVol/fieldBase.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdGeom/xformable.h"
#include "UsdVol/api.h"
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
// FIELDBASE                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdVolFieldBase
///
/// Base class for field primitives.
///
class UsdVolFieldBase : public UsdGeomXformable {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractTyped;

  /// Construct a UsdVolFieldBase on UsdPrim \p prim .
  /// Equivalent to UsdVolFieldBase::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdVolFieldBase(const UsdPrim &prim = UsdPrim()) : UsdGeomXformable(prim) {}

  /// Construct a UsdVolFieldBase on the prim held by \p schemaObj .
  /// Should be preferred over UsdVolFieldBase(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdVolFieldBase(const UsdSchemaBase &schemaObj) : UsdGeomXformable(schemaObj) {}

  /// Destructor.
  USDVOL_API
  virtual ~UsdVolFieldBase();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDVOL_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdVolFieldBase holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdVolFieldBase(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDVOL_API
  static UsdVolFieldBase Get(const UsdStagePtr &stage, const SdfPath &path);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDVOL_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDVOL_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDVOL_API
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
