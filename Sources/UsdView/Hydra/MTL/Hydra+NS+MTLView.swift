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

#if canImport(SwiftCrossUI)
  import SwiftCrossUI

  #if os(macOS)
    import AppKitBackend
    import Combine
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

        public init(hydra: Hydra.RenderEngine, renderer: MTLRenderer)
        {
          self.hydra = hydra
          device = hydra.hydraDevice
          self.renderer = renderer
        }

        public func makeCoordinator() -> Coordinator
        {
          let mtkView = HydraMTKView()
          mtkView.isPaused = false // driven by display link
          mtkView.framebufferOnly = false // we're using the drawable in our own render pass
          mtkView.enableSetNeedsDisplay = false // don't wait for setNeedsDisplay
          mtkView.presentsWithTransaction = true // sync presentation with our command buffer

          if let mode = CGDisplayCopyDisplayMode(CGMainDisplayID())
          {
            mtkView.preferredFramesPerSecond = Int(mode.refreshRate)
          }
          else
          {
            mtkView.preferredFramesPerSecond = 60
          }

          return Coordinator(mtkView: mtkView)
        }

        public func makeNSView(context: NSViewRepresentableContext<Self>) -> MTKView
        {
          let metalView = context.coordinator.metalView

          metalView.device = device
          metalView.delegate = renderer
          metalView.colorPixelFormat = MTLPixelFormat.bgra8Unorm
          metalView.sampleCount = 1
          metalView.layer?.backgroundColor = NSColor.clear.cgColor
          metalView.layer?.isOpaque = false

          // hand the view a (weak) reference to the
          // engine whose camera it should drive.
          metalView.hydra = hydra

          metalView.becomeFirstResponder()
          return metalView
        }

        public func updateNSView(_: MTKView, context _: NSViewRepresentableContext<Self>)
        {}

        public class Coordinator
        {
          private var cancellable: AnyCancellable?
          public var metalView: HydraMTKView

          public init(mtkView: HydraMTKView)
          {
            cancellable = nil
            metalView = mtkView
          }
        }
      }

      /// A `MTKView` that turns mouse/trackpad input on the viewport directly
      /// into orbit (tumble) and dolly (zoom) adjustments on the Hydra view
      /// camera.
      final class HydraMTKView: MTKView
      {
        /// Weak: the view drives the engine's camera, but doesn't own the engine.
        weak var hydra: Hydra.RenderEngine?

        public override var acceptsFirstResponder: Bool { true }

        public override func mouseDragged(with event: NSEvent)
        {
          hydra?.orbit(
            deltaYaw: Double(event.deltaX) * 0.4,
            deltaPitch: Double(event.deltaY) * 0.4
          )
        }

        public override func scrollWheel(with event: NSEvent)
        {
          // two finger trackpad scroll (or a mouse wheel): scrolling up
          // (positive `scrollingDeltaY`) dollies inward, toward the subject -
          // matching the pinch-to-zoom direction in `magnify` below.
          hydra?.dolly(by: -Double(event.scrollingDeltaY) * 0.01)
        }

        public override func magnify(with event: NSEvent)
        {
          // trackpad pinch: `magnification` is a small fractional delta per
          // tick (spreading fingers apart is positive = zoom in = move closer).
          hydra?.dolly(by: -event.magnification)
        }
      }
    }
  #endif // os(macOS)
#endif // canImport(SwiftCrossUI)
