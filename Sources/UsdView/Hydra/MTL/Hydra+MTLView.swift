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

#if canImport(SwiftUI)
  import Combine
  import SwiftUI

  #if canImport(Metal) && !os(visionOS)
    import Metal
    import MetalKit

    public extension Hydra
    {
      struct MTLView: NSViewRepresentable
      {
        public typealias NSViewType = MTKView
        public typealias SetNeedsDisplayTrigger = AnyPublisher<Void, Never>

        public enum DrawingMode
        {
          case timeUpdates(preferredFramesPerSecond: Int)
          case drawNotifications(setNeedsDisplayTrigger: SetNeedsDisplayTrigger?)
        }

        private let hydra: Hydra.RenderEngine!
        private let device: MTLDevice!
        private let renderer: MTLRenderer!

        var rgba: (Double, Double, Double, Double)

        public init(hydra: Hydra.RenderEngine, device: MTLDevice, renderer: MTLRenderer, rgba: (Double, Double, Double, Double))
        {
          self.hydra = hydra
          self.device = device
          self.renderer = renderer
          self.rgba = rgba
        }

        public func makeCoordinator() -> Coordinator
        {
          Coordinator()
        }

        public func makeNSView(context: Context) -> MTKView
        {
          let metalView = context.coordinator.metalView
          metalView.device = device
          metalView.delegate = renderer
          metalView.clearColor = MTLClearColorMake(rgba.0, rgba.1, rgba.2, rgba.3)
          metalView.apply(context.environment)

          context.coordinator.setNeedsDisplayTrigger = context.environment.setNeedsDisplayTrigger

          return metalView
        }

        public func updateNSView(_ view: MTKView, context: Context)
        {
          // view.clearColor = MTLClearColorMake(rgba.0, rgba.1, rgba.2, rgba.3)

          renderer.draw(in: view)
          hydra.render(rgba: rgba)
        }

        public class Coordinator
        {
          private var cancellable: AnyCancellable?
          public var metalView: MTKView = .init(frame: .zero)

          public init()
          {
            cancellable = nil
            setNeedsDisplayTrigger = nil
          }

          public var setNeedsDisplayTrigger: SetNeedsDisplayTrigger?
          {
            didSet
            {
              cancellable = setNeedsDisplayTrigger?.receive(on: DispatchQueue.main).sink
              { [weak self] in
                guard
                  let self,
                  metalView.isPaused,
                  metalView.enableSetNeedsDisplay
                else { return }

                metalView.setNeedsDisplay(metalView.bounds)
              }
            }
          }
        }
      }
    }
  #endif // canImport(Metal)
#endif // canImport(SwiftUI)
