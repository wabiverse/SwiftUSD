//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDLUX_GENERATED_DOMELIGHT_1_H
#define USDLUX_GENERATED_DOMELIGHT_1_H

/// \file usdLux/domeLight_1.h

#include "Usd/prim.h"
#include "Usd/stage.h"
#include "UsdLux/api.h"
#include "UsdLux/nonboundableLightBase.h"
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
// DOMELIGHT_1                                                                //
// -------------------------------------------------------------------------- //

/// \class UsdLuxDomeLight_1
///
/// Light emitted inward from a distant external environment,
/// such as a sky or IBL light probe.
///
/// In this version of the dome light, the dome's default orientation is
/// determined by its *poleAxis* property. The fallback value, "scene", means
/// that the dome starts with its top pole aligned with the stage's up axis.
///
/// Note that the rotation necessary to align the dome light with its *poleAxis*
/// is intended to be applied by a renderer to only the dome itself, and *not*
/// to inherit down to any USD namespace children of the dome light prim.
///
/// If *poleAxis* is set to "Y" or "scene" and the stage's up axis is "Y", the
/// dome's default orientation will adhere to the OpenEXR specification for
/// latlong environment maps.  From the OpenEXR documentation:
///
/// -------------------------------------------------------------------------
/// Latitude-Longitude Map:
///
/// The environment is projected onto the image using polar coordinates
/// (latitude and longitude).  A pixel's x coordinate corresponds to
/// its longitude, and the y coordinate corresponds to its latitude.
/// Pixel (dataWindow.min.x, dataWindow.min.y) has latitude +pi/2 and
/// longitude +pi; pixel (dataWindow.max.x, dataWindow.max.y) has
/// latitude -pi/2 and longitude -pi.
///
/// In 3D space, latitudes -pi/2 and +pi/2 correspond to the negative and
/// positive y direction.  Latitude 0, longitude 0 points into positive
/// z direction; and latitude 0, longitude pi/2 points into positive x
/// direction.
///
/// The size of the data window should be 2*N by N pixels (width by height),
/// where N can be any integer greater than 0.
/// -------------------------------------------------------------------------
///
/// If *poleAxis* is set to "Z" or "scene" and the stage's up axis is "Z",
/// latitudes -pi/2 and +pi/2 will instead correspond to the negative and
/// positive Z direction, and latitude 0, longitude 0 will instead point into
/// the negative Y direction in 3D space.
///
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdLuxTokens.
/// So to set an attribute to the value "rightHanded", use UsdLuxTokens->rightHanded
/// as the value.
///
class UsdLuxDomeLight_1 : public UsdLuxNonboundableLightBase {
 public:
  /// Compile time constant representing what kind of schema this class is.
  ///
  /// \sa UsdSchemaKind
  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

  /// Construct a UsdLuxDomeLight_1 on UsdPrim \p prim .
  /// Equivalent to UsdLuxDomeLight_1::Get(prim.GetStage(), prim.GetPath())
  /// for a \em valid \p prim, but will not immediately throw an error for
  /// an invalid \p prim
  explicit UsdLuxDomeLight_1(const UsdPrim &prim = UsdPrim()) : UsdLuxNonboundableLightBase(prim)
  {
  }

  /// Construct a UsdLuxDomeLight_1 on the prim held by \p schemaObj .
  /// Should be preferred over UsdLuxDomeLight_1(schemaObj.GetPrim()),
  /// as it preserves SchemaBase state.
  explicit UsdLuxDomeLight_1(const UsdSchemaBase &schemaObj)
      : UsdLuxNonboundableLightBase(schemaObj)
  {
  }

  /// Destructor.
  USDLUX_API
  virtual ~UsdLuxDomeLight_1();

