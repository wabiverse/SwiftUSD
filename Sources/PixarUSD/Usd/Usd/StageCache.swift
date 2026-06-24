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
#if canImport(Usd)
  import Sdf
  import Usd
#else
  import OpenUSD
#endif

public typealias UsdStageCache = Pixar.UsdStageCache
public typealias UsdStageCacheContext = Pixar.UsdStageCacheContext

public extension UsdStageCache
{
  // func contains(_ stage: UsdStage) -> Bool
  // {
  //   Contains(Overlay.TfWeakPtr(stage))
  // }
  //
  // func getId(for stage: UsdStage) -> Int
  // {
  //   GetId(Overlay.TfWeakPtr(stage)).ToLongInt()
  // }
}

public extension UsdStageCacheContext
{
  @discardableResult
  static func bind(cache: inout UsdStageCache) -> UsdStageCacheContext
  {
    Pixar.UsdStageCacheContext.Create(&cache)
  }
}
