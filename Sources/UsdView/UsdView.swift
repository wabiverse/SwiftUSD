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
    xformMain.addXformOp(type: .translate).set(GfVec3d(0.0, 1.0, 0.0))
    xformMain.addXformOp(type: .scale, precision: .float).set(GfVec3f(5, 5, 5))

    let sphere = Pixar.UsdGeom.Sphere.define(stage, path: "/Main/Sphere")
    sphere.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -5.0))

    let capsule = Pixar.UsdGeom.Capsule.define(stage, path: "/Main/Capsule")
    capsule.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -10.0))
    capsule.addXformOp(type: .rotateX, precision: .float).set(-90)

    let cylinder = Pixar.UsdGeom.Cylinder.define(stage, path: "/Main/Cylinder")
    cylinder.addXformOp(type: .rotateX, precision: .float).set(-90)

    let cube = Pixar.UsdGeom.Cube.define(stage, path: "/Main/Cube")
    cube.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 5.0))

    let cone = Pixar.UsdGeom.Cone.define(stage, path: "/Main/Cone")
    cone.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 10.0))
    cone.addXformOp(type: .rotateX, precision: .float).set(-90)

    stage.getPseudoRoot().set(doc: "SwiftUSD v23.11.12")

    stage.save()

    print("'usdview' does nothing... will exit now.")
  }
}
