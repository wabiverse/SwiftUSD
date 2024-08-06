//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_HGIMETAL_H
#define PXR_IMAGING_HGI_METAL_HGIMETAL_H

#include "Hgi/hgiImpl.h"
#include "Hgi/tokens.h"
#include "HgiMetal/api.h"
#include "HgiMetal/capabilities.h"
#include "HgiMetal/indirectCommandEncoder.h"
#include "pxr/pxrns.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>
#include <stack>

PXR_NAMESPACE_OPEN_SCOPE

using HgiMetalPtr = std::shared_ptr<class HgiMetal>;

enum { APIVersion_Metal1_0 = 0, APIVersion_Metal2_0, APIVersion_Metal3_0 };

/// \class HgiMetal
///
/// Metal implementation of the Hydra Graphics Interface.
///
class HgiMetal final : public Hgi {
 public:
  enum CommitCommandBufferWaitType {
    CommitCommandBuffer_NoWait = 0,
    CommitCommandBuffer_WaitUntilScheduled,
    CommitCommandBuffer_WaitUntilCompleted
  };

  HGIMETAL_API
  HgiMetal(MTL::Device* device = nil);

  HGIMETAL_API
  ~HgiMetal() override;

  HGIMETAL_API
  static HgiMetalPtr CreateHgi();

  HGIMETAL_API
  bool IsBackendSupported() const override;

  HGIMETAL_API
  HgiGraphicsCmdsUniquePtr CreateGraphicsCmds(HgiGraphicsCmdsDesc const &desc) override;

  HGIMETAL_API
  HgiComputeCmdsUniquePtr CreateComputeCmds(HgiComputeCmdsDesc const &desc) override;

  HGIMETAL_API
  HgiBlitCmdsUniquePtr CreateBlitCmds() override;

  HGIMETAL_API
  HgiTextureHandle CreateTexture(HgiTextureDesc const &desc) override;

  HGIMETAL_API
  void DestroyTexture(HgiTextureHandle *texHandle) override;

  HGIMETAL_API
  HgiTextureViewHandle CreateTextureView(HgiTextureViewDesc const &desc) override;

  HGIMETAL_API
  void DestroyTextureView(HgiTextureViewHandle *viewHandle) override;

  HGIMETAL_API
  HgiSamplerHandle CreateSampler(HgiSamplerDesc const &desc) override;

  HGIMETAL_API
  void DestroySampler(HgiSamplerHandle *smpHandle) override;

  HGIMETAL_API
  HgiBufferHandle CreateBuffer(HgiBufferDesc const &desc) override;

  HGIMETAL_API
  void DestroyBuffer(HgiBufferHandle *texHandle) override;

  HGIMETAL_API
  HgiShaderFunctionHandle CreateShaderFunction(HgiShaderFunctionDesc const &desc) override;

  HGIMETAL_API
  void DestroyShaderFunction(HgiShaderFunctionHandle *shaderFunctionHandle) override;

  HGIMETAL_API
  HgiShaderProgramHandle CreateShaderProgram(HgiShaderProgramDesc const &desc) override;

  HGIMETAL_API
  void DestroyShaderProgram(HgiShaderProgramHandle *shaderProgramHandle) override;

  HGIMETAL_API
  HgiResourceBindingsHandle CreateResourceBindings(HgiResourceBindingsDesc const &desc) override;

  HGIMETAL_API
  void DestroyResourceBindings(HgiResourceBindingsHandle *resHandle) override;

  HGIMETAL_API
  HgiGraphicsPipelineHandle CreateGraphicsPipeline(
      HgiGraphicsPipelineDesc const &pipeDesc) override;

  HGIMETAL_API
  void DestroyGraphicsPipeline(HgiGraphicsPipelineHandle *pipeHandle) override;

  HGIMETAL_API
  HgiComputePipelineHandle CreateComputePipeline(HgiComputePipelineDesc const &pipeDesc) override;

  HGIMETAL_API
  void DestroyComputePipeline(HgiComputePipelineHandle *pipeHandle) override;

