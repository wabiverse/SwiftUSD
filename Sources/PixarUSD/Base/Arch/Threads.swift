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

import Arch

/**
 * # Multithreading
 *
 * Functions having to do with multithreading. */
public extension Arch
{
  /// Return true if the calling thread is the main thread, false otherwise.
  static func isMainThread() -> Bool
  {
    Pixar.ArchIsMainThread()
  }
}
