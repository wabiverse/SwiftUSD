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

public typealias UsdGeomSubset = Pixar.UsdGeomSubset

public extension UsdGeom
{
  typealias Subset = UsdGeomSubset
}

public extension UsdGeom.Subset
{
  @discardableResult
  static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdGeom.Subset
  {
    UsdGeom.Subset.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  static func define(_ stage: UsdStage, path: String) -> UsdGeom.Subset
  {
    UsdGeom.Subset.define(stage, path: .init(path))
  }
}
