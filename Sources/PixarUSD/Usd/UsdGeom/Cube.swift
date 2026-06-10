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

public typealias UsdGeomCube = Pixar.UsdGeomCube

public extension UsdGeom
{
  typealias Cube = UsdGeomCube
}

@Xformable
extension UsdGeom.Cube: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdGeom.Cube
  {
    UsdGeom.Cube.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStage, path: String) -> UsdGeom.Cube
  {
    UsdGeom.Cube.define(stage, path: .init(path))
  }
}
