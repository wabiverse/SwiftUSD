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
#if canImport(HgiGL)
  import HgiGL

  public extension Hydra
  {
    /**
     * ``GLRenderer``
     *
     * ## Overview
     *
     * The Hydra Engine (``Hd``) OpenGL renderer for the ``UsdView``
     * application. */
    class GLRenderer
    {
      let hgi: Pixar.HgiGLPtr
      var device: Pixar.HgiGLDevice!

      public var stage: UsdStageRefPtr

      #if canImport(UsdImagingGL)
        /// UsdImagingGL is not available on iOS.
        var engine: UsdImagingGL.EngineSharedPtr
      #endif // canImport(UsdImagingGL)

      public required init(stage: UsdStageRefPtr)
      {
        hgi = HgiGL.createHgi()
        device = hgi.device
        self.stage = stage

        let driver = HdDriver(name: .renderDriver, driver: hgi.value)

        #if canImport(UsdImagingGL)
          engine = UsdImagingGL.Engine.createEngine(
            rootPath: stage.getPseudoRoot().getPath(),
            excludedPaths: Sdf.PathVector(),
            invisedPaths: Sdf.PathVector(),
            sceneDelegateId: Sdf.Path.absoluteRootPath(),
            driver: driver
          )

          engine.setEnablePresentation(false)
          engine.setRenderer(aov: .color)
        #endif // canImport(UsdImagingGL)
      }

      public func info()
      {
        Msg.logger.log(level: .info, "Created HGI -> OpenGL.")
      }
    }
  }
#endif // canImport(HgiGL)
