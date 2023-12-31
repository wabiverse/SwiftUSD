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

    /* Create stage with a sphere, capsule, cylinder, cube, and cone on a transform. */

    let stage = Pixar.Usd.Stage.createNew("HelloPixarUSD.usda")

    let xform = Pixar.UsdGeom.Xform.define(stage, path: "/Geometry")
    xform.addXformOp(type: .translate).set(GfVec3d(0.0, 5.0, 0.0))
    xform.addXformOp(type: .scale, precision: .float).set(GfVec3f(5, 5, 5))

    let sphere = Pixar.UsdGeom.Sphere.define(stage, path: "/Geometry/Sphere")
    sphere.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -5.0))

    let capsule = Pixar.UsdGeom.Capsule.define(stage, path: "/Geometry/Capsule")
    capsule.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -10.0))
    capsule.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    let cylinder = Pixar.UsdGeom.Cylinder.define(stage, path: "/Geometry/Cylinder")
    cylinder.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    let cube = Pixar.UsdGeom.Cube.define(stage, path: "/Geometry/Cube")
    cube.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 5.0))

    let cone = Pixar.UsdGeom.Cone.define(stage, path: "/Geometry/Cone")
    cone.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, 10.0))
    cone.addXformOp(type: .rotateX, precision: .float).set(Float(-90))

    /* Create material with a surface shader and bind it to all geometry. */

    let material = Pixar.UsdShade.Material.define(stage, path: "/Materials/Material")

    var pbrShader = Pixar.UsdShadeShader.define(stage, path: "/Materials/Material/PBRShader")
    pbrShader.createIdAttr("UsdPreviewSurface")
    pbrShader.createInput(for: .roughness, type: .float).set(Float(0.4))
    pbrShader.createInput(for: .metallic, type: .float).set(Float(0.0))
    material.createSurfaceOutput().connectTo(source: pbrShader.connectableAPI(), at: .surface)

    Pixar.UsdShade.MaterialBindingAPI.apply(sphere).bind(material)
    Pixar.UsdShade.MaterialBindingAPI.apply(capsule).bind(material)
    Pixar.UsdShade.MaterialBindingAPI.apply(cylinder).bind(material)
    Pixar.UsdShade.MaterialBindingAPI.apply(cube).bind(material)
    Pixar.UsdShade.MaterialBindingAPI.apply(cone).bind(material)

    stage.getPseudoRoot().set(doc: "SwiftUSD v23.11.13")

    stage.save()

    print("'usdview' not yet implemented... will exit now.")
  }
}
