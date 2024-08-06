//
// Copyright 2020 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "Hgi/graphicsCmdsDesc.h"
#include "HgiMetal/buffer.h"
#include "HgiMetal/conversions.h"
#include "HgiMetal/diagnostic.h"
#include "HgiMetal/graphicsCmds.h"
#include "HgiMetal/graphicsPipeline.h"
#include "HgiMetal/hgi.h"
#include "HgiMetal/indirectCommandEncoder.h"
#include "HgiMetal/resourceBindings.h"
#include "HgiMetal/texture.h"

#include "Work/dispatcher.h"
#include "Work/loops.h"
#include "Work/withScopedParallelism.h"

#include "Arch/defines.h"

PXR_NAMESPACE_OPEN_SCOPE

HgiMetalGraphicsCmds::CachedEncoderState::CachedEncoderState()
{
  ResetCachedEncoderState();
}

void HgiMetalGraphicsCmds::CachedEncoderState::ResetCachedEncoderState()
{
  vertexBindings.clear();

  resourceBindings = nil;
  graphicsPipeline = nil;
  argumentBuffer = nil;
}

static void _SetVertexBindings(MTL::RenderCommandEncoder *encoder,
                               HgiVertexBufferBindingVector const &bindings)
{
  for (HgiVertexBufferBinding const binding : bindings) {
    if (binding.buffer) {
      HgiMetalBuffer *mtlBuffer = static_cast<HgiMetalBuffer *>(binding.buffer.Get());

      encoder->setVertexBuffer(mtlBuffer->GetBufferId(), binding.byteOffset, binding.index);
    }
  }
}

