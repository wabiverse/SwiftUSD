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

import UsdLux

public typealias UsdLuxVolumeLightAPI = Pixar.UsdLuxVolumeLightAPI

public extension UsdLux
{
  typealias VolumeLightAPI = UsdLuxVolumeLightAPI
}

public extension UsdLux.VolumeLightAPI
{
  @discardableResult
  static func apply(_ prim: Usd.Prim) -> UsdLux.VolumeLightAPI
  {
    UsdLux.VolumeLightAPI.Apply(prim)
  }
}
