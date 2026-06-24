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

import ArgumentParser
import Foundation

extension Array: ExpressibleByArgument where Element: ExpressibleByArgument
{
  public var defaultValueDescription: String
  {
    "[" + map(\.defaultValueDescription).joined(separator: ", ") + "]"
  }

  public init?(argument _: String)
  {
    nil
  }
}
