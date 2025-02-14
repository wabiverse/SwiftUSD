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

  #if os(iOS) || os(visionOS)
    import Metal
    import MetalKit

    public extension Hydra
    {
      struct MTLView: UIViewRepresentable
      {
        public typealias UIViewType = MTKView
        public typealias SetNeedsDisplayTrigger = AnyPublisher<Void, Never>

        public enum DrawingMode
        {
          case timeUpdates(preferredFramesPerSecond: Int)
          case drawNotifications(setNeedsDisplayTrigger: SetNeedsDisplayTrigger?)
        }

        private let hydra: Hydra.RenderEngine!
        private let device: MTLDevice!
        private let renderer: MTLRenderer!

        public init(hydra: Hydra.RenderEngine, renderer: MTLRenderer)
        {
          self.hydra = hydra
          device = hydra.hydraDevice
          self.renderer = renderer
        }

        public func makeCoordinator() -> Coordinator
        {
          let mtkView = MTKView()
          mtkView.isPaused = false
          mtkView.framebufferOnly = true
          mtkView.preferredFramesPerSecond = 60
          mtkView.drawableSize = mtkView.frame.size

          return Coordinator(mtkView: mtkView)
        }

        public func makeUIView(context: Context) -> MTKView
        {
          let metalView = context.coordinator.metalView

          metalView.device = device
          metalView.delegate = renderer
          metalView.colorPixelFormat = .bgra8Unorm
          metalView.sampleCount = 1
          metalView.layer.backgroundColor = UIColor.clear.cgColor
          metalView.layer.isOpaque = false

          metalView.becomeFirstResponder()
          return metalView
        }

        public func updateUIView(_ view: MTKView, context _: Context)
        {
          renderer.draw(in: view)
        }

        public class Coordinator
        {
          private var cancellable: AnyCancellable?
          public var metalView: MTKView

          public init(mtkView: MTKView)
          {
            cancellable = nil
            metalView = mtkView
          }
        }
      }
    }
  #endif // os(iOS)
#endif // canImport(SwiftUI)
