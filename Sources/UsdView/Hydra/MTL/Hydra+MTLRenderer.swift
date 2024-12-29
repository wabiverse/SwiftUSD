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
      /// private let commandQueue: MTLCommandQueue
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

        // guard let commandQueue = device.makeCommandQueue()
        // else { return nil }

        // self.commandQueue = commandQueue
        super.init()

        loadMetal()
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
        drawFrame(in: view, timeCode: 0.0)
      }

      /// draw the scene, and blit the result to the view.
      func drawFrame(in view: MTKView, timeCode: Double) -> Bool
      {
        guard let hgi = hydra?.getHgi() else { return false }

        // start the next frame.
        _ = inFlightSemaphore.wait(timeout: .distantFuture)
        defer { inFlightSemaphore.signal() }

        hgi.pointee.StartFrame()

        // draw the scene using Hydra, and recast the result to a MTLTexture.
        let viewSize = view.drawableSize
        guard
          let hgiTexture = hydra?.render(at: timeCode, viewSize: viewSize),
          let metalTexture = hgiTexture.GetId() as? MTLTexture,
          let commandBuffer = hgi.pointee.GetPrimaryCommandBuffer()
        else { return false }

        // copy the rendered texture to the view.
        blitToView(view, commandBuffer: commandBuffer, texture: metalTexture)

        // tell Hydra to commit the command buffer and complete the work.
        hgi.pointee.CommitPrimaryCommandBuffer()
        hgi.pointee.EndFrame()

        return true
      }

      /// copies the texture to the view with a shader.
      public func blitToView(_ view: MTKView, commandBuffer: MTLCommandBuffer, texture: MTLTexture)
      {
        guard let renderPassDescriptor = view.currentRenderPassDescriptor
        else
        {
          return
        }

        // Create a render command encoder to encode the copy command.
        guard let renderEncoder = commandBuffer.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
        else
        {
          return
        }

        // Blit the texture to the view.
        renderEncoder.pushDebugGroup("FinalBlit")
        renderEncoder.setFragmentTexture(texture, index: 0)
        if let pipelineState
        {
          renderEncoder.setRenderPipelineState(pipelineState)
        }
        renderEncoder.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3)
        renderEncoder.popDebugGroup()

        // Finish encoding the copy command.
        renderEncoder.endEncoding()
        if let drawable = view.currentDrawable
        {
          commandBuffer.present(drawable)
        }
      }

      /// Prepares the Metal objects for copying to the view.
      private func loadMetal()
      {
        do
        {
          let defaultLibrary = try device.makeDefaultLibrary(bundle: .usdview)

          guard let vertexFunction = defaultLibrary.makeFunction(name: "vtxBlit")
          else
          {
            print("Failed to create vertex function.")
            return
          }

          guard let fragmentFunction = defaultLibrary.makeFunction(name: "fragBlitLinear")
          else
          {
            print("Failed to create fragment function.")
            return
          }

          // Set up the pipeline state descriptor.
          let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
          pipelineStateDescriptor.rasterSampleCount = 1
          pipelineStateDescriptor.vertexFunction = vertexFunction
          pipelineStateDescriptor.fragmentFunction = fragmentFunction
          pipelineStateDescriptor.depthAttachmentPixelFormat = .invalid

          // Configure the color attachment for blending.
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

          // Create the pipeline state object.
          pipelineState = try device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        }
        catch
        {
          print("Failed to create pipeline state: \(error.localizedDescription)")
        }
      }
    }
  }
#endif // canImport(Metal) && !os(visionOS)
