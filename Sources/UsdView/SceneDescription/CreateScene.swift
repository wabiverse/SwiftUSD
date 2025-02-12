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

import Foundation
import PixarUSD

extension UsdView
{
  /**
   * Create a stage with a sphere, capsule, cylinder, cube
   * and cone on a transform, create a different colored
   * material for each geometry prim, iterate the stage and
   * print out the path to each prim, and finally save the
   * stage to disk. */
  func createScene()
  {
    /* Create stage with a sphere, capsule, cylinder, cube, and cone on a transform. */

    let xform = UsdGeom.Xform.define(stage, path: "/Geometry")
    xform.addXformOp(type: .translate).set(GfVec3d(0.0, 5.0, 0.0))
    xform.addXformOp(type: .scale, precision: .float).set(GfVec3f(5, 5, 5))

    let sphere = UsdGeom.Sphere.define(stage, path: "/Geometry/Sphere")
    sphere.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -5.0))

    let capsule = UsdGeom.Capsule.define(stage, path: "/Geometry/Capsule")
    capsule.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -10.0))
    capsule.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    let cylinder = UsdGeom.Cylinder.define(stage, path: "/Geometry/Cylinder")
    cylinder.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    let cube = UsdGeom.Cube.define(stage, path: "/Geometry/Cube")
    cube.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 5.0))

    let cone = UsdGeom.Cone.define(stage, path: "/Geometry/Cone")
    cone.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 10.0))
    cone.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    /* Create a different colored material for each geometry prim. */

    UsdShade.MaterialBindingAPI.apply(sphere).bind(matDef(stage, color: .red))
    UsdShade.MaterialBindingAPI.apply(capsule).bind(matDef(stage, color: .yellow))
    UsdShade.MaterialBindingAPI.apply(cylinder).bind(matDef(stage, color: .green))
    UsdShade.MaterialBindingAPI.apply(cube).bind(matDef(stage, color: .blue))
    UsdShade.MaterialBindingAPI.apply(cone).bind(matDef(stage, color: .purple))

    stage.getPseudoRoot().set(doc: "SwiftUSD v\(Pixar.version)")

    /* Iterate the stage and print out the path to each prim. */

    for prim in stage.traverse()
    {
      let primType = !prim.typeName.isEmpty ? "(\(prim.typeName.string))" : ""
      Msg.logger.log(level: .info, "\(prim.name.string)\(primType) -> \(prim.path.string)")
    }

    /* Save the stage to disk. */

    stage.save()
  }
}
