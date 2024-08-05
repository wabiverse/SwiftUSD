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

public typealias UsdGeomXformOp = Pixar.UsdGeomXformOp

public extension UsdGeom
{
  typealias XformOp = UsdGeomXformOp
}

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
