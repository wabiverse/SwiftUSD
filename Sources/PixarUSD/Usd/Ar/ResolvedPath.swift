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

#if canImport(Ar)
  import Ar
#else
  import OpenUSD
#endif
import Foundation

public typealias ArResolvedPath = Pixar.ArResolvedPath

public extension ArResolvedPath
{
  var path: String
  {
    String(cString: Overlay.GetResolvedPathText(self))
  }
}
