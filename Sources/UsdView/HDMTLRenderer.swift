/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
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
   * ### Overview
   *
   * The Hydra Engine (``Hd``) Metal renderer for the ``UsdView``
   * application conforms to the ``MTKViewDelegate`` protocol,
   * allowing it to be set as a ``MTKView`` object's delegate to
   * provide a drawing method to a ``MTKView`` object and respond
   * to rendering events. */
  class HDMTLRenderer: NSObject, MTKViewDelegate
  {
    let hgi: Pixar.HgiMetalPtr
    let driver: HdDriver

    init?(device _: MTLDevice)
    {
      hgi = HgiMetal.createHgi()
      driver = HdDriver(name: .renderDriver, driver: VtValue(hgi))
    }

    func info()
    {
      Msg.logger.log(level: .info, "Created HGI -> Metal API v\(hgi.apiVersion).")
    }

    func mtkView(_: MTKView, drawableSizeWillChange size: CGSize)
    {
      print("drawableSizeWillChange", size)
    }

    func draw(in _: MTKView)
    {}
  }
#endif /* canImport(Metal) && !os(visionOS) */
