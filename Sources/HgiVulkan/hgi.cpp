//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HgiVulkan/hgi.h"
#include "Hgi/debugCodes.h"
#include "HgiVulkan/blitCmds.h"
#include "HgiVulkan/buffer.h"
#include "HgiVulkan/capabilities.h"
#include "HgiVulkan/commandQueue.h"
#include "HgiVulkan/computeCmds.h"
#include "HgiVulkan/computePipeline.h"
#include "HgiVulkan/device.h"
#include "HgiVulkan/diagnostic.h"
#include "HgiVulkan/garbageCollector.h"
#include "HgiVulkan/graphicsCmds.h"
#include "HgiVulkan/graphicsPipeline.h"
#include "HgiVulkan/instance.h"
#include "HgiVulkan/resourceBindings.h"
#include "HgiVulkan/sampler.h"
#include "HgiVulkan/shaderFunction.h"
#include "HgiVulkan/shaderProgram.h"
#include "HgiVulkan/texture.h"

#include "Trace/traceImpl.h"

#include "Tf/envSetting.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType t = TfType::Define<HgiVulkan, TfType::Bases<Hgi>>();
  t.SetFactory<HgiFactory<HgiVulkan>>();
}

HgiVulkan::HgiVulkan()
    : _instance(new HgiVulkanInstance()),
      _device(new HgiVulkanDevice(_instance)),
      _garbageCollector(new HgiVulkanGarbageCollector(this)),
      _threadId(std::this_thread::get_id()),
      _frameDepth(0)
{
}

HgiVulkan::~HgiVulkan()
{
  HgiVulkanCommandQueue *queue = _device->GetCommandQueue();

  // Wait for command buffers to complete, then reset command buffers for
  // each device's queue.
  queue->ResetConsumedCommandBuffers(HgiSubmitWaitTypeWaitUntilCompleted);

  // Wait for all devices and perform final garbage collection.
  _device->WaitForIdle();
  _garbageCollector->PerformGarbageCollection(_device);
  delete _garbageCollector;
  delete _device;
  delete _instance;
}

bool HgiVulkan::IsBackendSupported() const
{
  // Want Vulkan 1.2 or higher.
  const uint32_t apiVersion = GetCapabilities()->GetAPIVersion();
  const uint32_t majorVersion = VK_VERSION_MAJOR(apiVersion);
  const uint32_t minorVersion = VK_VERSION_MINOR(apiVersion);

  bool support = (majorVersion > 1) || ((majorVersion == 1) && (minorVersion >= 2));
  if (!support) {
    TF_DEBUG(HGI_DEBUG_IS_SUPPORTED)
        .Msg(
            "HgiVulkan unsupported due to Vulkan API version: %d.%d "
            "(must be >= 1.2)\n",
            majorVersion,
            minorVersion);
  }
  return support;
}

/* Multi threaded */
HgiGraphicsCmdsUniquePtr HgiVulkan::CreateGraphicsCmds(HgiGraphicsCmdsDesc const &desc)
{
  HgiVulkanGraphicsCmds *cmds(new HgiVulkanGraphicsCmds(this, desc));
  return HgiGraphicsCmdsUniquePtr(cmds);
}

/* Multi threaded */
HgiBlitCmdsUniquePtr HgiVulkan::CreateBlitCmds()
{
  return HgiBlitCmdsUniquePtr(new HgiVulkanBlitCmds(this));
}

HgiComputeCmdsUniquePtr HgiVulkan::CreateComputeCmds(HgiComputeCmdsDesc const &desc)
{
  HgiVulkanComputeCmds *cmds(new HgiVulkanComputeCmds(this, desc));
  return HgiComputeCmdsUniquePtr(cmds);
}

/* Multi threaded */
HgiTextureHandle HgiVulkan::CreateTexture(HgiTextureDesc const &desc)
{
  return HgiTextureHandle(new HgiVulkanTexture(this, GetPrimaryDevice(), desc), GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroyTexture(HgiTextureHandle *texHandle)
{
  TrashObject(texHandle, GetGarbageCollector()->GetTextureList());
}

/* Multi threaded */
HgiTextureViewHandle HgiVulkan::CreateTextureView(HgiTextureViewDesc const &desc)
{
  if (!desc.sourceTexture) {
    TF_CODING_ERROR("Source texture is null");
  }

  HgiTextureHandle src = HgiTextureHandle(new HgiVulkanTexture(this, GetPrimaryDevice(), desc),
                                          GetUniqueId());
  HgiTextureView *view = new HgiTextureView(desc);
  view->SetViewTexture(src);
  return HgiTextureViewHandle(view, GetUniqueId());
}

void HgiVulkan::DestroyTextureView(HgiTextureViewHandle *viewHandle)
{
  // Trash the texture inside the view and invalidate the view handle.
  HgiTextureHandle texHandle = (*viewHandle)->GetViewTexture();
  TrashObject(&texHandle, GetGarbageCollector()->GetTextureList());
  (*viewHandle)->SetViewTexture(HgiTextureHandle());
  delete viewHandle->Get();
  *viewHandle = HgiTextureViewHandle();
}

/* Multi threaded */
HgiSamplerHandle HgiVulkan::CreateSampler(HgiSamplerDesc const &desc)
{
  return HgiSamplerHandle(new HgiVulkanSampler(GetPrimaryDevice(), desc), GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroySampler(HgiSamplerHandle *smpHandle)
{
  TrashObject(smpHandle, GetGarbageCollector()->GetSamplerList());
}

/* Multi threaded */
HgiBufferHandle HgiVulkan::CreateBuffer(HgiBufferDesc const &desc)
{
  return HgiBufferHandle(new HgiVulkanBuffer(this, GetPrimaryDevice(), desc), GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroyBuffer(HgiBufferHandle *bufHandle)
{
  TrashObject(bufHandle, GetGarbageCollector()->GetBufferList());
}

/* Multi threaded */
HgiShaderFunctionHandle HgiVulkan::CreateShaderFunction(HgiShaderFunctionDesc const &desc)
{
  return HgiShaderFunctionHandle(
      new HgiVulkanShaderFunction(
          GetPrimaryDevice(), this, desc, GetCapabilities()->GetShaderVersion()),
      GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroyShaderFunction(HgiShaderFunctionHandle *shaderFnHandle)
{
  TrashObject(shaderFnHandle, GetGarbageCollector()->GetShaderFunctionList());
}

/* Multi threaded */
HgiShaderProgramHandle HgiVulkan::CreateShaderProgram(HgiShaderProgramDesc const &desc)
{
  return HgiShaderProgramHandle(new HgiVulkanShaderProgram(GetPrimaryDevice(), desc),
                                GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroyShaderProgram(HgiShaderProgramHandle *shaderPrgHandle)
{
  TrashObject(shaderPrgHandle, GetGarbageCollector()->GetShaderProgramList());
}

/* Multi threaded */
HgiResourceBindingsHandle HgiVulkan::CreateResourceBindings(HgiResourceBindingsDesc const &desc)
{
  return HgiResourceBindingsHandle(new HgiVulkanResourceBindings(GetPrimaryDevice(), desc),
                                   GetUniqueId());
}

/* Multi threaded */
void HgiVulkan::DestroyResourceBindings(HgiResourceBindingsHandle *resHandle)
{
  TrashObject(resHandle, GetGarbageCollector()->GetResourceBindingsList());
}

HgiGraphicsPipelineHandle HgiVulkan::CreateGraphicsPipeline(HgiGraphicsPipelineDesc const &desc)
{
  return HgiGraphicsPipelineHandle(new HgiVulkanGraphicsPipeline(GetPrimaryDevice(), desc),
                                   GetUniqueId());
}

void HgiVulkan::DestroyGraphicsPipeline(HgiGraphicsPipelineHandle *pipeHandle)
{
  TrashObject(pipeHandle, GetGarbageCollector()->GetGraphicsPipelineList());
}

HgiComputePipelineHandle HgiVulkan::CreateComputePipeline(HgiComputePipelineDesc const &desc)
{
  return HgiComputePipelineHandle(new HgiVulkanComputePipeline(GetPrimaryDevice(), desc),
                                  GetUniqueId());
}

void HgiVulkan::DestroyComputePipeline(HgiComputePipelineHandle *pipeHandle)
{
  TrashObject(pipeHandle, GetGarbageCollector()->GetComputePipelineList());
}

/* Multi threaded */
TfToken const &HgiVulkan::GetAPIName() const
{
  return HgiTokens->Vulkan;
}

/* Multi threaded */
HgiVulkanCapabilities const *HgiVulkan::GetCapabilities() const
{
  return &_device->GetDeviceCapabilities();
}

HgiIndirectCommandEncoder *HgiVulkan::GetIndirectCommandEncoder() const
{
  return nullptr;
}

/* Single threaded */
void HgiVulkan::StartFrame()
{
  // Please read important usage limitations for Hgi::StartFrame

  if (_frameDepth++ == 0) {
    HgiVulkanBeginQueueLabel(GetPrimaryDevice(), "Full Hydra Frame");
  }
}

/* Single threaded */
void HgiVulkan::EndFrame()
{
  // Please read important usage limitations for Hgi::EndFrame

  if (--_frameDepth == 0) {
    _EndFrameSync();
    HgiVulkanEndQueueLabel(GetPrimaryDevice());
  }
}

/* Multi threaded */
HgiVulkanInstance *HgiVulkan::GetVulkanInstance() const
{
  return _instance;
}

/* Multi threaded */
HgiVulkanDevice *HgiVulkan::GetPrimaryDevice() const
{
  return _device;
}

/* Multi threaded */
HgiVulkanGarbageCollector *HgiVulkan::GetGarbageCollector() const
{
  return _garbageCollector;
}

/* Single threaded */
bool HgiVulkan::_SubmitCmds(HgiCmds *cmds, HgiSubmitWaitType wait)
{
  TRACE_FUNCTION();

  // XXX The device queue is externally synchronized so we would at minimum
  // need a mutex here to ensure only one thread submits cmds at a time.
  // However, since we currently call garbage collection here and because
  // we only have one resource command buffer, we cannot support submitting
  // cmds from secondary threads until those issues are resolved.
  if (ARCH_UNLIKELY(_threadId != std::this_thread::get_id())) {
    TF_CODING_ERROR("Secondary threads should not submit cmds");
    return false;
  }

  // Submit Cmds work
  bool result = false;
  if (cmds) {
    result = Hgi::_SubmitCmds(cmds, wait);
  }

  // XXX If client does not call StartFrame / EndFrame we perform end of frame
  // cleanup after each SubmitCmds. This is more frequent than ideal and also
  // prevents us from making SubmitCmds thread-safe.
  if (_frameDepth == 0) {
    _EndFrameSync();
  }

  return result;
}

/* Single threaded */
void HgiVulkan::_EndFrameSync()
{
  // The garbage collector and command buffer reset must happen on the
  // main-thread when no threads are recording.
  if (ARCH_UNLIKELY(_threadId != std::this_thread::get_id())) {
    TF_CODING_ERROR("Secondary thread violation");
    return;
  }

  HgiVulkanDevice *device = GetPrimaryDevice();
  HgiVulkanCommandQueue *queue = device->GetCommandQueue();

  // Reset command buffers for each device's queue.
  queue->ResetConsumedCommandBuffers();

  // Perform garbage collection for each device.
  _garbageCollector->PerformGarbageCollection(device);
}

PXR_NAMESPACE_CLOSE_SCOPE
