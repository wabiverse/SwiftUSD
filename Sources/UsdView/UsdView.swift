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
#if canImport(PyBundle)
  import PyBundle
#endif /* canImport(PyBundle) */
#if canImport(Metal)
  import Metal
#endif /* canImport(Metal) */
#if canImport(SwiftUI)
  import SwiftUI

  public protocol PixarApp: App
  {}
#else /* canImport(SwiftUI) */
  public protocol PixarApp
  {}
#endif /* canImport(SwiftUI) */

/**
 * ``UsdView``
 *
 * ## Overview
 *
 * A ``UsdView`` application written in Swift for
 * the purposes of demonstrating the usage of USD,
 * from the Swift programming language. */
@main
struct UsdView: PixarApp
{
  #if canImport(Metal) && !os(visionOS)
    let hydra: Hydra.MTLRenderer
  #endif /* canImport(Metal) && !os(visionOS) */

  public init()
  {
    /* Setup all usd resources (python, plugins, resources). */
    #if os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
      Pixar.Bundler.shared.setup(.resources, installPlugins: true)
    #else
      Pixar.Bundler.shared.setup(.resources, installPlugins: false)
    #endif

    #if canImport(PyBundle) && DEBUG
      /*
        embed & init python.
        TODO: for some reason python
        crashes release builds, figure
        out why (its likely improper
        resource bundle paths).
      */
      PyBundler.shared.pyInit()
      PyBundler.shared.pyInfo()
    #endif /* canImport(PyBundle) */

    #if canImport(Metal) && !os(visionOS)
      hydra = Hydra.MTLRenderer(device: MTLCreateSystemDefaultDevice()!)!
    #endif /* canImport(Metal) && !os(visionOS) */

    #if canImport(SwiftUI)
      runDemo(with: self)
    #endif /* canImport(SwiftUI) */
  }

  #if canImport(SwiftUI)
    var body: some Scene
    {
      WindowGroup("UsdView", id: "usdview")
      {
        VStack
        {
          Text("UsdView Under Construction...")
            .font(.system(size: 24, weight: .black))
            .padding()
        }
      }
    }
  #else /* canImport(SwiftUI) */
    static func main()
    {
      let app = UsdView()

      app.runDemo(with: app)
    }
  #endif /* canImport(SwiftUI) */

  func runDemo(with app: Self)
  {
    /* ---------- Hydra Engine. ---------- */

    #if canImport(Metal) && !os(visionOS)

      app.hydra.info()

    #endif /* canImport(Metal) && !os(visionOS) */

    /* ----- Imperative api example. ----- */

    /* Create stage with a sphere, capsule, cylinder, cube, and cone on a transform. */

    let stage = Usd.Stage.createNew("\(documentsDirPath())/HelloPixarUSD", ext: .usda)

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

    /* ----- Declarative api example. ----- */

    USDStage("\(documentsDirPath())/DeclarativePixarUSD", ext: .usda)
    {
      USDPrim("DeclarativeScene")
      {
        USDPrim("Sun", type: .distantLight)
        {
          USDPrim("Hello", type: .xform)
          {
            USDPrim("World", type: .sphere)
            USDPrim("Box", type: .cube)
          }

          USDPrim("RandomCone", type: .cone)
        }
      }
    }
    .set(doc: "SwiftUSD v\(Pixar.version) | Declarative API")
    .save()

    /* ------------------------------------ */

    Msg.logger.log(level: .info, "UsdView launched | USD v\(Pixar.version).")

    /* ------------------------------------ */
  }
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

public func documentsDirPath() -> String
{
  #if os(macOS) || os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
    let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
    return paths[0].path
  #else
    return "."
  #endif
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
