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

@Xformable
extension UsdGeomXformable: GeomXformable
{}
