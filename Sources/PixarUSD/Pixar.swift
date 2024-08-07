/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                                        Copyright (C) 2016 Pixar.
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import CxxStdlib
@_exported import pxr

/* --- xxx --- */

public extension Pixar
{
  /**
   * The current version of ``PixarUSD``.
   *
   * The semantic versioning used for ``PixarUSD`` tracks both the upstream
   * Pixar USD version, as well as the evolution iteration of the ``PixarUSD``
   * SwiftPM package, which is setup as follows:
   * - ``PXR_MINOR_VERSION``.``PXR_PATCH_VERSION``.``SWIFTUSD_EVOLUTION`` */
  static let version = "24.08.\(SWIFTUSD_EVOLUTION)"
}

/* --- xxx --- */
