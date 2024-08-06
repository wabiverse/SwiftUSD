//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_GRAPHICS_CMDS_H
#define PXR_IMAGING_HGI_METAL_GRAPHICS_CMDS_H

#include "Gf/vec4i.h"
#include "Hgi/graphicsCmds.h"
#include "HgiMetal/api.h"
#include "HgiMetal/stepFunctions.h"
#include "pxr/pxrns.h"
#include <cstdint>

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

struct HgiGraphicsCmdsDesc;
class HgiMetalResourceBindings;
class HgiMetalGraphicsPipeline;

/// \class HgiMetalGraphicsCmds
///
/// Metal implementation of HgiGraphicsEncoder.
///
class HgiMetalGraphicsCmds final : public HgiGraphicsCmds {
 public:
  HGIMETAL_API
  ~HgiMetalGraphicsCmds() override;

  HGIMETAL_API
  void SetViewport(GfVec4i const &vp) override;

  HGIMETAL_API
  void SetScissor(GfVec4i const &sc) override;

  HGIMETAL_API
  void BindPipeline(HgiGraphicsPipelineHandle pipeline) override;

  HGIMETAL_API
  void BindResources(HgiResourceBindingsHandle resources) override;

  HGIMETAL_API
  void SetConstantValues(HgiGraphicsPipelineHandle pipeline,
                         HgiShaderStage stages,
                         uint32_t bindIndex,
                         uint32_t byteSize,
                         const void *data) override;

  HGIMETAL_API
  void BindVertexBuffers(HgiVertexBufferBindingVector const &bindings) override;

  HGIMETAL_API
  void Draw(uint32_t vertexCount,
            uint32_t baseVertex,
            uint32_t instanceCount,
            uint32_t baseInstance) override;

  HGIMETAL_API
  void DrawIndirect(HgiBufferHandle const &drawParameterBuffer,
                    uint32_t bufferOffset,
                    uint32_t drawCount,
                    uint32_t stride) override;

  HGIMETAL_API
  void DrawIndexed(HgiBufferHandle const &indexBuffer,
                   uint32_t indexCount,
                   uint32_t indexBufferByteOffset,
                   uint32_t baseVertex,
                   uint32_t instanceCount,
                   uint32_t baseInstance) override;

  HGIMETAL_API
  void DrawIndexedIndirect(HgiBufferHandle const &indexBuffer,
                           HgiBufferHandle const &drawParameterBuffer,
                           uint32_t drawBufferByteOffset,
                           uint32_t drawCount,
                           uint32_t stride,
                           std::vector<uint32_t> const &drawParameterBufferUInt32,
                           uint32_t patchBaseVertexByteOffset) override;

  HGIMETAL_API
  void PushDebugGroup(const char *label) override;

  HGIMETAL_API
  void PopDebugGroup() override;

  HGIMETAL_API
  void InsertMemoryBarrier(HgiMemoryBarrier barrier) override;

  HGIMETAL_API
  void EnableParallelEncoder(bool enable);

  // Needs to be accessible from the Metal IndirectCommandEncoder
  MTL::RenderCommandEncoder* GetEncoder(uint32_t encoderIndex = 0);

 protected:
  friend class HgiMetal;

  HGIMETAL_API
  HgiMetalGraphicsCmds(HgiMetal *hgi, HgiGraphicsCmdsDesc const &desc);

  HGIMETAL_API
  bool _Submit(Hgi *hgi, HgiSubmitWaitType wait) override;

 private:
  HgiMetalGraphicsCmds() = delete;
  HgiMetalGraphicsCmds &operator=(const HgiMetalGraphicsCmds &) = delete;
  HgiMetalGraphicsCmds(const HgiMetalGraphicsCmds &) = delete;

  uint32_t _GetNumEncoders();
  void _SetNumberParallelEncoders(uint32_t numEncoders);
  void _SetCachedEncoderState(MTL::RenderCommandEncoder* encoder);
  mutable std::mutex _encoderLock;

  void _CreateArgumentBuffer();
  void _SyncArgumentBuffer();
  void _VegaIndirectFix();

  struct CachedEncoderState {
    CachedEncoderState();

    void ResetCachedEncoderState();

    MTL::Viewport viewport;
    MTL::ScissorRect scissorRect;

    HgiMetalResourceBindings *resourceBindings;
    HgiMetalGraphicsPipeline *graphicsPipeline;
    MTL::Buffer* argumentBuffer;
    HgiVertexBufferBindingVector vertexBindings;
  } _CachedEncState;

  HgiMetal *_hgi;
  MTL::RenderPassDescriptor *_renderPassDescriptor;
  MTL::ParallelRenderCommandEncoder* _parallelEncoder;
  std::vector<MTL::RenderCommandEncoder*> _encoders;
  MTL::Buffer* _argumentBuffer;
  HgiGraphicsCmdsDesc _descriptor;
  HgiPrimitiveType _primitiveType;
  uint32_t _primitiveIndexSize;
  uint32_t _drawBufferBindingIndex;
  NS::String *_debugLabel;
  bool _viewportSet;
  bool _scissorRectSet;
  bool _enableParallelEncoder;
  bool _primitiveTypeChanged;
  uint32_t _maxNumEncoders;
  HgiMetalStepFunctions _stepFunctions;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
