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

#if canImport(Metal) && !os(visionOS)
  import Metal
  import MetalKit
#endif // canImport(Metal) && !os(visionOS)

public enum Hydra
{
  public class RenderEngine
  {
    public var stage: UsdStageRefPtr

    private let hgi: Pixar.HgiMetalPtr
    private let engine: UsdImagingGL.EngineSharedPtr

    public required init(stage: UsdStageRefPtr)
    {
      self.stage = stage

      hgi = HgiMetal.createHgi()
      let driver = HdDriver(name: .renderDriver, driver: hgi.value)

      engine = UsdImagingGL.Engine.createEngine(
        rootPath: stage.getPseudoRoot().getPath(),
        excludedPaths: Sdf.PathVector(),
        invisedPaths: Sdf.PathVector(),
        sceneDelegateId: Sdf.Path.absoluteRootPath(),
        driver: driver
      )

      engine.setEnablePresentation(false)
      engine.setRenderer(aov: .color)
    }

    public func render(at timeCode: Double, viewSize: CGSize) -> Pixar.HgiTextureHandle
    {
      // Draws the scene using Hydra.
      // Camera projection setup.
      // let cameraTransform = viewCamera.getTransform()
      // let cameraParams = viewCamera.getShaderParams()
      // let frustum = computeFrustum(cameraTransform: cameraTransform, viewSize: viewSize, params: cameraParams)
      // let modelViewMatrix = frustum.computeViewMatrix()
      // let projMatrix = frustum.computeProjectionMatrix()
      // engine.setCameraState(modelViewMatrix: modelViewMatrix, projMatrix: projMatrix)

      // Viewport setup.
      let viewport = Gf.Vec4d(0, 0, viewSize.width, viewSize.height)
      engine.pointee.SetRenderViewport(viewport)
      engine.pointee.SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(0))

      var params = UsdImagingGL.RenderParams()
      params.frame = Usd.TimeCode(timeCode)
      params.clearColor = .init(Float(0.2), Float(0.2), Float(0.2), Float(1.0))
      params.enableIdRender = false
      params.showGuides = true
      params.showRender = true
      params.showProxy = true

      // Light and material setup.
      // let lights = computeLights(cameraTransform: cameraTransform)
      // engine.setLightingState(lights: lights, material: material, sceneAmbient: sceneAmbient)

      // Render the frame.
      engine.render(root: stage.getPseudoRoot(), params: params)

      // Return the color output.
      return engine.pointee.GetAovTexture(Hd.AovTokens.color.token)
    }

    public var hydraDevice: MTLDevice
    {
      hgi.device
    }

    public func getHgi() -> Pixar.HgiMetalPtr
    {
      hgi
    }

    public func getEngine() -> UsdImagingGL.EngineSharedPtr
    {
      engine
    }
  }
}
