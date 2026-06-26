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

#if canImport(UsdGeom)
  import UsdGeom
#else
  import OpenUSD
#endif

public typealias UsdGeomXformOp = Pixar.UsdGeomXformOp

public extension UsdGeom
{
  typealias XformOp = UsdGeomXformOp
}

#if !canImport(UsdGeom)
extension UsdGeomXformOp.`Type`
{
  public static let invalid    = TypeInvalid
  public static let translateX = TypeTranslateX
  public static let translateY = TypeTranslateY
  public static let translateZ = TypeTranslateZ
  public static let translate  = TypeTranslate
  public static let scaleX     = TypeScaleX
  public static let scaleY     = TypeScaleY
  public static let scaleZ     = TypeScaleZ
  public static let scale      = TypeScale
  public static let rotateX    = TypeRotateX
  public static let rotateY    = TypeRotateY
  public static let rotateZ    = TypeRotateZ
  public static let rotateXYZ  = TypeRotateXYZ
  public static let rotateXZY  = TypeRotateXZY
  public static let rotateYXZ  = TypeRotateYXZ
  public static let rotateYZX  = TypeRotateYZX
  public static let rotateZXY  = TypeRotateZXY
  public static let rotateZYX  = TypeRotateZYX
  public static let orient     = TypeOrient
  public static let transform  = TypeTransform
}

extension UsdGeomXformOp.Precision
{
  public static let double = UsdGeomXformOp.Precision(rawValue: 0)
  public static let float = UsdGeomXformOp.Precision(rawValue: 1)
  public static let half = UsdGeomXformOp.Precision(rawValue: 2)
}
#endif

public extension UsdGeom.XformOp
{
  @discardableResult
  func set(_ value: Float, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }

  @discardableResult
  func set(_ value: Double, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }

  @discardableResult
  func set(_ value: GfVec2f, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }

  @discardableResult
  func set(_ value: GfVec2d, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }

  @discardableResult
  func set(_ value: GfVec3f, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }

  @discardableResult
  func set(_ value: GfVec3d, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }
}
