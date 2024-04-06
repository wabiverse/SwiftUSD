/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
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

@Xformable
extension UsdGeom.Curves: GeomXformable
{
  public static func get(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdGeom.Curves
  {
    UsdGeom.Curves.Get(stage.pointee.getPtr(), path)
  }

  public static func get(_ stage: Usd.StageRefPtr, path: String) -> UsdGeom.Curves
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
}
