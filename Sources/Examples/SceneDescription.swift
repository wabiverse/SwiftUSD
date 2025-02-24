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

func createScene()
{
  /* Create stage with a sphere on a transform. */

  let stage = Usd.Stage.createNew("\(documentsDirPath())/HelloWorldExample", ext: .usd)

  let xform = UsdGeom.Xform.define(stage, path: "/Geometry")
  xform.addXformOp(type: .translate).set(GfVec3d(0.0, 5.0, 0.0))
  xform.addXformOp(type: .scale, precision: .float).set(GfVec3f(5, 5, 5))

  let sphere = UsdGeom.Sphere.define(stage, path: "/Geometry/Sphere")
  sphere.addXformOp(type: .translate).set(GfVec3d(0.0, 0.0, -5.0))

  /* Create a colored material for the sphere prim. */

  UsdShade.MaterialBindingAPI.apply(sphere).bind(matDef(stage, color: .red))

  /* Iterate the stage and print out the path to each prim. */

  for prim in stage.traverse()
  {
    let primType = !prim.typeName.isEmpty ? "(\(prim.typeName.string))" : ""
    Msg.logger.log(level: .info, "\(prim.name.string)\(primType) -> \(prim.path.string)")
  }

  /* Save the stage to disk. */

  stage.getPseudoRoot().set(doc: "SwiftUSD v\(Pixar.version)")
  stage.save()
}

public enum ShadeColor: String, CaseIterable
{
  case red
  case orange
  case yellow
  case green
  case blue
  case purple
  case white
  case black

  public var vec3f: GfVec3f
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
public func matDef(_ stage: UsdStageRefPtr, color: ShadeColor = ShadeColor.white) -> UsdShade.Material
{
  let matName = "\(color.rawValue.capitalized)Material"

  let material = UsdShade.Material.define(stage, path: "/Materials/\(matName)")

  var pbrShader = UsdShade.Shader.define(stage, path: "/Materials/\(matName)/PBRShader")
  pbrShader.createIdAttr(.usdPreviewSurface)
  pbrShader.createInput(for: .diffuseColor, type: .color3f).set(color.vec3f)
  pbrShader.createInput(for: .roughness, type: .float).set(Float(0.4))
  pbrShader.createInput(for: .metallic, type: .float).set(Float(0.0))
  material.createSurfaceOutput().connectTo(source: pbrShader.connectableAPI(), at: .surface)

  return material
}

public enum SceneDescriptionExamples
{
  static func run()
  {
    Msg.logger.info("running scene description examples...")

    createScene()

    Msg.logger.info("scene description examples complete.")
  }
}
