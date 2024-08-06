//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDLUX_GENERATED_RECTLIGHT_H
#define USDLUX_GENERATED_RECTLIGHT_H

/// \file usdLux/rectLight.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdLux/api.h"
#include "UsdLux/boundableLightBase.h"
#include "UsdLux/tokens.h"
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
// RECTLIGHT                                                                  //
// -------------------------------------------------------------------------- //

/// \class UsdLuxRectLight
///
/// Light emitted from one side of a rectangle.
/// The rectangle is centered in the XY plane and emits light along the -Z axis.
/// The rectangle is 1 unit in length in the X and Y axis.  In the default
/// position, a texture file's min coordinates should be at (+X, +Y) and
/// max coordinates at (-X, -Y).
///
class UsdLuxRectLight : public UsdLuxBoundableLightBase {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdLuxRectLight on UsdPrim \p prim .
  /// Equivalent to UsdLuxRectLight::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdLuxRectLight(const UsdPrim &prim = UsdPrim()) : UsdLuxBoundableLightBase(prim) {}

  /// Construct a UsdLuxRectLight on the prim held by \p schemaObj .
  /// Should be preferred over UsdLuxRectLight(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdLuxRectLight(const UsdSchemaBase &schemaObj) : UsdLuxBoundableLightBase(schemaObj) {}

  /// Destructor.
  USDLUX_API
  virtual ~UsdLuxRectLight();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDLUX_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdLuxRectLight holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdLuxRectLight(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDLUX_API
  static UsdLuxRectLight Get(const UsdStagePtr &stage, const SdfPath &path);

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
  USDLUX_API
  static UsdLuxRectLight Define(const UsdStagePtr &stage, const SdfPath &path);

 protected:
  /// Returns the kind of schema this class belongs to.
  ///
  /// \sa UsdSchemaKind
  USDLUX_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:
  // needs to invoke _GetStaticTfType.
  friend class UsdSchemaRegistry;
  USDLUX_API
  static const TfType &_GetStaticTfType();

  static bool _IsTypedSchema();

  // override SchemaBase virtuals.
  USDLUX_API
  const TfType &_GetTfType() const override;

 public:
  // --------------------------------------------------------------------- //
  // WIDTH
  // --------------------------------------------------------------------- //
  /// Width of the rectangle, in the local X axis.
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `float inputs:width = 1` |
  /// | C++ Type | float |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
  USDLUX_API
  UsdAttribute GetWidthAttr() const;

  /// See GetWidthAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreateWidthAttr(VtValue const &defaultValue = VtValue(),
                               bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // HEIGHT
  // --------------------------------------------------------------------- //
  /// Height of the rectangle, in the local Y axis.
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `float inputs:height = 1` |
  /// | C++ Type | float |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
  USDLUX_API
  UsdAttribute GetHeightAttr() const;

  /// See GetHeightAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreateHeightAttr(VtValue const &defaultValue = VtValue(),
                                bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // TEXTUREFILE
  // --------------------------------------------------------------------- //
  /// A color texture to use on the rectangle.
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `asset inputs:texture:file` |
  /// | C++ Type | SdfAssetPath |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Asset |
  USDLUX_API
  UsdAttribute GetTextureFileAttr() const;

  /// See GetTextureFileAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreateTextureFileAttr(VtValue const &defaultValue = VtValue(),
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