HgiMetalGraphicsCmds::HgiMetalGraphicsCmds(HgiMetal *hgi, HgiGraphicsCmdsDesc const &desc)
    : HgiGraphicsCmds(),
      _hgi(hgi),
      _renderPassDescriptor(nil),
      _parallelEncoder(nil),
      _argumentBuffer(nil),
      _descriptor(desc),
      _primitiveType(HgiPrimitiveTypeTriangleList),
      _primitiveIndexSize(0),
      _drawBufferBindingIndex(0),
      _debugLabel(nil),
      _viewportSet(false),
      _scissorRectSet(false),
      _enableParallelEncoder(false),
      _primitiveTypeChanged(false),
      _maxNumEncoders(1)
{
  TF_VERIFY(desc.colorTextures.size() == desc.colorAttachmentDescs.size());

  if (!desc.colorResolveTextures.empty() &&
      desc.colorResolveTextures.size() != desc.colorTextures.size())
  {
    TF_CODING_ERROR("color and resolve texture count mismatch.");
    return;
  }

  if (desc.depthResolveTexture && !desc.depthTexture) {
    TF_CODING_ERROR("DepthResolve texture without depth texture.");
    return;
  }

  _renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();

  // The GPU culling pass is only a vertex shader, so it doesn't have any
  // render targets bound to it.  To prevent an API validation error, set
  // some default values for the target.
  if (!desc.HasAttachments()) {
    _renderPassDescriptor->setRenderTargetWidth(256);
    _renderPassDescriptor->setRenderTargetHeight(256);
    _renderPassDescriptor->setDefaultRasterSampleCount(1);
  }

  // Color attachments
  bool resolvingColor = !desc.colorResolveTextures.empty();
  bool hasClear = false;
  for (size_t i = 0; i < desc.colorAttachmentDescs.size(); i++) {
    HgiAttachmentDesc const &hgiColorAttachment = desc.colorAttachmentDescs[i];
    MTL::RenderPassColorAttachmentDescriptor *metalColorAttachment =
        _renderPassDescriptor->colorAttachments()->object(i);

    if (hgiColorAttachment.loadOp == HgiAttachmentLoadOpClear) {
      hasClear = true;
    }

#if defined(ARCH_OS_IOS) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= 130000)
    metalColorAttachment->setLoadAction(MTL::LoadActionLoad);
#else  /* defined(ARCH_OS_OSX) */
    metalColorAttachment->setLoadAction(
        HgiMetalConversions::GetAttachmentLoadOp(hgiColorAttachment.loadOp));
#endif /* defined(ARCH_OS_IOS) && (__IPHONE_OS_VERSION_MAX_ALLOWED >= 130000) */

    metalColorAttachment->setStoreAction(
        HgiMetalConversions::GetAttachmentStoreOp(hgiColorAttachment.storeOp));
    if (hgiColorAttachment.loadOp == HgiAttachmentLoadOpClear) {
      GfVec4f const &clearColor = hgiColorAttachment.clearValue;
      metalColorAttachment->setClearColor(
          MTL::ClearColor::Make(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
    }

    HgiMetalTexture *colorTexture = static_cast<HgiMetalTexture *>(desc.colorTextures[i].Get());

    TF_VERIFY(colorTexture->GetDescriptor().format == hgiColorAttachment.format);
    metalColorAttachment->setTexture(colorTexture->GetTextureId());

    if (resolvingColor) {
      HgiMetalTexture *resolveTexture = static_cast<HgiMetalTexture *>(
          desc.colorResolveTextures[i].Get());

      metalColorAttachment->setResolveTexture(resolveTexture->GetTextureId());

      if (hgiColorAttachment.storeOp == HgiAttachmentStoreOpStore) {
        metalColorAttachment->setStoreAction(MTL::StoreActionStoreAndMultisampleResolve);
      }
      else {
        metalColorAttachment->setStoreAction(MTL::StoreActionMultisampleResolve);
      }
    }
  }

  // Depth attachment
  if (desc.depthTexture) {
    HgiAttachmentDesc const &hgiDepthAttachment = desc.depthAttachmentDesc;
    MTL::RenderPassDepthAttachmentDescriptor *metalDepthAttachment =
        _renderPassDescriptor->depthAttachment();

    if (hgiDepthAttachment.loadOp == HgiAttachmentLoadOpClear) {
      hasClear = true;
    }

    metalDepthAttachment->setLoadAction(
        HgiMetalConversions::GetAttachmentLoadOp(hgiDepthAttachment.loadOp));
    metalDepthAttachment->setStoreAction(
        HgiMetalConversions::GetAttachmentStoreOp(hgiDepthAttachment.storeOp));
    metalDepthAttachment->setClearDepth(hgiDepthAttachment.clearValue[0]);

    HgiMetalTexture *depthTexture = static_cast<HgiMetalTexture *>(desc.depthTexture.Get());

    TF_VERIFY(depthTexture->GetDescriptor().format == hgiDepthAttachment.format);
    metalDepthAttachment->setTexture(depthTexture->GetTextureId());

    if (desc.depthResolveTexture) {
      HgiMetalTexture *resolveTexture = static_cast<HgiMetalTexture *>(
          desc.depthResolveTexture.Get());

      metalDepthAttachment->setResolveTexture(resolveTexture->GetTextureId());

      if (hgiDepthAttachment.storeOp == HgiAttachmentStoreOpStore) {
        metalDepthAttachment->setStoreAction(MTL::StoreActionStoreAndMultisampleResolve);
      }
      else {
        metalDepthAttachment->setStoreAction(MTL::StoreActionMultisampleResolve);
      }
    }

    // Stencil attachment
    if (depthTexture->GetDescriptor().format == HgiFormatFloat32UInt8) {
      MTL::RenderPassStencilAttachmentDescriptor *stencilAttachment =
          _renderPassDescriptor->stencilAttachment();
      stencilAttachment->setLoadAction(metalDepthAttachment->loadAction());
      stencilAttachment->setStoreAction(metalDepthAttachment->storeAction());
      stencilAttachment->setClearStencil(hgiDepthAttachment.clearValue[0]);
      stencilAttachment->setTexture(metalDepthAttachment->texture());

      if (desc.depthResolveTexture) {
        stencilAttachment->setResolveTexture(metalDepthAttachment->resolveTexture());
        stencilAttachment->setStencilResolveFilter(
            MTL::MultisampleStencilResolveFilterDepthResolvedSample);
        stencilAttachment->setStoreAction(metalDepthAttachment->storeAction());
      }
    }
  }

  _enableParallelEncoder = _hgi->GetCapabilities()->useParallelEncoder;

  if (_enableParallelEncoder) {
    _maxNumEncoders = WorkGetPhysicalConcurrencyLimit() / 2;
  }
  else {
    _maxNumEncoders = 1;
  }

  if (hasClear) {
    GetEncoder();
    _CreateArgumentBuffer();
  }
}

HgiMetalGraphicsCmds::~HgiMetalGraphicsCmds()
{
  TF_VERIFY(_encoders.empty(), "Encoder created, but never commited.");

  _renderPassDescriptor->release();
  if (_debugLabel) {
    _debugLabel->release();
  }
}

void HgiMetalGraphicsCmds::EnableParallelEncoder(bool enable)
{
  _enableParallelEncoder = enable;
}

void HgiMetalGraphicsCmds::_VegaIndirectFix()
{
  if (!_primitiveTypeChanged) {
    return;
  }

  if (!_hgi->GetCapabilities()->requiresIndirectDrawFix) {
    return;
  }
  // Fix for Vega in macOS before 12.0.  There is state leakage between
  // indirect draw of different prim types which results in a GPU crash.
  // Flush with a null draw through the direct path.
  MTL::RenderCommandEncoder *encoder = GetEncoder();
  MTL::PrimitiveType mtlType = HgiMetalConversions::GetPrimitiveType(_primitiveType);
  encoder->drawPrimitives(mtlType, NS::UInteger(0), NS::UInteger(0));
}

uint32_t HgiMetalGraphicsCmds::_GetNumEncoders()
{
  return (uint32_t)_encoders.size();
}

void HgiMetalGraphicsCmds::_SetCachedEncoderState(MTL::RenderCommandEncoder *encoder)
{
  if (_viewportSet) {
    encoder->setViewport(_CachedEncState.viewport);
  }
  if (_scissorRectSet) {
    encoder->setScissorRect(_CachedEncState.scissorRect);
  }
  if (_CachedEncState.graphicsPipeline) {
    _CachedEncState.graphicsPipeline->BindPipeline(encoder);
  }
  if (_CachedEncState.resourceBindings) {
    _CachedEncState.resourceBindings->BindResources(_hgi, encoder, _CachedEncState.argumentBuffer);
  }

  _SetVertexBindings(encoder, _CachedEncState.vertexBindings);
}

void HgiMetalGraphicsCmds::_SetNumberParallelEncoders(uint32_t numEncoders)
{
  // Put a lock around the creation to prevent two requests colliding
  // (this should never happen...)
  std::lock_guard<std::mutex> lock(_encoderLock);

  uint32_t const numActiveEncoders = _GetNumEncoders();

  // Check if we already have enough
  if (numEncoders <= numActiveEncoders) {
    return;
  }

  if (_enableParallelEncoder) {
    // Do we need to create a parallel encoder
    if (!_parallelEncoder) {
      _parallelEncoder = _hgi->GetPrimaryCommandBuffer(this, false)
                             ->parallelRenderCommandEncoder(_renderPassDescriptor);

      if (_debugLabel) {
        _parallelEncoder->pushDebugGroup(_debugLabel);
      }
    }
    // Create any missing encoders
    for (uint32_t i = numActiveEncoders; i < numEncoders; i++) {
      MTL::RenderCommandEncoder *encoder = _parallelEncoder->renderCommandEncoder();
      _encoders.push_back(encoder);
    }
  }
  else {
    if (numEncoders > 1) {
      TF_CODING_ERROR("Only 1 encoder supported");
    }
    if (numActiveEncoders >= 1) {
      return;
    }

    MTL::RenderCommandEncoder *encoder =
        _hgi->GetPrimaryCommandBuffer(this, false)->renderCommandEncoder(_renderPassDescriptor);
    if (_debugLabel) {
      encoder->pushDebugGroup(_debugLabel);
    }
    _encoders.push_back(encoder);
  }

  for (uint32_t i = numActiveEncoders; i < numEncoders; i++) {
    // Setup any relevant state for the new encoder(s)
    _SetCachedEncoderState(_encoders[i]);
  }

  if (_debugLabel) {
    _debugLabel->release();
    _debugLabel = nil;
  }
}

MTL::RenderCommandEncoder *HgiMetalGraphicsCmds::GetEncoder(uint32_t encoderIndex)
{
  uint32_t numActiveEncoders = _GetNumEncoders();

  // Do we need to create an intial encoder
  if (!numActiveEncoders) {
    _SetNumberParallelEncoders(1);
    numActiveEncoders = _GetNumEncoders();
  }

  // Check if we have this encoder (it's OK not to have it)
  if (encoderIndex >= numActiveEncoders) {
    TF_CODING_ERROR("Invalid render encoder index specified");
    return nil;
  }

  return _encoders[encoderIndex];
}

void HgiMetalGraphicsCmds::_CreateArgumentBuffer()
{
  if (!_argumentBuffer) {
    _argumentBuffer = _hgi->GetArgBuffer();
  }
}

void HgiMetalGraphicsCmds::_SyncArgumentBuffer()
{
  if (_argumentBuffer) {
    if (_argumentBuffer->storageMode() != MTL::StorageModeShared) {
      _argumentBuffer->didModifyRange(NS::Range::Make(0, _argumentBuffer->length()));
    }
    _argumentBuffer = nil;
  }
}

void HgiMetalGraphicsCmds::SetViewport(GfVec4i const &vp)
{
  double x = vp[0];
  double y = vp[1];
  double w = vp[2];
  double h = vp[3];

  // Viewport is inverted in the y. Along with the front face winding order
  // being inverted.
  // This combination allows us to emulate the OpenGL coordinate space on
  // Metal
  _CachedEncState.viewport = (MTL::Viewport){x, y + h, w, -h, 0.0, 1.0};

  for (auto &encoder : _encoders) {
    encoder->setViewport(_CachedEncState.viewport);
  }

  _viewportSet = true;
}

void HgiMetalGraphicsCmds::SetScissor(GfVec4i const &sc)
{
  uint32_t x = sc[0];
  uint32_t y = sc[1];
  uint32_t w = sc[2];
  uint32_t h = sc[3];

  _CachedEncState.scissorRect = (MTL::ScissorRect){x, y, w, h};

  for (auto &encoder : _encoders) {
    encoder->setScissorRect(_CachedEncState.scissorRect);
  }

  _scissorRectSet = true;
}

void HgiMetalGraphicsCmds::BindPipeline(HgiGraphicsPipelineHandle pipeline)
{
  _primitiveTypeChanged = (_primitiveType != pipeline->GetDescriptor().primitiveType);
  _primitiveType = pipeline->GetDescriptor().primitiveType;

  _primitiveIndexSize = pipeline->GetDescriptor().tessellationState.primitiveIndexSize;

  _stepFunctions.Init(pipeline->GetDescriptor());

  _CachedEncState.graphicsPipeline = static_cast<HgiMetalGraphicsPipeline *>(pipeline.Get());

  if (_CachedEncState.graphicsPipeline) {
    for (auto &encoder : _encoders) {
      _CachedEncState.graphicsPipeline->BindPipeline(encoder);
    }
  }
}

void HgiMetalGraphicsCmds::BindResources(HgiResourceBindingsHandle r)
{
  _CreateArgumentBuffer();

  _CachedEncState.resourceBindings = static_cast<HgiMetalResourceBindings *>(r.Get());
  _CachedEncState.argumentBuffer = _argumentBuffer;

  if (_CachedEncState.resourceBindings) {
    for (auto &encoder : _encoders) {
      _CachedEncState.resourceBindings->BindResources(_hgi, encoder, _argumentBuffer);
    }
  }
}

void HgiMetalGraphicsCmds::SetConstantValues(HgiGraphicsPipelineHandle pipeline,
                                             HgiShaderStage stages,
                                             uint32_t bindIndex,
                                             uint32_t byteSize,
                                             const void *data)
{
  _CreateArgumentBuffer();

  HgiMetalResourceBindings::SetConstantValues(_argumentBuffer, stages, bindIndex, byteSize, data);
}

void HgiMetalGraphicsCmds::BindVertexBuffers(HgiVertexBufferBindingVector const &bindings)
{
  _stepFunctions.Bind(bindings);

  _CachedEncState.vertexBindings.insert(
      _CachedEncState.vertexBindings.end(), bindings.begin(), bindings.end());

  for (auto &encoder : _encoders) {
    _SetVertexBindings(encoder, bindings);
  }
}

void HgiMetalGraphicsCmds::Draw(uint32_t vertexCount,
                                uint32_t baseVertex,
                                uint32_t instanceCount,
                                uint32_t baseInstance)
{
  _SyncArgumentBuffer();

  MTL::PrimitiveType type = HgiMetalConversions::GetPrimitiveType(_primitiveType);
  MTL::RenderCommandEncoder *encoder = GetEncoder();

  _stepFunctions.SetVertexBufferOffsets(encoder, baseInstance);

  if (_primitiveType == HgiPrimitiveTypePatchList) {
    const NS::UInteger controlPointCount = _primitiveIndexSize;
    encoder->drawPatches(controlPointCount,
                         0,
                         vertexCount / controlPointCount,
                         nil,
                         0,
                         instanceCount,
                         baseInstance);
  }
  else {
    if (instanceCount == 1) {
      encoder->drawPrimitives(type, baseVertex, vertexCount);
    }
    else {
      encoder->drawPrimitives(type, baseVertex, vertexCount, instanceCount, baseInstance);
    }
  }

  _hgi->SetHasWork();
}

void HgiMetalGraphicsCmds::DrawIndirect(HgiBufferHandle const &drawParameterBuffer,
                                        uint32_t drawBufferByteOffset,
                                        uint32_t drawCount,
                                        uint32_t stride)
{
  MTL::PrimitiveType mtlType = HgiMetalConversions::GetPrimitiveType(_primitiveType);
  MTL::Buffer *drawBufferId =
      static_cast<HgiMetalBuffer *>(drawParameterBuffer.Get())->GetBufferId();

  _SyncArgumentBuffer();
  static const uint32_t _drawCallsPerThread = 256;
  const uint32_t numEncoders = std::min(std::max(drawCount / _drawCallsPerThread, 1U),
                                        _maxNumEncoders);
  const uint32_t normalCount = drawCount / numEncoders;
  const uint32_t finalCount = normalCount + (drawCount - normalCount * numEncoders);

  _SetNumberParallelEncoders(numEncoders);

  WorkWithScopedParallelism([&]() {
    WorkDispatcher wd;

    for (uint32_t i = 0; i < numEncoders; ++i) {
      const uint32_t encoderOffset = normalCount * i;
      // If this is the last encoder then ensure that we have all prims.
      const uint32_t encoderCount = (i == numEncoders - 1) ? finalCount : normalCount;
      wd.Run([&, i, encoderOffset, encoderCount]() {
        MTL::RenderCommandEncoder *encoder = GetEncoder(i);

        if (_primitiveType == HgiPrimitiveTypePatchList) {
          const NS::UInteger controlPointCount = _primitiveIndexSize;
          for (uint32_t offset = encoderOffset; offset < encoderOffset + encoderCount; ++offset) {
            _stepFunctions.SetVertexBufferOffsets(encoder, offset);
            const uint32_t bufferOffset = drawBufferByteOffset + (offset * stride);
            encoder->drawPatches(controlPointCount, nil, 0, drawBufferId, bufferOffset);
          }
        }
        else {
          _VegaIndirectFix();

          for (uint32_t offset = encoderOffset; offset < encoderOffset + encoderCount; ++offset) {
            _stepFunctions.SetVertexBufferOffsets(encoder, offset);
            const uint32_t bufferOffset = drawBufferByteOffset + (offset * stride);

            encoder->drawPrimitives(mtlType, drawBufferId, bufferOffset);
          }
        }
      });
    }
  });

  _hgi->SetHasWork();
}

void HgiMetalGraphicsCmds::DrawIndexed(HgiBufferHandle const &indexBuffer,
                                       uint32_t indexCount,
                                       uint32_t indexBufferByteOffset,
                                       uint32_t baseVertex,
                                       uint32_t instanceCount,
                                       uint32_t baseInstance)
{
  _SyncArgumentBuffer();

  HgiMetalBuffer *indexBuf = static_cast<HgiMetalBuffer *>(indexBuffer.Get());

  MTL::PrimitiveType mtlType = HgiMetalConversions::GetPrimitiveType(_primitiveType);

  MTL::RenderCommandEncoder *encoder = GetEncoder();

  _stepFunctions.SetVertexBufferOffsets(encoder, baseInstance);

  if (_primitiveType == HgiPrimitiveTypePatchList) {
    const NS::UInteger controlPointCount = _primitiveIndexSize;

    _stepFunctions.SetPatchBaseOffsets(encoder, baseVertex);

    encoder->drawIndexedPatches(controlPointCount,
                                indexBufferByteOffset / sizeof(uint32_t),
                                indexCount,
                                nil,
                                0,
                                indexBuf->GetBufferId(),
                                0,
                                instanceCount,
                                baseInstance);
  }
  else {
    _VegaIndirectFix();

    encoder->drawIndexedPrimitives(mtlType,
                                   indexCount,
                                   MTL::IndexTypeUInt32,
                                   indexBuf->GetBufferId(),
                                   indexBufferByteOffset,
                                   instanceCount,
                                   baseVertex,
                                   baseInstance);
  }

  _hgi->SetHasWork();
}

void HgiMetalGraphicsCmds::DrawIndexedIndirect(
    HgiBufferHandle const &indexBuffer,
    HgiBufferHandle const &drawParameterBuffer,
    uint32_t drawBufferByteOffset,
    uint32_t drawCount,
    uint32_t stride,
    std::vector<uint32_t> const &drawParameterBufferUInt32,
    uint32_t patchBaseVertexByteOffset)
{
  MTL::PrimitiveType mtlType = HgiMetalConversions::GetPrimitiveType(_primitiveType);
  MTL::Buffer *drawBufferId =
      static_cast<HgiMetalBuffer *>(drawParameterBuffer.Get())->GetBufferId();
  MTL::Buffer *indexBufferId = static_cast<HgiMetalBuffer *>(indexBuffer.Get())->GetBufferId();

  _SyncArgumentBuffer();
  static const uint32_t _drawCallsPerThread = 256;
  const uint32_t numEncoders = std::min(std::max(drawCount / _drawCallsPerThread, 1U),
                                        _maxNumEncoders);
  const uint32_t normalCount = drawCount / numEncoders;
  const uint32_t finalCount = normalCount + (drawCount - normalCount * numEncoders);

  _SetNumberParallelEncoders(numEncoders);

  WorkWithScopedParallelism([&]() {
    WorkDispatcher wd;

    for (uint32_t i = 0; i < numEncoders; ++i) {
      const uint32_t encoderOffset = normalCount * i;
      // If this is the last encoder then ensure that we have all prims.
      const uint32_t encoderCount = (i == numEncoders - 1) ? finalCount : normalCount;
      wd.Run([&, i, encoderOffset, encoderCount]() {
        MTL::RenderCommandEncoder *encoder = GetEncoder(i);

        if (_primitiveType == HgiPrimitiveTypePatchList) {
          const NS::UInteger controlPointCount = _primitiveIndexSize;

          for (uint32_t offset = encoderOffset; offset < encoderOffset + encoderCount; ++offset) {
            _stepFunctions.SetVertexBufferOffsets(encoder, offset);

            const uint32_t baseVertexIndex = (patchBaseVertexByteOffset + offset * stride) /
                                             sizeof(uint32_t);
            const uint32_t baseVertex = drawParameterBufferUInt32[baseVertexIndex];

            _stepFunctions.SetPatchBaseOffsets(encoder, baseVertex);

            const uint32_t bufferOffset = drawBufferByteOffset + (offset * stride);
            encoder->drawIndexedPatches(
                controlPointCount, nil, 0, indexBufferId, 0, drawBufferId, bufferOffset);
          }
        }
        else {
          _VegaIndirectFix();

          for (uint32_t offset = encoderOffset; offset < encoderOffset + encoderCount; ++offset) {
            _stepFunctions.SetVertexBufferOffsets(encoder, offset);

            const uint32_t bufferOffset = drawBufferByteOffset + (offset * stride);

            encoder->drawIndexedPrimitives(
                mtlType, MTL::IndexTypeUInt32, indexBufferId, 0, drawBufferId, bufferOffset);
          }
        }
      });
    }
  });

  _hgi->SetHasWork();
}

void HgiMetalGraphicsCmds::PushDebugGroup(const char *label)
{
  if (!HgiMetalDebugEnabled()) {
    return;
  }
  if (_parallelEncoder) {
    HGIMETAL_DEBUG_PUSH_GROUP(_parallelEncoder, label)
  }
  else if (!_encoders.empty()) {
    HGIMETAL_DEBUG_PUSH_GROUP(GetEncoder(), label)
  }
  else {
    _debugLabel = NS::String::string(label, NS::UTF8StringEncoding)->copy();
  }
}

void HgiMetalGraphicsCmds::PopDebugGroup()
{
  if (_parallelEncoder) {
    HGIMETAL_DEBUG_POP_GROUP(_parallelEncoder)
  }
  else if (!_encoders.empty()) {
    HGIMETAL_DEBUG_POP_GROUP(GetEncoder());
  }
  if (_debugLabel) {
    _debugLabel->release();
    _debugLabel = nil;
  }
}

void HgiMetalGraphicsCmds::InsertMemoryBarrier(HgiMemoryBarrier barrier)
{
  TF_VERIFY(barrier == HgiMemoryBarrierAll, "Unknown barrier");

  // Apple Silicon only support memory barriers between vertex stages after
  // macOS 12.3.
#if defined(ARCH_OS_OSX) && (defined(__MAC_12_3) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_12_3))
  MTL::BarrierScope scope = MTL::BarrierScopeBuffers;
  MTL::RenderStages srcStages = MTL::RenderStageVertex;
  MTL::RenderStages dstStages = MTL::RenderStageVertex;

  for (auto &encoder : _encoders) {
    encoder->memoryBarrier(scope, srcStages, dstStages);
  }
#endif /* defined(ARCH_OS_OSX) && (defined(__MAC_10_15) && (__MAC_OS_X_VERSION_MAX_ALLOWED >= \
          __MAC_10_15)) */
}

