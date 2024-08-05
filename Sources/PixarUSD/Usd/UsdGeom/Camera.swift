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

public typealias UsdGeomCamera = Pixar.UsdGeomCamera

public extension UsdGeom
{
  typealias Camera = UsdGeomCamera
}

@Xformable
extension UsdGeom.Camera: GeomXformable
{
  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdGeom.Camera
  {
    UsdGeom.Camera.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdGeom.Camera
  {
    UsdGeom.Camera.define(stage, path: .init(path))
  }
}
