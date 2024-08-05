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

import Ar
import Foundation

public typealias ArDefaultResolverContext = Pixar.ArDefaultResolverContext

public extension ArDefaultResolverContext
{
  private borrowing func GetSearchPathCopy() -> ArDefaultResolverContext.SearchPaths
  {
    __GetSearchPathUnsafe().pointee
  }

  var searchPath: [String]
  {
    GetSearchPathCopy().map
    {
      String($0)
    }
  }
}
