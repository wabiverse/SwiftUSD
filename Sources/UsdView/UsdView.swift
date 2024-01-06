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
 *       Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
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

    /* ----- Imperative api example. ----- */

    /* Create stage with a sphere, capsule, cylinder, cube, and cone on a transform. */

    let stage = Pixar.Usd.Stage.createNew("HelloPixarUSD", ext: .usda)

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

    /* Create a different colored material for each geometry prim. */

    Pixar.UsdShade.MaterialBindingAPI.apply(sphere).bind(matDef(stage, color: .red))
    Pixar.UsdShade.MaterialBindingAPI.apply(capsule).bind(matDef(stage, color: .yellow))
    Pixar.UsdShade.MaterialBindingAPI.apply(cylinder).bind(matDef(stage, color: .green))
    Pixar.UsdShade.MaterialBindingAPI.apply(cube).bind(matDef(stage, color: .blue))
    Pixar.UsdShade.MaterialBindingAPI.apply(cone).bind(matDef(stage, color: .purple))

    stage.getPseudoRoot().set(doc: "SwiftUSD v\(Pixar.version)")

    /* Iterate the stage and print out the path to each prim. */

    for prim in stage.scene
    {
      Msg.Log.point("\(prim.name.string)\(!prim.typeName.isEmpty ? "(\(prim.typeName.string))" : "")", to: prim.path.string)
    }

    /* Save the stage to disk. */

    stage.save()

    /* ----- Declarative api example. ----- */

    UsdStage("DeclarativePixarUSD", ext: .usda)
    {
      UsdPrim("Hello")
      {
        UsdPrim("Declarative")
        {
          UsdPrim("Scene")
          {
            UsdPrim("Description")
            {}
          }
        }
      }
    }
    .set(doc: "SwiftUSD v\(Pixar.version) | Declarative API")
    .save()

    /* ------------------------------------ */

    print("'usdview' not yet implemented... will exit now.")

    /* ------------------------------------ */
  }
}

enum MaterialColor: String, CaseIterable
{
  case red
  case orange
  case yellow
  case green
  case blue
  case purple
  case white
  case black

  var vec3f: GfVec3f
  {
    switch self
    {
      case .red: GfVec3f(0.992, 0.207, 0.061)
      case .orange: GfVec3f(0.922, 0.501, 0.0)
      case .yellow: GfVec3f(0.950, 0.800, 0.0)
      case .green: GfVec3f(0.0, 0.766, 0.014)
      case .blue: GfVec3f(0.132, 0.218, 0.932)
      case .purple: GfVec3f(0.531, 0.122, 0.922)
      case .white: GfVec3f(0.8, 0.8, 0.8)
      case .black: GfVec3f(0.2, 0.2, 0.2)
    }
  }
}

/**
 * Create a material with a surface shader.
 *
 * - Parameter stage: The stage to create the material on.
 * - Parameter color: The diffuse color to set on the shader.
 * - Returns: The newly created material.
 */
func matDef(_ stage: StageRefPtr, color: MaterialColor = .white) -> Pixar.UsdShade.Material
{
  let matName = "\(color.rawValue.capitalized)Material"

  let material = Pixar.UsdShade.Material.define(stage, path: "/Materials/\(matName)")

  var pbrShader = Pixar.UsdShadeShader.define(stage, path: "/Materials/\(matName)/PBRShader")
  pbrShader.createIdAttr(.usdPreviewSurface)
  pbrShader.createInput(for: .diffuseColor, type: .color3f).set(color.vec3f)
  pbrShader.createInput(for: .roughness, type: .float).set(Float(0.4))
  pbrShader.createInput(for: .metallic, type: .float).set(Float(0.0))
  material.createSurfaceOutput().connectTo(source: pbrShader.connectableAPI(), at: .surface)

  return material
}
