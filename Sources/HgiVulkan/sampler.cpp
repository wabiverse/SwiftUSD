//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/diagnostic.h"

#include "HgiVulkan/capabilities.h"
#include "HgiVulkan/conversions.h"
#include "HgiVulkan/device.h"
#include "HgiVulkan/sampler.h"

#include <float.h>

PXR_NAMESPACE_OPEN_SCOPE

HgiVulkanSampler::HgiVulkanSampler(HgiVulkanDevice *device, HgiSamplerDesc const &desc)
    : HgiSampler(desc), _vkSampler(nullptr), _device(device), _inflightBits(0)
{
  VkSamplerCreateInfo sampler = {VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO};
  sampler.magFilter = HgiVulkanConversions::GetMinMagFilter(desc.magFilter);
  sampler.minFilter = HgiVulkanConversions::GetMinMagFilter(desc.minFilter);
  sampler.addressModeU = HgiVulkanConversions::GetSamplerAddressMode(desc.addressModeU);
  sampler.addressModeV = HgiVulkanConversions::GetSamplerAddressMode(desc.addressModeV);
  sampler.addressModeW = HgiVulkanConversions::GetSamplerAddressMode(desc.addressModeW);

  // Eg. Percentage-closer filtering
  sampler.compareEnable = desc.enableCompare ? VK_TRUE : VK_FALSE;
  sampler.compareOp = HgiVulkanConversions::GetDepthCompareFunction(desc.compareFunction);

  sampler.borderColor = HgiVulkanConversions::GetBorderColor(desc.borderColor);
  sampler.mipLodBias = 0.0f;
  sampler.mipmapMode = HgiVulkanConversions::GetMipFilter(desc.mipFilter);
  sampler.minLod = 0.0f;
  sampler.maxLod = FLT_MAX;

  if ((desc.minFilter != HgiSamplerFilterNearest || desc.mipFilter == HgiMipFilterLinear) &&
      desc.magFilter != HgiSamplerFilterNearest)
  {
    HgiVulkanCapabilities const &caps = device->GetDeviceCapabilities();
    sampler.anisotropyEnable = caps.vkDeviceFeatures.samplerAnisotropy;
    sampler.maxAnisotropy = sampler.anisotropyEnable ?
                                caps.vkDeviceProperties.limits.maxSamplerAnisotropy :
                                1.0f;
  }

  TF_VERIFY(
      vkCreateSampler(device->GetVulkanDevice(), &sampler, HgiVulkanAllocator(), &_vkSampler) ==
      VK_SUCCESS);
}

HgiVulkanSampler::~HgiVulkanSampler()
{
  vkDestroySampler(_device->GetVulkanDevice(), _vkSampler, HgiVulkanAllocator());
}

uint64_t HgiVulkanSampler::GetRawResource() const
{
  return (uint64_t)_vkSampler;
}

VkSampler HgiVulkanSampler::GetVulkanSampler() const
{
  return _vkSampler;
}

HgiVulkanDevice *HgiVulkanSampler::GetDevice() const
{
  return _device;
}

uint64_t &HgiVulkanSampler::GetInflightBits()
{
  return _inflightBits;
}

PXR_NAMESPACE_CLOSE_SCOPE
