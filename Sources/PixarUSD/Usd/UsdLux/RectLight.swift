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

public typealias UsdLuxRectLight = Pixar.UsdLuxRectLight

public extension UsdLux
{
  typealias RectLight = UsdLuxRectLight
}

@Xformable
extension UsdLux.RectLight: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdLux.RectLight
  {
    UsdLux.RectLight.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStage, path: String) -> UsdLux.RectLight
  {
    UsdLux.RectLight.define(stage, path: .init(path))
  }
}
