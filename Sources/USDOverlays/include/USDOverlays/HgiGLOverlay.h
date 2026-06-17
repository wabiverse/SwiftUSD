/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                                  ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                   Copyright (C) 2016 Pixar. All Rights Reserved.
 *                              Copyright (C) 2024 Wabi Foundation.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

#ifndef SWIFTUSD_SWIFTOVERLAY_HGI_GL_OVERLAY_H
#define SWIFTUSD_SWIFTOVERLAY_HGI_GL_OVERLAY_H

#include "HgiGL/hgi.h"
#include "Vt/value.h"

/// `HgiGL::CreateHgi()` registers the `shared_ptr` it creates in
/// `Tf_SharedPtrRetainReleaseHelper<HgiGL>`'s side table with an initial
/// count of 1 (the reference transferred to Swift), then returns the raw
/// pointer directly. `HgiGLRetain`/`HgiGLRelease` (called by Swift's ARC via
/// `SWIFT_SHARED_REFERENCE`) adjust that count and drop the `shared_ptr`
/// once it reaches 0, so Swift can hold the bare `Pixar::HgiGL` - with real
/// reference-counted lifetime - directly from `HgiGL::CreateHgi()`.
namespace Overlay
{
  Pixar::VtValue GetValue(Pixar::HgiGL *hgi);
}

#endif // SWIFTUSD_SWIFTOVERLAY_HGI_GL_OVERLAY_H
