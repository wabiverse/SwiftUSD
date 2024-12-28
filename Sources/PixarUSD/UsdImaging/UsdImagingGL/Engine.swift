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

    func setRenderer(aov: Hd.AovTokens)
    {
      SetRendererAov(aov.token)
    }

    func render(root: Usd.Prim, params: UsdImagingGL.RenderParams)
    {
      Render(root, params)
    }
  }

  public extension UsdImagingGL.EngineSharedPtr
  {
    func setEnablePresentation(_ value: Bool)
    {
      pointee.setEnablePresentation(value)
    }

    func setRenderer(aov token: Hd.AovTokens)
    {
      pointee.setRenderer(aov: token)
    }

    func render(root prim: Usd.Prim, params: UsdImagingGL.RenderParams)
    {
      pointee.render(root: prim, params: params)
    }
  }
#endif // canImport(UsdImagingGLEngine)
