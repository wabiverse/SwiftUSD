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
    class MTLRenderer: NSObject, MTKViewDelegate
    {
      let hgi: Pixar.HgiMetalPtr
      // let engine: UsdImagingGLEngineSharedPtr
      // let stage: UsdStageRefPtr

      public init?(device _: MTLDevice)
      {
        hgi = HgiMetal.createHgi()

        // let excludedPaths = SdfPathVector()
        let driver = HdDriver(name: .renderDriver, driver: VtValue(hgi))

        // engine.reset(UsdImagingGLEngineSharedPtr(
        //   stage.getPseudoRoot().getPath(),
        //   excludedPaths,
        //   SdfPathVector(),
        //   SdfPath.AbsoluteRootPath(),
        //   driver
        // ))

        // engine.SetEnablePresentation(false)
        // engine.SetRendererAov(false)
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

      public func draw(in _: MTKView)
      {}
    }
  }
#endif // canImport(Metal) && !os(visionOS)
