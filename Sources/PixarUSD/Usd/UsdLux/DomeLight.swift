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

public typealias UsdLuxDomeLight = Pixar.UsdLuxDomeLight

public extension UsdLux
{
  typealias DomeLight = UsdLuxDomeLight
}

@Xformable
extension UsdLux.DomeLight: GeomXformable
{
  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdLux.DomeLight
  {
    UsdLux.DomeLight.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdLux.DomeLight
  {
    UsdLux.DomeLight.define(stage, path: .init(path))
  }

  public func getTextureFileAttr() -> Usd.Attribute
  {
    GetTextureFileAttr()
  }

  public func createTextureFileAttr(defaultValue: Vt.Value = Vt.Value(), writeSparsely: Bool = false) -> Usd.Attribute
  {
    CreateTextureFileAttr(defaultValue, writeSparsely)
  }
}
