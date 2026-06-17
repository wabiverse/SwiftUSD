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

#ifndef SWIFTUSD_SWIFTOVERLAY_HGI_METAL_OVERLAY_H
#define SWIFTUSD_SWIFTOVERLAY_HGI_METAL_OVERLAY_H

#if __APPLE__

#include "HgiMetal/hgi.h"
#include "Vt/value.h"

/// `HgiMetal::CreateHgi()` registers the `shared_ptr` it creates in
/// `Tf_SharedPtrRetainReleaseHelper<HgiMetal>`'s side table with an initial
/// count of 1 (the reference transferred to Swift), then returns the raw
/// pointer directly. `HgiMetalRetain`/`HgiMetalRelease` (called by Swift's
/// ARC via `SWIFT_SHARED_REFERENCE`) adjust that count and drop the
/// `shared_ptr` once it reaches 0, so Swift can hold the bare
/// `Pixar::HgiMetal` - with real reference-counted lifetime - directly from
/// `HgiMetal::CreateHgi()`.
namespace Overlay
{
  Pixar::VtValue GetValue(Pixar::HgiMetal *hgi);
}

#endif // __APPLE__

#endif // SWIFTUSD_SWIFTOVERLAY_HGI_METAL_OVERLAY_H
