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

public typealias UsdGeomPoints = Pixar.UsdGeomPoints

public extension UsdGeom
{
  typealias Points = UsdGeomPoints
}

public extension UsdGeom.Points
{
  @discardableResult
  static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdGeom.Points
  {
    UsdGeom.Points.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdGeom.Points
  {
    UsdGeom.Points.define(stage, path: .init(path))
  }
}
