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
    private var viewCamera: Hydra.Camera

    private var worldCenter: Pixar.GfVec3d = .init(0.0, 0.0, 0.0)
    private var worldSize: Double = 1.0

    private var material = Pixar.GlfSimpleMaterial()
    private var sceneAmbient = Pixar.GfVec4f(0.01, 0.01, 0.01, 1.0)

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
      engine.setRendererAov(.color)

      viewCamera = Hydra.Camera(isZUp: Hydra.RenderEngine.isZUp(for: stage))
      setupCamera()
      setupMaterial()
    }

    public func render(at timeCode: Double, viewSize: CGSize) -> Pixar.HgiTextureHandle
    {
      // draws the scene using hydra.
      let cameraTransform = viewCamera.getTransform()
      let cameraParams = viewCamera.getShaderParams()
      let frustum = computeFrustum(cameraTransform: cameraTransform, viewSize: viewSize, cameraParams: cameraParams)
      let viewMatrix = frustum.computeViewMatrix()
      let projMatrix = frustum.computeProjectionMatrix()
      engine.setCameraState(modelViewMatrix: viewMatrix, projectionMatrix: projMatrix)

      // viewport setup.
      let viewport = Gf.Vec4d(0, 0, viewSize.width, viewSize.height)
      engine.setRenderViewport(viewport)
      engine.setWindowPolicy(.matchHorizontally)

      // light and material setup.
      let lights = computeLights(cameraTransform: cameraTransform)
      engine.setLightingState(lights: lights.getLights(), material: material, sceneAmbient: sceneAmbient)

      var params = UsdImagingGL.RenderParams()
      params.frame = Usd.TimeCode(timeCode)
      params.clearColor = .init(0.0, 0.0, 0.0, 0.0)
      params.colorCorrectionMode = .sRGB
      params.enableIdRender = false
      params.showGuides = true
      params.showRender = true
      params.showProxy = true

      // render the frame.
      engine.render(rootPrim: stage.getPseudoRoot(), params: params)

      // return the color output.
      return engine.getAovTexture(.color)
    }

    public func setupCamera()
    {
      calculateOriginAndSize()

      viewCamera.params.rotation = .init(0.0, 0.0, 0.0)
      viewCamera.params.focus = worldCenter
      viewCamera.params.distance = worldSize

      if worldSize <= 16.0
      {
        viewCamera.scaleBias = 1.0
      }
      else
      {
        viewCamera.scaleBias = log2(worldSize / 16.0 * 1.8) / log2(1.8)
      }

      viewCamera.params.focalLength = 18.0
      viewCamera.standardFocalLength = 18.0
    }

    /// creates a light source located at the camera position.
    func computeCameraLight(cameraTransform: Gf.Matrix4d) -> Pixar.GlfSimpleLight
    {
      let cameraPosition = Pixar.GfVec3f(cameraTransform.ExtractTranslation())

      var light = Pixar.GlfSimpleLight(.init(0.0, 0.0, 0.0, 1.0))
      light.SetPosition(Pixar.GfVec4f(cameraPosition[0], cameraPosition[1], cameraPosition[2], 1))

      return light
    }

    func computeLights(cameraTransform: Gf.Matrix4d) -> Pixar.GlfSimpleLightCollector
    {
      var lights = Pixar.GlfSimpleLightCollector()
      lights.addLight(computeCameraLight(cameraTransform: cameraTransform))

      return lights
    }

    func setupMaterial()
    {
      let kA = Float(0.2)
      let kS = Float(0.1)

      material.SetAmbient(Pixar.GfVec4f(kA, kA, kA, 1.0))
      material.SetSpecular(Pixar.GfVec4f(kS, kS, kS, 1.0))
      material.SetShininess(Double(32.0))

      sceneAmbient = Pixar.GfVec4f(Float(0.01), Float(0.01), Float(0.01), Float(1.0))
    }

    public func calculateOriginAndSize()
    {
      var bboxCache = computeBBoxCache()

      var bbox = bboxCache.ComputeWorldBound(stage.getPseudoRoot())

      if bbox.GetRange().pointee.IsEmpty() || isInfiniteBBox(bbox)
      {
        bbox = Pixar.GfBBox3d(.init(.init(-10, -10, -10), .init(10, 10, 10)))
      }

      let world = bbox.ComputeAlignedRange()

      worldCenter = (world.GetMin().pointee + world.GetMax().pointee) / 2.0
      worldSize = world.GetSize().GetLength()
    }

    func isInfiniteBBox(_ bbox: Pixar.GfBBox3d) -> Bool
    {
      Double(bbox.GetRange().pointee.GetMin().pointee.GetLength()).isInfinite ||
        Double(bbox.GetRange().pointee.GetMax().pointee.GetLength()).isInfinite
    }

    func computeBBoxCache() -> Pixar.UsdGeomBBoxCache
    {
      var purposes = Pixar.TfTokenVector()
      purposes.push_back(UsdGeom.Tokens.default_.token)
      purposes.push_back(UsdGeom.Tokens.proxy.token)

      let useExtentHints = true
      var timeCode = UsdTimeCode.Default()
      if stage.pointee.HasAuthoredTimeCodeRange()
      {
        timeCode = UsdTimeCode(stage.pointee.GetStartTimeCode())
      }

      let bboxCache = Pixar.UsdGeomBBoxCache(timeCode, purposes, useExtentHints, false)
      return bboxCache
    }

    public func computeFrustum(cameraTransform: Gf.Matrix4d, viewSize: CGSize, cameraParams: Hydra.Camera.Params) -> Gf.Frustum
    {
      var camera = Pixar.GfCamera(
        .init(1.0),
        .init(0),
        0.825 * 2.54 / 0.1,
        0.602 * 2.54 / 0.1,
        0.0,
        0.0,
        50.0,
        .init(1, 1_000_000),
        .init(),
        0.0,
        0.0
      )
      camera.SetTransform(cameraTransform)
      var frustum = camera.GetFrustum()
      camera.SetFocalLength(Float(cameraParams.focalLength))

      if cameraParams.projection.rawValue == 0
      {
        let targetAspect = Double(viewSize.width) / Double(viewSize.height)
        let filmbackWidthMM = 24.0
        let hFOVInRadians = 2.0 * atan(0.5 * filmbackWidthMM / cameraParams.focalLength)
        let fov = (180.0 * hFOVInRadians) / Double.pi
        frustum.SetPerspective(fov, targetAspect, 1.0, 100_000.0)
      }
      else
      {
        let left = cameraParams.leftBottomNear[0] * cameraParams.scaleViewport
        let right = cameraParams.rightTopFar[0] * cameraParams.scaleViewport
        let bottom = cameraParams.leftBottomNear[1] * cameraParams.scaleViewport
        let top = cameraParams.rightTopFar[1] * cameraParams.scaleViewport
        let nearPlane = cameraParams.leftBottomNear[2]
        let farPlane = cameraParams.rightTopFar[2]
        frustum.SetOrthographic(left, right, bottom, top, nearPlane, farPlane)
      }

      return frustum
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

    static func isZUp(for stage: UsdStageRefPtr) -> Bool
    {
      Pixar.UsdGeomGetStageUpAxis(stage.pointee.getPtr()) == UsdGeom.Tokens.z.token
    }
  }
}
