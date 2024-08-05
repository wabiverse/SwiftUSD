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

public typealias UsdLuxPortalLight = Pixar.UsdLuxPortalLight

public extension UsdLux
{
  typealias PortalLight = UsdLuxPortalLight
}

@Xformable
extension UsdLux.PortalLight: GeomXformable
{
  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdLux.PortalLight
  {
    UsdLux.PortalLight.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdLux.PortalLight
  {
    UsdLux.PortalLight.define(stage, path: .init(path))
  }
}
