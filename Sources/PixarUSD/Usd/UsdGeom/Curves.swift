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

public typealias UsdGeomCurves = Pixar.UsdGeomCurves

public extension UsdGeom
{
  typealias Curves = UsdGeomCurves
}

extension UsdGeom.Curves: GeomXformable
{
  public static func get(_ stage: UsdStage, path: Sdf.Path) -> UsdGeom.Curves
  {
    UsdGeom.Curves.Get(Overlay.TfWeakPtr(stage), path)
  }

  public static func get(_ stage: UsdStage, path: String) -> UsdGeom.Curves
  {
    UsdGeom.Curves.get(stage, path: .init(path))
  }

  public func getCurveVertexCountsAttr() -> Usd.Attribute
  {
    GetCurveVertexCountsAttr()
  }

  @discardableResult
  public func createCurveVertexCountsAttr(_ defaultValue: Vt.Value = Vt.Value(),
                                          writeSparsely: Bool = false) -> Usd.Attribute
  {
    CreateCurveVertexCountsAttr(defaultValue, writeSparsely)
  }

  public func getWidthsAttr() -> Usd.Attribute
  {
    GetWidthsAttr()
  }

  @discardableResult
  public func createWidthsAttr(_ defaultValue: Vt.Value = Vt.Value(),
                               writeSparsely: Bool = false) -> Usd.Attribute
  {
    CreateWidthsAttr(defaultValue, writeSparsely)
  }

  public func getWidthsInterpolation() -> Tf.Token
  {
    GetWidthsInterpolation()
  }

  @discardableResult
  public mutating func setWidthsInterpolation(_ interpolation: Tf.Token) -> Bool
  {
    SetWidthsInterpolation(interpolation)
  }

  public static func computeExtent(points: Vt.Vec3fArray,
                                   widths: Vt.FloatArray,
                                   extent: inout Vt.Vec3fArray) -> Bool
  {
    UsdGeom.Curves.ComputeExtent(points, widths, &extent)
  }

  public static func computeExtent(points: Vt.Vec3fArray,
                                   widths: Vt.FloatArray,
                                   transform: Gf.Matrix4d,
                                   extent: inout Vt.Vec3fArray) -> Bool
  {
    UsdGeom.Curves.ComputeExtent(points, widths, transform, &extent)
  }

  public func getCurveCount(timeCode: Usd.TimeCode = Usd.TimeCode.Default()) -> Int

  {
    Int(GetCurveCount(timeCode))
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