  /// Return a vector of names of all pre-declared attributes for this schema
  /// class and all its ancestor classes.  Does not include attributes that
  /// may be authored by custom/extended methods of the schemas involved.
  USDLUX_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited = true);

  /// Return a UsdLuxDomeLight_1 holding the prim adhering to this
  /// schema at \p path on \p stage.  If no prim exists at \p path on
  /// \p stage, or if the prim at that path does not adhere to this schema,
  /// return an invalid schema object.  This is shorthand for the following:
  ///
  /// \code
  /// UsdLuxDomeLight_1(stage->GetPrimAtPath(path));
  /// \endcode
  ///
  USDLUX_API
  static UsdLuxDomeLight_1 Get(const UsdStagePtr &stage, const SdfPath &path);

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
  static UsdLuxDomeLight_1 Define(const UsdStagePtr &stage, const SdfPath &path);

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
  // TEXTUREFILE
  // --------------------------------------------------------------------- //
  /// A color texture to use on the dome, such as an HDR (high
  /// dynamic range) texture intended for IBL (image based lighting).
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
  // --------------------------------------------------------------------- //
  // TEXTUREFORMAT
  // --------------------------------------------------------------------- //
  /// Specifies the parameterization of the color map file.
  /// Valid values are:
  /// - automatic: Tries to determine the layout from the file itself.
  /// For example, Renderman texture files embed an explicit
  /// parameterization.
  /// - latlong: Latitude as X, longitude as Y.
  /// - mirroredBall: An image of the environment reflected in a
  /// sphere, using an implicitly orthogonal projection.
  /// - angular: Similar to mirroredBall but the radial dimension
  /// is mapped linearly to the angle, providing better sampling
  /// at the edges.
  /// - cubeMapVerticalCross: A cube map with faces laid out as a
  /// vertical cross.
  ///
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `token inputs:texture:format = "automatic"` |
  /// | C++ Type | TfToken |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
  /// | \ref UsdLuxTokens "Allowed Values" | automatic, latlong, mirroredBall, angular,
  /// cubeMapVerticalCross |
  USDLUX_API
  UsdAttribute GetTextureFormatAttr() const;

  /// See GetTextureFormatAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreateTextureFormatAttr(VtValue const &defaultValue = VtValue(),
                                       bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // GUIDERADIUS
  // --------------------------------------------------------------------- //
  /// The radius of guide geometry to use to visualize the dome light.  The default is 1 km for
  /// scenes whose metersPerUnit is the USD default of 0.01 (i.e., 1 world unit is 1 cm).
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `float guideRadius = 100000` |
  /// | C++ Type | float |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
  USDLUX_API
  UsdAttribute GetGuideRadiusAttr() const;

  /// See GetGuideRadiusAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreateGuideRadiusAttr(VtValue const &defaultValue = VtValue(),
                                     bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // POLEAXIS
  // --------------------------------------------------------------------- //
  /// A token which indicates the starting alignment of the dome
  /// light's top pole. This alignment is for the dome itself and is *not*
  /// inherited by the namespace children of the dome.
  /// Valid values are:
  /// - scene: The dome light's top pole is aligned with the stage's up axis.
  /// - Y: The dome light's top pole is aligned with the +Y axis.
  /// - Z: The dome light's top pole is aligned with the +Z axis.
  ///
  ///
  /// | ||
  /// | -- | -- |
  /// | Declaration | `uniform token poleAxis = "scene"` |
  /// | C++ Type | TfToken |
  /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
  /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
  /// | \ref UsdLuxTokens "Allowed Values" | scene, Y, Z |
  USDLUX_API
  UsdAttribute GetPoleAxisAttr() const;

  /// See GetPoleAxisAttr(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
  /// If specified, author \p defaultValue as the attribute's default,
  /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
  /// the default for \p writeSparsely is \c false.
  USDLUX_API
  UsdAttribute CreatePoleAxisAttr(VtValue const &defaultValue = VtValue(),
                                  bool writeSparsely = false) const;

 public:
  // --------------------------------------------------------------------- //
  // PORTALS
  // --------------------------------------------------------------------- //
  /// Optional portals to guide light sampling.
  ///
  USDLUX_API
  UsdRelationship GetPortalsRel() const;

  /// See GetPortalsRel(), and also
  /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create
  USDLUX_API
  UsdRelationship CreatePortalsRel() const;

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
