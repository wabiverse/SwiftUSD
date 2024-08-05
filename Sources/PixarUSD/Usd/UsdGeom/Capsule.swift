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

public typealias UsdGeomCapsule = Pixar.UsdGeomCapsule

public extension UsdGeom
{
  typealias Capsule = UsdGeomCapsule
}

@Xformable
extension UsdGeom.Capsule: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStageRefPtr, path: Sdf.Path) -> UsdGeom.Capsule
  {
    UsdGeom.Capsule.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStageRefPtr, path: String) -> UsdGeom.Capsule
  {
    UsdGeom.Capsule.define(stage, path: .init(path))
  }
}
