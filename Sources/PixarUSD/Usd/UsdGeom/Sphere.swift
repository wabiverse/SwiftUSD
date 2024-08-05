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

public typealias UsdGeomSphere = Pixar.UsdGeomSphere

public extension UsdGeom
{
  typealias Sphere = UsdGeomSphere
}

@Xformable
extension UsdGeom.Sphere: GeomXformable
{
  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: Sdf.Path) -> UsdGeom.Sphere
  {
    UsdGeom.Sphere.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  public static func define(_ stage: Usd.StageRefPtr, path: String) -> UsdGeom.Sphere
  {
    UsdGeom.Sphere.define(stage, path: .init(path))
  }
}
