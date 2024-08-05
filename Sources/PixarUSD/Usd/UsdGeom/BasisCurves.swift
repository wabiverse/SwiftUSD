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

public typealias UsdGeomBasisCurves = Pixar.UsdGeomBasisCurves

public extension UsdGeom
{
  typealias BasisCurves = UsdGeomBasisCurves
}

public extension UsdGeom.BasisCurves
{
  @discardableResult
  static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdGeom.BasisCurves
  {
    UsdGeom.BasisCurves.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdGeom.BasisCurves
  {
    UsdGeom.BasisCurves.define(stage, path: .init(path))
  }
}
