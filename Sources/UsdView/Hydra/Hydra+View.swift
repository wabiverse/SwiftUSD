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

public extension Hydra
{
  #if canImport(Metal) && !os(visionOS)
    typealias Viewport = Hydra.MTLView
  #elseif os(macOS)
    typealias Viewport = NSViewRepresentable
  #elseif os(visionOS) || os(tvOS) || os(watchOS)
    typealias Viewport = UIViewRepresentable
  #else
    struct Viewport {}
  #endif // canImport(Metal) && !os(visionOS)
}

public extension Hydra.Viewport
{
  init(engine: Hydra.RenderEngine, rgba: (Double, Double, Double, Double))
  {
    #if canImport(Metal) && !os(visionOS)
      let device = MTLCreateSystemDefaultDevice()!
      let renderer = Hydra.MTLRenderer(device: device)!
      self.init(hydra: engine, device: device, renderer: renderer, rgba: rgba)
    #endif // canImport(Metal) && !os(visionOS)
  }
}
