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

#if canImport(UsdImagingGL)
  import UsdImagingGL

  public typealias UsdImagingGLEngine = Pixar.UsdImagingGLEngine
  public typealias UsdImagingGLEngineSharedPtr = Pixar.UsdImagingGLEngineSharedPtr

  public enum UsdImagingGL
  {
    public typealias Engine = UsdImagingGLEngine
    public typealias EngineSharedPtr = UsdImagingGLEngineSharedPtr
  }

  public extension UsdImagingGL.Engine
  {
    static func createEngine() -> UsdImagingGL.EngineSharedPtr
    {
      UsdImagingGL.Engine.CreateEngine()
    }

    static func createEngine(params: Parameters) -> UsdImagingGL.EngineSharedPtr
    {
      UsdImagingGL.Engine.CreateEngine(params)
    }

    static func createEngine(driver: HdDriver = HdDriver(name: Tf.Token(), driver: VtValue()),
                             rendererPluginId: Tf.Token = Tf.Token(),
                             gpuEnabled: Bool = true) -> UsdImagingGL.EngineSharedPtr
    {
      UsdImagingGL.Engine.CreateEngine(driver, rendererPluginId, gpuEnabled)
    }

    static func createEngine(rootPath: Sdf.Path,
                             excludedPaths: Sdf.PathVector,
                             invisedPaths: Sdf.PathVector = Sdf.PathVector(),
                             sceneDelegateId: Sdf.Path = Sdf.Path.absoluteRootPath(),
                             driver: HdDriver = HdDriver(name: Tf.Token(), driver: VtValue()),
                             rendererPluginId: Tf.Token = Tf.Token(),
                             gpuEnabled: Bool = true,
                             displayUnloadedPrimsWithBounds: Bool = false,
                             allowAsynchronousSceneProcessing: Bool = false) -> UsdImagingGL.EngineSharedPtr
    {
      UsdImagingGL.Engine.CreateEngine(
        rootPath,
        excludedPaths,
        invisedPaths,
        sceneDelegateId,
        driver,
        rendererPluginId,
        gpuEnabled,
        displayUnloadedPrimsWithBounds,
        allowAsynchronousSceneProcessing
      )
    }

    func setEnablePresentation(_ value: Bool)
    {
      SetEnablePresentation(value)
    }

    func setRendererAov(_ aovName: Hd.AovTokens)
    {
      SetRendererAov(aovName.token)
    }

    func render(rootPrim: Usd.Prim, params: UsdImagingGL.RenderParams)
    {
      Render(rootPrim, params)
    }

    func setCameraState(modelViewMatrix: Gf.Matrix4d, projectionMatrix: Gf.Matrix4d)
    {
      SetCameraState(modelViewMatrix, projectionMatrix)
    }

    func setRenderViewport(_ viewport: Gf.Vec4d)
    {
      SetRenderViewport(viewport)
    }

    enum CameraUtilWindowConformPolicy
    {
      case matchVertically
      case matchHorizontally
      case fit
      case crop
      case dontConform
    }

    func setWindowPolicy(_ policy: CameraUtilWindowConformPolicy)
    {
      switch policy
      {
        case .matchVertically: SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(0))
        case .matchHorizontally: SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(1))
        case .fit: SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(2))
        case .crop: SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(3))
        case .dontConform: SetWindowPolicy(Pixar.CameraUtilConformWindowPolicy(4))
      }
    }

    func setLightingState(lights: Pixar.GlfSimpleLightVector, material: Pixar.GlfSimpleMaterial, sceneAmbient: Pixar.GfVec4f)
    {
      SetLightingState(lights, material, sceneAmbient)
    }

    func getAovTexture(_ aovName: Hd.AovTokens) -> Pixar.HgiTextureHandle
    {
      GetAovTexture(aovName.token)
    }
  }

  public extension UsdImagingGL.EngineSharedPtr
  {
    func setEnablePresentation(_ value: Bool)
    {
      pointee.setEnablePresentation(value)
    }

    func setRendererAov(_ aovName: Hd.AovTokens)
    {
      pointee.setRendererAov(aovName)
    }

    func render(rootPrim: Usd.Prim, params: UsdImagingGL.RenderParams)
    {
      pointee.render(rootPrim: rootPrim, params: params)
    }

    func setCameraState(modelViewMatrix: Gf.Matrix4d, projectionMatrix: Gf.Matrix4d)
    {
      pointee.setCameraState(modelViewMatrix: modelViewMatrix, projectionMatrix: projectionMatrix)
    }

    func setRenderViewport(_ viewport: Gf.Vec4d)
    {
      pointee.setRenderViewport(viewport)
    }

    func setWindowPolicy(_ policy: UsdImagingGL.Engine.CameraUtilWindowConformPolicy)
    {
      self.pointee.setWindowPolicy(policy)
    }

    func setLightingState(lights: Pixar.GlfSimpleLightVector, material: Pixar.GlfSimpleMaterial, sceneAmbient: Pixar.GfVec4f)
    {
      pointee.setLightingState(lights: lights, material: material, sceneAmbient: sceneAmbient)
    }

    func getAovTexture(_ aovName: Hd.AovTokens) -> Pixar.HgiTextureHandle
    {
      pointee.getAovTexture(aovName)
    }
  }
#endif // canImport(UsdImagingGLEngine)
