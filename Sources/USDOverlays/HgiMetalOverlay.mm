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

#include "USDOverlays/HgiMetalOverlay.h"

#if __APPLE__

namespace Overlay
{
  Pixar::VtValue GetValue(Pixar::HgiMetal *hgi)
  {
    return Pixar::VtValue(static_cast<Pixar::Hgi*>(hgi));
  }
}

#endif // __APPLE__
