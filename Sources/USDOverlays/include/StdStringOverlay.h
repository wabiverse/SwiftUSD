/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                            ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                   Copyright (C) 2016 Pixar. All Rights Reserved.
 *                              Copyright (C) 2024 Wabi Foundation.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

#ifndef SWIFTUSD_SWIFTOVERLAY_STD_STRING_OVERLAY_H
#define SWIFTUSD_SWIFTOVERLAY_STD_STRING_OVERLAY_H

#include "Plug/registry.h"
#include "Sdf/assetPath.h"
#include "Sdf/layer.h"
#include "Sdf/layerOffset.h"
#include "Sdf/path.h"
#include "Sdf/reference.h"
#include "Tf/token.h"
#include "Usd/attribute.h"
#include "Usd/common.h"
#include "Usd/object.h"
#include "Usd/prim.h"
#include "Usd/references.h"
#include "Usd/stage.h"
#include "Usd/timeCode.h"
#include "UsdShade/shader.h"
#include "Vt/dictionary.h"
#include "Vt/value.h"
#include "pxr/pxrns.h"

/// On Linux/Swift 6.2.1, every `CxxStdlib` overlay initializer for `std::string`
/// (`init(_ string: String)` and `init(_ cString: UnsafePointer<CChar>?)`) triggers
/// a `*** DESERIALIZATION FAILURE ***` while resolving `std::allocator<CChar>`
/// across module boundaries.
///
/// To avoid Swift ever constructing a `std::string` itself, every API that needs
/// one is wrapped here: Swift passes a raw `const char *` (via `withCString`) and
/// the `std::string` is constructed entirely on the C++ side.
namespace Overlay
{
  Pixar::TfToken MakeToken(const char *value);

  Pixar::SdfPath MakePath(const char *path);
  Pixar::SdfAssetPath MakeAssetPath(const char *path);
  Pixar::SdfReference MakeReference(const char *assetPath, const Pixar::SdfPath &primPath, const Pixar::SdfLayerOffset &layerOffset, const Pixar::VtDictionary &customData);

  void SetDocumentation(const Pixar::SdfLayerHandle &layer, const char *doc);
  void SetDocumentation(const Pixar::UsdPrim &prim, const char *doc);
  void SetDocumentation(const Pixar::UsdAttribute &attr, const char *doc);

  bool SetAttributeString(const Pixar::UsdAttribute &attr, const char *value, const Pixar::UsdTimeCode &time);

  Pixar::UsdStageRefPtr CreateNewStage(const char *identifier, Pixar::UsdStage::InitialLoadSet load);
  Pixar::UsdStageRefPtr CreateInMemoryStage(const char *identifier, Pixar::UsdStage::InitialLoadSet load);
  Pixar::UsdStageRefPtr OpenStage(const char *filePath, Pixar::UsdStage::InitialLoadSet load);

  bool AddReference(Pixar::UsdReferences references, const char *assetPath, const Pixar::SdfPath &primPath, const Pixar::SdfLayerOffset &layerOffset, Pixar::UsdListPosition position);
  bool AddReference(Pixar::UsdReferences references, const char *assetPath, const Pixar::SdfLayerOffset &layerOffset, Pixar::UsdListPosition position);

  Pixar::UsdAttribute CreateIdAttr(const Pixar::UsdShadeShader &shader, const char *defaultValue, bool writeSparsely);

  Pixar::PlugRegistry::PlugPathsVector PushBackPath(Pixar::PlugRegistry::PlugPathsVector paths, const char *path);
} // namespace Overlay

#endif // SWIFTUSD_SWIFTOVERLAY_STD_STRING_OVERLAY_H
