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
    class MTLRenderer: NSObject, MTKViewDelegate
    {
      private let device: MTLDevice
      private let commandQueue: MTLCommandQueue
      private var pipelineState: MTLRenderPipelineState?

      init?(device: MTLDevice)
      {
        self.device = device

        guard let commandQueue = device.makeCommandQueue()
        else { return nil }

        self.commandQueue = commandQueue
        super.init()

        setupPipeline()
      }

      private func setupPipeline()
      {
        let library = try! device.makeDefaultLibrary(bundle: .usdview)
        let vertexFunction = library.makeFunction(name: "vertex_main")
        let fragmentFunction = library.makeFunction(name: "fragment_main")

        let pipelineDescriptor = MTLRenderPipelineDescriptor()
        pipelineDescriptor.vertexFunction = vertexFunction
        pipelineDescriptor.fragmentFunction = fragmentFunction
        pipelineDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm

        pipelineState = try? device.makeRenderPipelineState(descriptor: pipelineDescriptor)
      }

      public func mtkView(_: MTKView, drawableSizeWillChange _: CGSize)
      {}

      public func draw(in view: MTKView)
      {
        guard
          let drawable = view.currentDrawable,
          let renderPassDescriptor = view.currentRenderPassDescriptor,
          let pipelineState
        else { return }

        let commandBuffer = commandQueue.makeCommandBuffer()
        let renderEncoder = commandBuffer?.makeRenderCommandEncoder(descriptor: renderPassDescriptor)

        renderEncoder?.setRenderPipelineState(pipelineState)
        renderEncoder?.setViewport(
          MTLViewport(
            originX: 0.0,
            originY: 0.0,
            width: Double(view.drawableSize.width),
            height: Double(view.drawableSize.height),
            znear: -1.0,
            zfar: 1.0
          )
        )
        renderEncoder?.endEncoding()

        commandBuffer?.present(drawable)
        commandBuffer?.commit()
      }
    }
  }
#endif // canImport(Metal) && !os(visionOS)
