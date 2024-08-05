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

public typealias UsdLuxLightAPI = Pixar.UsdLuxLightAPI

public extension UsdLux
{
  typealias LuxLightAPI = UsdLuxLightAPI
}

public extension UsdLux.LuxLightAPI
{
  @discardableResult
  static func apply(_ prim: Usd.Prim) -> UsdLux.LuxLightAPI
  {
    UsdLux.LuxLightAPI.Apply(prim)
  }
}
