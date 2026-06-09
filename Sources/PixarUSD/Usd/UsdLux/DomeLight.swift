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

extension UsdLux.DomeLight: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdLux.DomeLight
  {
    UsdLux.DomeLight.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStage, path: String) -> UsdLux.DomeLight
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


  public func addXformOp(type: UsdGeomXformOp.`Type`,
                         precision: UsdGeomXformOp.Precision = .double,
                         suffix: Tf.Token = Tf.Token(),
                         invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddXformOp(type, precision, suffix, invert)
  }

  public func addTranslateOp(precision: UsdGeomXformOp.Precision = .double,
                             suffix: Tf.Token = Tf.Token(),
                             invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddTranslateOp(precision, suffix, invert)
  }

  public func addScaleOp(precision: UsdGeomXformOp.Precision = .float,
                         suffix: Tf.Token = Tf.Token(),
                         invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddScaleOp(precision, suffix, invert)
  }

  public func addRotateXOp(precision: UsdGeomXformOp.Precision = .float,
                           suffix: Tf.Token = Tf.Token(),
                           invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddRotateXOp(precision, suffix, invert)
  }

  public func addRotateYOp(precision: UsdGeomXformOp.Precision = .float,
                           suffix: Tf.Token = Tf.Token(),
                           invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddRotateYOp(precision, suffix, invert)
  }

  public func addRotateZOp(precision: UsdGeomXformOp.Precision = .float,
                           suffix: Tf.Token = Tf.Token(),
                           invert: Bool = false) -> UsdGeomXformOp
  {
    self.AddRotateZOp(precision, suffix, invert)
  }

}
