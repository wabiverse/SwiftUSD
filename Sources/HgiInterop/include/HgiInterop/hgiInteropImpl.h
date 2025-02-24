//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGIINTEROP_HGIINTEROP_H
#define PXR_IMAGING_HGIINTEROP_HGIINTEROP_H

#include "Gf/vec4i.h"
#include "Hgi/texture.h"
#include "HgiInterop/api.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

#include <memory>

PXR_NAMESPACE_OPEN_SCOPE

class Hgi;
class VtValue;

struct HgiInteropImpl;

/// \class HgiInterop
///
/// Hydra Graphics Interface Interop.
///
/// HgiInterop provides functionality to transfer render targets between
/// supported APIs as efficiently as possible.
///
class HgiInterop final {
 public:
  HGIINTEROP_API
  HgiInterop();

  HGIINTEROP_API
  ~HgiInterop();

  /// Composite the provided textures over the application / viewer's
  /// framebuffer contents.
  /// `srcHgi`:
  ///     Determines the source format/platform of the textures.
  ///     Eg. if hgi is of type HgiMetal, the textures are HgiMetalTexture.
  /// `srcColor`: is the source color aov texture to composite to screen.
  /// `srcDepth`: (optional) is the depth aov texture to composite to screen.
  /// `dstApi`:
  ///     Determines what target format/platform the application is using.
  ///     E.g. If hgi==HgiMetal and dstApi==OpenGL then TransferToApp
  ///     will present the metal textures to the gl application.
  /// `dstFramebuffer`:
  ///     The framebuffer that the source textures are presented into. This
  ///     is a VtValue that encoding a framebuffer in a dstApi specific way.
  ///     E.g., a uint32_t (aka GLuint) for framebuffer object for
  ///     dstApi==OpenGL. For backwards compatibility, the currently bound
  ///     framebuffer is used when the VtValue is empty.
  ///
  /// `dstRegion`:
  ///     Subrect region of the framebuffer over which to composite.
  ///     Coordinates are (left, BOTTOM, width, height) which is the same
  ///     convention as OpenGL viewport coordinates.
  ///
  /// Note:
  /// To composite correctly, blending is enabled.
  /// If `srcDepth` is provided, depth testing is enabled.
  /// As a result, the contents of the application framebuffer matter.
  /// In order to use the contents of `srcColor` and `srcDepth` as-is
  /// (i.e., blit), the color attachment should be cleared to (0,0,0,0) and
  /// the depth attachment needs to be cleared to 1.
  ///
  HGIINTEROP_API
  void TransferToApp(Hgi *srcHgi,
                     HgiTextureHandle const &srcColor,
                     HgiTextureHandle const &srcDepth,
                     TfToken const &dstApi,
                     VtValue const &dstFramebuffer,
                     GfVec4i const &dstRegion);

  /// Retrieve an Hgi, from a VtValue, typically from a client's HdDriver.
  /// This is especially useful for programming languages such as Swift, where
  /// the Hgi base class cannot be utilized, so clients must interface with the
  /// platform specific Hgi (such as HgiGL, HgiMetal, and HgiVulkan). As such,
  /// we cannot rely on inquiring or retrieving the base (Hgi) class from VtValue,
  /// typically done by calling: `IsHolding<Hgi *>()` since platform Hgis created
  /// by client (Swift code in this case) can only be retrieved by their respective
  /// platform-specific Hgis (ex: `IsHolding<HgiGL *>()`, `IsHolding<HgiMetal *>()`)
  /// which this function encapsulates for all the different Hgi backends, if you
  /// ever require checking whether a `VtValue.IsHolding<Hgi *>()`, or casting this
  /// VtValue back to the base Hgi class, you should utilize this function instead.
  HGIINTEROP_API
  static Hgi *GetHgiFromDriver(VtValue const &hdDriver);

 private:
  HgiInterop &operator=(const HgiInterop &) = delete;
  HgiInterop(const HgiInterop &) = delete;

  std::unique_ptr<HgiInteropImpl> _hgiInteropImpl;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif

