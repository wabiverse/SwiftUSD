//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGIVULKAN_HGI_H
#define PXR_IMAGING_HGIVULKAN_HGI_H

#include "Hgi/hgi.h"
#include "Hgi/tokens.h"
#include "pxr/pxrns.h"

#include "HgiVulkan/api.h"
#include "HgiVulkan/capabilities.h"
#include "HgiVulkan/commandQueue.h"
#include "HgiVulkan/device.h"
#include "HgiVulkan/vulkan.h"

#include <thread>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class HgiVulkanGarbageCollector;
class HgiVulkanInstance;

/// \class HgiVulkan
///
/// Vulkan implementation of the Hydra Graphics Interface.
///
class HgiVulkan final : public Hgi {
 public:
  HGIVULKAN_API
  HgiVulkan();

  HGIVULKAN_API
  ~HgiVulkan() override;

  HGIVULKAN_API
  bool IsBackendSupported() const override;

  HGIVULKAN_API
  HgiGraphicsCmdsUniquePtr CreateGraphicsCmds(HgiGraphicsCmdsDesc const &desc) override;

  HGIVULKAN_API
  HgiBlitCmdsUniquePtr CreateBlitCmds() override;

  HGIVULKAN_API
  HgiComputeCmdsUniquePtr CreateComputeCmds(HgiComputeCmdsDesc const &desc) override;

  HGIVULKAN_API
  HgiTextureHandle CreateTexture(HgiTextureDesc const &desc) override;

  HGIVULKAN_API
  void DestroyTexture(HgiTextureHandle *texHandle) override;

  HGIVULKAN_API
  HgiTextureViewHandle CreateTextureView(HgiTextureViewDesc const &desc) override;

  HGIVULKAN_API
  void DestroyTextureView(HgiTextureViewHandle *viewHandle) override;

  HGIVULKAN_API
  HgiSamplerHandle CreateSampler(HgiSamplerDesc const &desc) override;

  HGIVULKAN_API
  void DestroySampler(HgiSamplerHandle *smpHandle) override;

  HGIVULKAN_API
  HgiBufferHandle CreateBuffer(HgiBufferDesc const &desc) override;

  HGIVULKAN_API
  void DestroyBuffer(HgiBufferHandle *bufHandle) override;

  HGIVULKAN_API
  HgiShaderFunctionHandle CreateShaderFunction(HgiShaderFunctionDesc const &desc) override;

  HGIVULKAN_API
  void DestroyShaderFunction(HgiShaderFunctionHandle *shaderFunctionHandle) override;

  HGIVULKAN_API
  HgiShaderProgramHandle CreateShaderProgram(HgiShaderProgramDesc const &desc) override;

  HGIVULKAN_API
  void DestroyShaderProgram(HgiShaderProgramHandle *shaderProgramHandle) override;

  HGIVULKAN_API
  HgiResourceBindingsHandle CreateResourceBindings(HgiResourceBindingsDesc const &desc) override;

  HGIVULKAN_API
  void DestroyResourceBindings(HgiResourceBindingsHandle *resHandle) override;

  HGIVULKAN_API
  HgiGraphicsPipelineHandle CreateGraphicsPipeline(
      HgiGraphicsPipelineDesc const &pipeDesc) override;

  HGIVULKAN_API
  void DestroyGraphicsPipeline(HgiGraphicsPipelineHandle *pipeHandle) override;

  HGIVULKAN_API
  HgiComputePipelineHandle CreateComputePipeline(HgiComputePipelineDesc const &pipeDesc) override;

  HGIVULKAN_API
  void DestroyComputePipeline(HgiComputePipelineHandle *pipeHandle) override;

  HGIVULKAN_API
  TfToken const &GetAPIName() const override;

  HGIVULKAN_API
  HgiVulkanCapabilities const *GetCapabilities() const override;

  HGIVULKAN_API
  HgiIndirectCommandEncoder *GetIndirectCommandEncoder() const override;

  HGIVULKAN_API
  void StartFrame() override;

  HGIVULKAN_API
  void EndFrame() override;

  //
  // HgiVulkan specific
  //

  /// Returns the Hgi vulkan instance.
  /// Thread safety: Yes.
  HGIVULKAN_API
  HgiVulkanInstance *GetVulkanInstance() const;

  /// Returns the primary (presentation) vulkan device.
  /// Thread safety: Yes.
  HGIVULKAN_API
  HgiVulkanDevice *GetPrimaryDevice() const;

  /// Returns the garbage collector.
  /// Thread safety: Yes.
  HGIVULKAN_API
  HgiVulkanGarbageCollector *GetGarbageCollector() const;

  /// Invalidates the resource handle and places the object in the garbage
  /// collector vector for future destruction.
  /// This is helpful to avoid destroying GPU resources still in-flight.
  template<class T, class H> void TrashObject(H *handle, std::vector<T *> *collector)
  {
    T *object = static_cast<T *>(handle->Get());
    if (object) {
      HgiVulkanDevice *device = object->GetDevice();
      HgiVulkanCommandQueue *queue = device->GetCommandQueue();
      object->GetInflightBits() = queue->GetInflightCommandBuffersBits();
      collector->push_back(object);
    }

    *handle = H();
  }

 protected:
  HGIVULKAN_API
  bool _SubmitCmds(HgiCmds *cmds, HgiSubmitWaitType wait) override;

 private:
  HgiVulkan &operator=(const HgiVulkan &) = delete;
  HgiVulkan(const HgiVulkan &) = delete;

  // Perform low frequency actions, such as garbage collection.
  // Thread safety: No. Must be called from main thread.
  void _EndFrameSync();

  HgiVulkanInstance *_instance;
  HgiVulkanDevice *_device;
  HgiVulkanGarbageCollector *_garbageCollector;
  std::thread::id _threadId;
  int _frameDepth;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
