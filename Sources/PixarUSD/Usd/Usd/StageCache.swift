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
import Foundation
import Sdf
import Usd

public typealias UsdStageCache = Pixar.UsdStageCache
public typealias UsdStageCacheContext = Pixar.UsdStageCacheContext

public extension UsdStageCache
{
  func contains(_ stage: UsdStageRefPtr) -> Bool
  {
    Contains(stage)
  }
}

public extension UsdStageCacheContext
{
  @discardableResult
  static func bind(cache: inout UsdStageCache) -> UsdStageCacheContext
  {
    UsdStageCacheContext.CreateCache(&cache)
  }
}
