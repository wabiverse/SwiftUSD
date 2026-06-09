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

import UsdGeom

public typealias UsdGeomXformable = Pixar.UsdGeomXformable

public extension UsdGeom
{
  typealias Xformable = UsdGeomXformable
}

@attached(member, names: arbitrary, conformances: GeomXformable)
public macro Xformable() = #externalMacro(module: "PixarMacros", type: "PixarXformableMacro")

public protocol GeomXformable
{
  func addXformOp(type: UsdGeomXformOp.`Type`,
                  precision: UsdGeomXformOp.Precision,
                  suffix: Tf.Token,
                  invert: Bool) -> UsdGeomXformOp

  func addTranslateOp(precision: UsdGeomXformOp.Precision,
                      suffix: Tf.Token,
                      invert: Bool) -> UsdGeomXformOp

  func addScaleOp(precision: UsdGeomXformOp.Precision,
                  suffix: Tf.Token,
                  invert: Bool) -> UsdGeomXformOp

  func addRotateXOp(precision: UsdGeomXformOp.Precision,
                    suffix: Tf.Token,
                    invert: Bool) -> UsdGeomXformOp

  func addRotateYOp(precision: UsdGeomXformOp.Precision,
                    suffix: Tf.Token,
                    invert: Bool) -> UsdGeomXformOp

  func addRotateZOp(precision: UsdGeomXformOp.Precision,
                    suffix: Tf.Token,
                    invert: Bool) -> UsdGeomXformOp
}

extension UsdGeomXformable: GeomXformable
{

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
