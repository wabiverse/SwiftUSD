/* --------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                          ::
 * --------------------------------------------------------------
 * This program is free software; you can redistribute it, and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Check out
 * the GNU General Public License for more details.
 *
 * You should have received a copy for this software license, the
 * GNU General Public License along with this program; or, if not
 * write to the Free Software Foundation, Inc., to the address of
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import Foundation
import Pixar

@main
enum Creator
{
  static func main()
  {
    /* Setup all usd resources (python, plugins, resources). */

    Pixar.Bundle.shared.setup(.resources)

    /* Create a new USD stage with a sphere, capsule, cylinder, cube, and cone. */

    let stage = Pixar.Usd.Stage.createNew("HelloPixarUSD.usda")

    let xformMain = Pixar.UsdGeom.Xform.define(stage, path: "/Main")
    xformMain.addXformOp(type: .translate).set(Pixar.GfVec3d(0.0, 1.0, 0.0))
    xformMain.addXformOp(type: .scale, precision: .float).set(Pixar.GfVec3f(5, 5, 5))

    let stageLeft = Pixar.UsdGeom.Xform.define(stage, path: "/Main/StageLeft")
    stageLeft.addXformOp(type: .translate).set(Pixar.GfVec3d(0.0, 0.0, -5.0))

    let stageUberLeft = Pixar.UsdGeom.Xform.define(stage, path: "/Main/StageUberLeft")
    stageUberLeft.addXformOp(type: .translate).set(Pixar.GfVec3d(0.0, 0.0, -10.0))
    stageUberLeft.addXformOp(type: .rotateX, precision: .float).set(-90)

    let stageRight = Pixar.UsdGeom.Xform.define(stage, path: "/Main/StageRight")
    stageRight.addXformOp(type: .translate).set(Pixar.GfVec3d(0.0, 0.0, 5.0))

    let stageUberRight = Pixar.UsdGeom.Xform.define(stage, path: "/Main/StageUberRight")
    stageUberRight.addXformOp(type: .translate).set(Pixar.GfVec3d(0.0, 0.0, 10.0))
    stageUberRight.addXformOp(type: .rotateX, precision: .float).set(-90)

    Pixar.UsdGeom.Sphere.define(stage, path: "/Main/StageLeft/Sphere")
    Pixar.UsdGeom.Capsule.define(stage, path: "/Main/StageUberLeft/Capsule")
    Pixar.UsdGeom.Cylinder.define(stage, path: "/Main/Cylinder")
    Pixar.UsdGeom.Cube.define(stage, path: "/Main/StageRight/Cube")
    Pixar.UsdGeom.Cone.define(stage, path: "/Main/StageUberRight/Cone")

    stage.getPseudoRoot().set(doc: "SwiftUSD v23.11.11")

    stage.save()

    print("'usdview' does nothing... will exit now.")
  }
}
