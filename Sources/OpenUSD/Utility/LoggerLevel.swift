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

import Logging

extension Logger.Level
{
  /// The log level as a colored string.
  func coloring(_ string: String) -> String
  {
    switch self
    {
      case .critical:
        string.red.bold
      case .error:
        string.red.bold
      case .warning:
        string.yellow.bold
      case .notice:
        string.cyan
      case .info:
        string.cyan
      case .debug:
        string.lightWhite
      case .trace:
        string.lightWhite
    }
  }
}
