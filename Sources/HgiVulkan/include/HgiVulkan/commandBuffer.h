//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGIVULKAN_COMMAND_BUFFER_H
#define PXR_IMAGING_HGIVULKAN_COMMAND_BUFFER_H

#include "Hgi/enums.h"
#include "HgiVulkan/api.h"
#include "HgiVulkan/vulkan.h"
#include "pxr/pxrns.h"
#include <functional>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class HgiVulkanDevice;

using HgiVulkanCompletedHandler = std::function<void(void)>;
using HgiVulkanCompletedHandlerVector = std::vector<HgiVulkanCompletedHandler>;

/// \class HgiVulkanCommandBuffer
///
/// Represents a primary command buffer in Vulkan.
/// Command buffers are managed by the CommandQueue.
///
class HgiVulkanCommandBuffer final {
 public:
  HGIVULKAN_API
  HgiVulkanCommandBuffer(HgiVulkanDevice *device, VkCommandPool pool);

  HGIVULKAN_API
  ~HgiVulkanCommandBuffer();

  /// Ensures that the command buffer is ready to receive commands.
  /// When recording is finished, submit the command buffer to CommandQueue.
  /// The 'inflightId' must uniquely identify the command buffer amongst all
  /// in-flight command buffers.
  HGIVULKAN_API
  void BeginCommandBuffer(uint8_t inflightId);

  /// End the ability to record commands. This should be called before
  /// submitting the command buffer to the queue.
  HGIVULKAN_API
  void EndCommandBuffer();

  /// Returns true if the command buffer is recording commands or being
  /// consumed by the GPU. Returns false if command buffer is available.
  HGIVULKAN_API
  bool IsInFlight() const;

  /// Returns the vulkan command buffer.
  HGIVULKAN_API
  VkCommandBuffer GetVulkanCommandBuffer() const;

  /// Returns the vulkan command pool that allocated this command buffer.
  HGIVULKAN_API
  VkCommandPool GetVulkanCommandPool() const;

  /// Returns the fence for this command buffer that is used to track when
  /// the command buffer has been consumed by the gpu.
  HGIVULKAN_API
  VkFence GetVulkanFence() const;

  /// Returns the semaphore that will be signaled when this command buffer
  /// has been completed in the queue.
  HGIVULKAN_API
  VkSemaphore GetVulkanSemaphore() const;

  /// Resets the cmd buffer if it has been consumed by the GPU.
  /// Returns true if the command buffer was reset, false if it was not reset.
  /// 'not reset' means it is still inflight or that it was previously reset.
  /// When the command buffer was reset the 'CompletedHandler' fns will have
  /// been executed in case of GPU->CPU read back cmds.
  // If wait = HgiSubmitWaitTypeWaitUntilCompleted, the function will wait
  // for the command buffer to be consumed before continuing.
  HGIVULKAN_API
  bool ResetIfConsumedByGPU(HgiSubmitWaitType wait);

  /// Inserts a barrier so that data written to memory by commands before
  /// the barrier is available to commands after the barrier.
  HGIVULKAN_API
  void InsertMemoryBarrier(HgiMemoryBarrier barrier);

  /// Returns the id that uniquely identifies this command buffer amongst
  /// all in-flight command buffers.
  HGIVULKAN_API
  uint8_t GetInflightId() const;

  /// Returns the device that was used to create the command buffer.
  HGIVULKAN_API
  HgiVulkanDevice *GetDevice() const;

  /// Insert a function that gets run when the command buffer has been
  /// consumed ("completed") on the GPU and the cmd buf is reset.
  HGIVULKAN_API
  void AddCompletedHandler(HgiVulkanCompletedHandler const &fn);

  /// Executes any CompleteHandler functions and clears the list.
  HGIVULKAN_API
  void RunAndClearCompletedHandlers();

 private:
  HgiVulkanCommandBuffer() = delete;
  HgiVulkanCommandBuffer &operator=(const HgiVulkanCommandBuffer &) = delete;
  HgiVulkanCommandBuffer(const HgiVulkanCommandBuffer &) = delete;

  // Returns the flags that will be used to reset command buffers.
  static VkCommandBufferResetFlags _GetCommandBufferResetFlags();

  HgiVulkanDevice *_device;
  VkCommandPool _vkCommandPool;
  VkCommandBuffer _vkCommandBuffer;
  VkFence _vkFence;
  VkSemaphore _vkSemaphore;

  HgiVulkanCompletedHandlerVector _completedHandlers;

  bool _isInFlight;
  bool _isSubmitted;
  uint8_t _inflightId;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
