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

public typealias UsdGeomXform = Pixar.UsdGeomXform

public extension UsdGeom
{
  typealias Xform = UsdGeomXform
}

@Xformable
extension UsdGeom.Xform: GeomXformable
{
  @discardableResult
  public static func define(_ stage: UsdStage, path: Sdf.Path) -> UsdGeom.Xform
  {
    UsdGeom.Xform.Define(Overlay.TfWeakPtr(stage), path)
  }

  @discardableResult
  public static func define(_ stage: UsdStage, path: String) -> UsdGeom.Xform
  {
    UsdGeom.Xform.define(stage, path: .init(path))
  }
}
