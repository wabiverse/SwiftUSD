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
      private var hydra: Hydra.RenderEngine?
      private var pipelineState: MTLRenderPipelineState?

      private var inFlightSemaphore = DispatchSemaphore(value: 1)

      convenience init(device: MTLDevice, hydra: Hydra.RenderEngine)
      {
        self.init(device: device)!
        self.hydra = hydra
      }

      init?(device: MTLDevice)
      {
        self.device = device

        super.init()

        setupPipeline()
      }

      private func setupPipeline()
      {
        do
        {
          let defaultLibrary = try device.makeDefaultLibrary(bundle: .usdview)

          guard let vertexFunction = defaultLibrary.makeFunction(name: "vtxBlit")
          else { Msg.logger.error("HYDRA: Failed to create vertex function."); return }

          guard let fragmentFunction = defaultLibrary.makeFunction(name: "fragBlitLinear")
          else { Msg.logger.error("HYDRA: Failed to create fragment function."); return }

          // set up the pipeline state descriptor.
          let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
          pipelineStateDescriptor.rasterSampleCount = 1
          pipelineStateDescriptor.vertexFunction = vertexFunction
          pipelineStateDescriptor.fragmentFunction = fragmentFunction
          pipelineStateDescriptor.depthAttachmentPixelFormat = .invalid

          // configure the color attachment for blending.
          if let colorAttachment = pipelineStateDescriptor.colorAttachments[0]
          {
            colorAttachment.pixelFormat = .bgra8Unorm
            colorAttachment.isBlendingEnabled = true
            colorAttachment.rgbBlendOperation = .add
            colorAttachment.alphaBlendOperation = .add
            colorAttachment.sourceRGBBlendFactor = .one
            colorAttachment.sourceAlphaBlendFactor = .one
            colorAttachment.destinationRGBBlendFactor = .oneMinusSourceAlpha
            colorAttachment.destinationAlphaBlendFactor = .zero
          }

          // create the pipeline state object.
          pipelineState = try device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        }
        catch
        {
          Msg.logger.error("HYDRA: Failed to create pipeline state: \(error.localizedDescription)")
        }
      }

      public func mtkView(_: MTKView, drawableSizeWillChange _: CGSize)
      {}

      public func draw(in view: MTKView)
      {
        drawFrame(in: view, timeCode: 0.0)
      }

      /// draw the scene, and blit the result to the view.
      func drawFrame(in view: MTKView, timeCode: Double) -> Bool
      {
        guard let hgi = hydra?.getHgi()
        else { Msg.logger.error("HYDRA: Failed to retrieve hgi."); return false }

        // start the next frame.
        _ = inFlightSemaphore.wait(timeout: .distantFuture)
        defer { inFlightSemaphore.signal() }

        /*
         * ---------------------------------------------------------------- */

        hgi.pointee.StartFrame()

        // draw the scene using hydra, and recast the result to a MTLTexture.
        let viewSize = view.drawableSize
        guard
          let hgiTexture = hydra?.render(at: timeCode, viewSize: viewSize),
          let metalTexture = hgiTexture.GetId() as? MTLTexture,
          let commandBuffer = hgi.pointee.GetPrimaryCommandBuffer()
        else { Msg.logger.error("HYDRA: Failed to draw the scene."); return false }

        // copy the rendered texture to the view.
        blitToView(view, commandBuffer: commandBuffer, texture: metalTexture)

        // tell hydra to commit the command buffer and complete the work.
        hgi.pointee.CommitPrimaryCommandBuffer()

        hgi.pointee.EndFrame()

        /*
         * ---------------------------------------------------------------- */

        return true
      }

      /// copies the texture to the view with a shader.
      public func blitToView(_ view: MTKView, commandBuffer: MTLCommandBuffer, texture: MTLTexture)
      {
        guard let renderPassDescriptor = view.currentRenderPassDescriptor
        else { Msg.logger.error("HYDRA: Failed to blit because there is no render pass descriptor for the current view."); return }

        // create a render command encoder to encode the copy command.
        guard let renderEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
        else { Msg.logger.error("HYDRA: Failed to create a render command encoder to blit the texture to the view."); return }

        // blit the texture to the view.
        renderEncoder.pushDebugGroup("FinalBlit")
        renderEncoder.setFragmentTexture(texture, index: 0)
        if let pipelineState
        {
          renderEncoder.setRenderPipelineState(pipelineState)
        }
        renderEncoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3)
        renderEncoder.popDebugGroup()

        // finish encoding the copy command.
        renderEncoder.endEncoding()
        if let drawable = view.currentDrawable
        {
          commandBuffer.present(drawable)
        }
      }
    }
  }
#endif // canImport(Metal) && !os(visionOS)
