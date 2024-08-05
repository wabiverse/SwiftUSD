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
 * # System Functions
 *
 * Functions that encapsulate differing low-level system calls. */
public extension Arch
{
  /// Return current working directory as a string.
  static func getCwd() -> String
  {
    String(Pixar.ArchGetCwd())
  }

  /// Return the path to the program's executable.
  static func getExecutablePath() -> String
  {
    String(Pixar.ArchGetExecutablePath())
  }

  /// Return the system's memory page size. Safe to assume power-of-two.
  static func getPageSize() -> Int
  {
    Int(Pixar.ArchGetPageSize())
  }
}
