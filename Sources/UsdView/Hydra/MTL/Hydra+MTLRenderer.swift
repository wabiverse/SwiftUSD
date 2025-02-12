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

  public extension Hydra
  {
    /**
     * ``MTLRenderer``
     *
     * ## Overview
     *
     * The Hydra Engine (``Hd``) Metal renderer for the ``UsdView``
     * application conforms to the ``MTKViewDelegate`` protocol,
     * allowing it to be set as a ``MTKView`` object's delegate to
     * provide a drawing method to a ``MTKView`` object and respond
     * to rendering events. */
    class MTLRenderer: NSObject, MTKViewDelegate, HdRenderEngine
    {
      let hgi: Pixar.HgiMetalPtr
      var device: MTLDevice!

      public var stage: UsdStageRefPtr

      #if canImport(UsdImagingGL)
        /// UsdImagingGL is not available on iOS.
        var engine: UsdImagingGL.EngineSharedPtr
      #endif // canImport(UsdImagingGL)

      public init(metalView: MTKView)
      {
        hgi = HgiMetal.createHgi()
        device = hgi.device
        stage = Usd.Stage.createInMemory()

        let driver = HdDriver(name: .renderDriver, driver: hgi.value)

        #if canImport(UsdImagingGL)
          // UsdImagingGL is not available on iOS.
          engine = UsdImagingGL.Engine.createEngine(
            rootPath: stage.getPseudoRoot().getPath(),
            excludedPaths: Sdf.PathVector(),
            invisedPaths: Sdf.PathVector(),
            sceneDelegateId: Sdf.Path.absoluteRootPath(),
            driver: driver
          )
        #endif // canImport(UsdImagingGL)

        metalView.device = hgi.device
      }

      public required convenience init(stage: UsdStageRefPtr)
      {
        self.init(metalView: MTKView())
        self.stage = stage

        #if canImport(UsdImagingGL)
          // UsdImagingGL is not available on iOS.
          engine.setEnablePresentation(false)
          engine.setRendererAov(.color)
        #endif // canImport(UsdImagingGL)
      }

      public func info()
      {
        Msg.logger.log(level: .info, "Created HGI -> Metal API v\(hgi.apiVersion).")
        Msg.logger.log(level: .info, "GPU Architecture -> \(hgi.device.architecture.name)")
      }

      public func mtkView(_: MTKView, drawableSizeWillChange size: CGSize)
      {
        print("drawableSizeWillChange", size)
      }

      public func draw()
      {}

      public func draw(in _: MTKView)
      {}
    }
  }
#endif // canImport(Metal) && !os(visionOS)
