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

public typealias UsdLuxDistantLight = Pixar.UsdLuxDistantLight

public extension UsdLux
{
  typealias DistantLight = UsdLuxDistantLight
}

@Xformable
extension UsdLux.DistantLight: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdLux.DistantLight
  {
    UsdLux.DistantLight.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStage, path: String) -> UsdLux.DistantLight
  {
    UsdLux.DistantLight.define(stage, path: .init(path))
  }
}
