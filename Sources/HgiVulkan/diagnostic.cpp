//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HgiVulkan/diagnostic.h"
#include "HgiVulkan/commandBuffer.h"
#include "HgiVulkan/commandQueue.h"
#include "HgiVulkan/device.h"
#include "HgiVulkan/instance.h"
#include "HgiVulkan/vulkan.h"

#include "Tf/diagnostic.h"
#include "Tf/envSetting.h"

#include <cstring>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(HGIVULKAN_DEBUG, 0, "Enable debugging for HgiVulkan");
TF_DEFINE_ENV_SETTING(HGIVULKAN_DEBUG_VERBOSE, 0, "Enable verbose debugging for HgiVulkan");

bool HgiVulkanIsDebugEnabled()
{
  static bool _v = TfGetEnvSetting(HGIVULKAN_DEBUG) == 1;
  return _v;
}

bool HgiVulkanIsVerboseDebugEnabled()
{
  static bool _v = TfGetEnvSetting(HGIVULKAN_DEBUG_VERBOSE) == 1;
  return _v;
}

VKAPI_ATTR VkBool32 VKAPI_CALL
_VulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity,
                     VkDebugUtilsMessageTypeFlagsEXT msgType,
                     const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                     void *userData)
{
  const char *type = (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) ? "VULKAN_ERROR" :
                                                                                  "VULKAN_MESSAGE";

  if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
    TF_CODING_ERROR("%s: %s\n", type, callbackData->pMessage);
  }
  else {
    TF_WARN("%s: %s\n", type, callbackData->pMessage);
  }

  return VK_FALSE;
}

void HgiVulkanCreateDebug(HgiVulkanInstance *instance)
{
  if (!HgiVulkanIsDebugEnabled()) {
    return;
  }

  VkInstance vkInstance = instance->GetVulkanInstance();

  instance->vkCreateDebugUtilsMessengerEXT = (PFN_vkCreateDebugUtilsMessengerEXT)
      vkGetInstanceProcAddr(vkInstance, "vkCreateDebugUtilsMessengerEXT");

  instance->vkDestroyDebugUtilsMessengerEXT = (PFN_vkDestroyDebugUtilsMessengerEXT)
      vkGetInstanceProcAddr(vkInstance, "vkDestroyDebugUtilsMessengerEXT");

  if (!TF_VERIFY(instance->vkCreateDebugUtilsMessengerEXT)) {
    return;
  }
  if (!TF_VERIFY(instance->vkDestroyDebugUtilsMessengerEXT)) {
    return;
  }

  VkDebugUtilsMessengerCreateInfoEXT dbgMsgCreateInfo = {
      VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT};
  dbgMsgCreateInfo.pNext = nullptr;
  dbgMsgCreateInfo.flags = 0;
  dbgMsgCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                     VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

  // Verbose debugging will cause many bits of information to be printed by
  // the vulkan validation layers. It is only useful for debugging.
  if (HgiVulkanIsVerboseDebugEnabled()) {
    dbgMsgCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                        VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
  }

  dbgMsgCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                 VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  dbgMsgCreateInfo.pfnUserCallback = _VulkanDebugCallback;
  dbgMsgCreateInfo.pUserData = nullptr;

  TF_VERIFY(instance->vkCreateDebugUtilsMessengerEXT(vkInstance,
                                                     &dbgMsgCreateInfo,
                                                     HgiVulkanAllocator(),
                                                     &instance->vkDebugMessenger) == VK_SUCCESS);
}

void HgiVulkanDestroyDebug(HgiVulkanInstance *instance)
{
  if (!HgiVulkanIsDebugEnabled()) {
    return;
  }

  VkInstance vkInstance = instance->GetVulkanInstance();

  if (!TF_VERIFY(instance->vkDestroyDebugUtilsMessengerEXT)) {
    return;
  }

  instance->vkDestroyDebugUtilsMessengerEXT(
      vkInstance, instance->vkDebugMessenger, HgiVulkanAllocator());
}

