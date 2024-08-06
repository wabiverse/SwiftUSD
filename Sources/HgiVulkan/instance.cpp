//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HgiVulkan/instance.h"
#include "HgiVulkan/diagnostic.h"

#include "Tf/diagnostic.h"
#include "Tf/iterator.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

static bool _CheckInstanceValidationLayerSupport(const char *layerName)
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
  std::vector<VkLayerProperties> availableLayers(layerCount);

  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for (const auto &layerProperties : availableLayers) {
    if (strcmp(layerName, layerProperties.layerName) == 0) {
      return true;
    }
  }

  return false;
}

HgiVulkanInstance::HgiVulkanInstance()
    : vkDebugMessenger(nullptr),
      vkCreateDebugUtilsMessengerEXT(nullptr),
      vkDestroyDebugUtilsMessengerEXT(nullptr),
      _vkInstance(nullptr)
{
  VkApplicationInfo appInfo = {VK_STRUCTURE_TYPE_APPLICATION_INFO};
  appInfo.apiVersion = VK_API_VERSION_1_3;

  VkInstanceCreateInfo createInfo = {VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO};
  createInfo.pApplicationInfo = &appInfo;

  // Setup instance extensions.
  std::vector<const char *> extensions = {
      VK_KHR_SURFACE_EXTENSION_NAME,

// Pick platform specific surface extension
#if defined(VK_USE_PLATFORM_WIN32_KHR)
      VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
#elif defined(VK_USE_PLATFORM_XLIB_KHR)
      VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
      VK_MVK_MACOS_SURFACE_EXTENSION_NAME,
#else
#  error Unsupported Platform
#endif

      // Extensions for interop with OpenGL
      VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME,
      VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME,

      VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME,
  };

  // Enable validation layers extension.
  // Requires VK_LAYER_PATH to be set.
  const std::vector<const char *> debugLayers = {"VK_LAYER_KHRONOS_validation"};
  if (HgiVulkanIsDebugEnabled()) {
    for (const auto &debugLayer : debugLayers) {
      if (!_CheckInstanceValidationLayerSupport(debugLayer)) {
        TF_WARN(
            "Instance layer %s is not present, instance "
            "creation will fail",
            debugLayer);
      }
    }
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    createInfo.ppEnabledLayerNames = debugLayers.data();
    createInfo.enabledLayerCount = (uint32_t)debugLayers.size();
  }

  createInfo.ppEnabledExtensionNames = extensions.data();
  createInfo.enabledExtensionCount = (uint32_t)extensions.size();

  TF_VERIFY(vkCreateInstance(&createInfo, HgiVulkanAllocator(), &_vkInstance) == VK_SUCCESS);

  HgiVulkanCreateDebug(this);
}

HgiVulkanInstance::~HgiVulkanInstance()
{
  HgiVulkanDestroyDebug(this);
  vkDestroyInstance(_vkInstance, HgiVulkanAllocator());
}

VkInstance const &HgiVulkanInstance::GetVulkanInstance() const
{
  return _vkInstance;
}

PXR_NAMESPACE_CLOSE_SCOPE
