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

  /**
   * ``HDMTLRenderer``
   *
   * ## Overview
   *
   * The Hydra Engine (``Hd``) Metal renderer for the ``UsdView``
   * application conforms to the ``MTKViewDelegate`` protocol,
   * allowing it to be set as a ``MTKView`` object's delegate to
   * provide a drawing method to a ``MTKView`` object and respond
   * to rendering events. */
  class HDMTLRenderer: NSObject, MTKViewDelegate
  {
    let hgi: Pixar.HgiMetalPtr

    init?(device _: MTLDevice)
    {
      hgi = HgiMetal.createHgi()

      let driver = HdDriver(name: .renderDriver, driver: VtValue(hgi))
    }

    func info()
    {
      Msg.logger.log(level: .info, "Created HGI -> Metal API v\(hgi.apiVersion).")
      Msg.logger.log(level: .info, "GPU Architecture -> \(hgi.device.architecture.name)")
    }

    func mtkView(_: MTKView, drawableSizeWillChange size: CGSize)
    {
      print("drawableSizeWillChange", size)
    }

    func draw(in _: MTKView)
    {}
  }
#endif /* canImport(Metal) && !os(visionOS) */