void HgiVulkanSetupDeviceDebug(HgiVulkanInstance *instance, HgiVulkanDevice *device)
{
  VkInstance vkInstance = instance->GetVulkanInstance();
  device->vkCmdBeginDebugUtilsLabelEXT = (PFN_vkCmdBeginDebugUtilsLabelEXT)vkGetInstanceProcAddr(
      vkInstance, "vkCmdBeginDebugUtilsLabelEXT");

  device->vkCmdEndDebugUtilsLabelEXT = (PFN_vkCmdEndDebugUtilsLabelEXT)vkGetInstanceProcAddr(
      vkInstance, "vkCmdEndDebugUtilsLabelEXT");

  device->vkCmdInsertDebugUtilsLabelEXT = (PFN_vkCmdInsertDebugUtilsLabelEXT)vkGetInstanceProcAddr(
      vkInstance, "vkCmdInsertDebugUtilsLabelEXT");

  device->vkSetDebugUtilsObjectNameEXT = (PFN_vkSetDebugUtilsObjectNameEXT)vkGetInstanceProcAddr(
      vkInstance, "vkSetDebugUtilsObjectNameEXT");

  device->vkQueueBeginDebugUtilsLabelEXT = (PFN_vkQueueBeginDebugUtilsLabelEXT)
      vkGetInstanceProcAddr(vkInstance, "vkQueueBeginDebugUtilsLabelEXT");

  device->vkQueueEndDebugUtilsLabelEXT = (PFN_vkQueueEndDebugUtilsLabelEXT)vkGetInstanceProcAddr(
      vkInstance, "vkQueueEndDebugUtilsLabelEXT");
}

void HgiVulkanSetDebugName(HgiVulkanDevice *device,
                           uint64_t vulkanObject,
                           VkObjectType objectType,
                           const char *name)
{
  if (!HgiVulkanIsDebugEnabled() || !name) {
    return;
  }

  if (!TF_VERIFY(device && device->vkSetDebugUtilsObjectNameEXT)) {
    return;
  }

  VkDebugUtilsObjectNameInfoEXT debugInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT};
  debugInfo.objectHandle = vulkanObject;
  debugInfo.objectType = objectType;
  debugInfo.pObjectName = name;
  device->vkSetDebugUtilsObjectNameEXT(device->GetVulkanDevice(), &debugInfo);
}

void HgiVulkanBeginLabel(HgiVulkanDevice *device, HgiVulkanCommandBuffer *cb, const char *label)
{
  if (!HgiVulkanIsDebugEnabled() || !label) {
    return;
  }

  VkCommandBuffer vkCmbuf = cb->GetVulkanCommandBuffer();
  VkDebugUtilsLabelEXT labelInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT};
  labelInfo.pLabelName = label;
  device->vkCmdBeginDebugUtilsLabelEXT(vkCmbuf, &labelInfo);
}

void HgiVulkanEndLabel(HgiVulkanDevice *device, HgiVulkanCommandBuffer *cb)
{
  if (!HgiVulkanIsDebugEnabled()) {
    return;
  }

  VkCommandBuffer vkCmbuf = cb->GetVulkanCommandBuffer();
  device->vkCmdEndDebugUtilsLabelEXT(vkCmbuf);
}

void HgiVulkanBeginQueueLabel(HgiVulkanDevice *device, const char *label)
{
  if (!HgiVulkanIsDebugEnabled() || !label) {
    return;
  }

  VkQueue gfxQueue = device->GetCommandQueue()->GetVulkanGraphicsQueue();
  VkDebugUtilsLabelEXT labelInfo = {VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT};
  labelInfo.pLabelName = label;
  device->vkQueueBeginDebugUtilsLabelEXT(gfxQueue, &labelInfo);
}

void HgiVulkanEndQueueLabel(HgiVulkanDevice *device)
{
  if (!HgiVulkanIsDebugEnabled()) {
    return;
  }

  VkQueue gfxQueue = device->GetCommandQueue()->GetVulkanGraphicsQueue();
  device->vkQueueEndDebugUtilsLabelEXT(gfxQueue);
}

PXR_NAMESPACE_CLOSE_SCOPE