static HgiMetal::CommitCommandBufferWaitType _ToHgiMetal(const HgiSubmitWaitType wait)
{
  switch (wait) {
    case HgiSubmitWaitTypeNoWait:
      return HgiMetal::CommitCommandBuffer_NoWait;
    case HgiSubmitWaitTypeWaitUntilCompleted:
      return HgiMetal::CommitCommandBuffer_WaitUntilCompleted;
  }

  TF_CODING_ERROR("Bad enum value for HgiSubmitWaitType");
  return HgiMetal::CommitCommandBuffer_WaitUntilCompleted;
}

bool HgiMetalGraphicsCmds::_Submit(Hgi *hgi, HgiSubmitWaitType wait)
{
  if (_parallelEncoder) {
    WorkParallelForEach(
        _encoders.begin(), _encoders.end(), [](auto &encoder) { encoder->endEncoding(); });
    _parallelEncoder->endEncoding();
    _parallelEncoder = nil;

    _hgi->CommitPrimaryCommandBuffer(_ToHgiMetal(wait));
  }
  else if (!_encoders.empty()) {
    for (auto &encoder : _encoders) {
      encoder->endEncoding();
    }

    _hgi->CommitPrimaryCommandBuffer(_ToHgiMetal(wait));
  }

  std::lock_guard<std::mutex> lock(_encoderLock);

  _argumentBuffer = nil;
  _encoders.clear();
  _CachedEncState.ResetCachedEncoderState();

  return true;
}

PXR_NAMESPACE_CLOSE_SCOPE