  HGIMETAL_API
  TfToken const &GetAPIName() const override;

  HGIMETAL_API
  HgiMetalCapabilities const *GetCapabilities() const override;

  HGIMETAL_API
  HgiMetalIndirectCommandEncoder *GetIndirectCommandEncoder() const override;

  HGIMETAL_API
  void StartFrame() override;

  HGIMETAL_API
  void EndFrame() override;

  //
  // HgiMetal specific
  //

  /// Returns the primary Metal device.
  HGIMETAL_API
  MTL::Device* GetPrimaryDevice() const;

  HGIMETAL_API
  MTL::CommandQueue* GetQueue() const;

  // Metal Command buffers are heavy weight, while encoders are lightweight.
  // But we cannot have more than one active encoder at a time per cmd buf.
  // (Ideally we would have created on encoder for each HgiCmds)
  // So for the sake of efficiency, we try to create only one cmd buf and
  // only use the secondary command buffer when the client code requires it.
  // For example, the client code may record in a HgiBlitCmds and a
  // HgiComputeCmds at the same time. It is the responsibility of the
  // command buffer implementation to call SetHasWork() if there is
  // work to be submitted from the primary command buffer.
  HGIMETAL_API
  MTL::CommandBuffer* GetPrimaryCommandBuffer(HgiCmds *requester = nullptr, bool flush = true);

  HGIMETAL_API
  MTL::CommandBuffer* GetSecondaryCommandBuffer();

  HGIMETAL_API
  void SetHasWork();

  HGIMETAL_API
  int GetAPIVersion() const;

  HGIMETAL_API
  void CommitPrimaryCommandBuffer(
      CommitCommandBufferWaitType waitType = CommitCommandBuffer_NoWait,
      bool forceNewBuffer = false);

  HGIMETAL_API
  void CommitSecondaryCommandBuffer(MTL::CommandBuffer* commandBuffer,
                                    CommitCommandBufferWaitType waitType);

  HGIMETAL_API
  void ReleaseSecondaryCommandBuffer(MTL::CommandBuffer* commandBuffer);

  HGIMETAL_API
  MTL::ArgumentEncoder* GetBufferArgumentEncoder() const;
  HGIMETAL_API
  MTL::ArgumentEncoder* GetSamplerArgumentEncoder() const;
  HGIMETAL_API
  MTL::ArgumentEncoder* GetTextureArgumentEncoder() const;
  HGIMETAL_API
  MTL::Buffer* GetArgBuffer();

 protected:
  HGIMETAL_API
  bool _SubmitCmds(HgiCmds *cmds, HgiSubmitWaitType wait) override;

 private:
  HgiMetal &operator=(const HgiMetal &) = delete;
  HgiMetal(const HgiMetal &) = delete;

  // Invalidates the resource handle and destroys the object.
  // Metal's internal garbage collection will handle the rest.
  template<class T> void _TrashObject(HgiHandle<T> *handle)
  {
    delete handle->Get();
    *handle = HgiHandle<T>();
  }

  MTL::Device* _device;
  MTL::CommandQueue* _commandQueue;
  MTL::CommandBuffer* _commandBuffer;
  MTL::CaptureScope* _captureScopeFullFrame;
  MTL::ArgumentEncoder* _argEncoderBuffer;
  MTL::ArgumentEncoder* _argEncoderSampler;
  MTL::ArgumentEncoder* _argEncoderTexture;

  using _FreeArgStack = std::stack<MTL::Buffer*>;
  using _ActiveArgBuffers = std::vector<MTL::Buffer*>;
  _FreeArgStack _freeArgBuffers;
  _ActiveArgBuffers _activeArgBuffers;
  std::mutex _freeArgMutex;

  HgiCmds *_currentCmds;

  std::unique_ptr<HgiMetalCapabilities> _capabilities;
  std::unique_ptr<HgiMetalIndirectCommandEncoder> _indirectCommandEncoder;

  int _frameDepth;
  bool _workToFlush;

  NS::AutoreleasePool* _pool;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
