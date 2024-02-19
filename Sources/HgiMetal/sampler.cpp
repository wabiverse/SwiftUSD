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
#include <Metal/Metal.hpp>

#include "HgiMetal/conversions.h"
#include "HgiMetal/diagnostic.h"
#include "HgiMetal/hgi.h"
#include "HgiMetal/sampler.h"

PXR_NAMESPACE_OPEN_SCOPE

HgiMetalSampler::HgiMetalSampler(HgiMetal *hgi, HgiSamplerDesc const &desc)
    : HgiSampler(desc), _samplerId(nil), _label(nil)
{
  MTL::SamplerDescriptor *smpDesc = MTL::SamplerDescriptor::alloc()->init();

  smpDesc->setSAddressMode(HgiMetalConversions::GetSamplerAddressMode(desc.addressModeU));
  smpDesc->setTAddressMode(HgiMetalConversions::GetSamplerAddressMode(desc.addressModeV));
  smpDesc->setRAddressMode(HgiMetalConversions::GetSamplerAddressMode(desc.addressModeW));
  smpDesc->setMinFilter(HgiMetalConversions::GetMinMagFilter(desc.magFilter));
  smpDesc->setMagFilter(HgiMetalConversions::GetMinMagFilter(desc.minFilter));
  smpDesc->setMipFilter(HgiMetalConversions::GetMipFilter(desc.mipFilter));
  smpDesc->setSupportArgumentBuffers(true);
  smpDesc->setBorderColor(HgiMetalConversions::GetBorderColor(desc.borderColor));
  smpDesc->setCompareFunction(HgiMetalConversions::GetCompareFunction(desc.compareFunction));

  HGIMETAL_DEBUG_LABEL(smpDesc, _descriptor.debugName.c_str());

  _samplerId = hgi->GetPrimaryDevice()->newSamplerState(smpDesc);

  smpDesc->release();
}

HgiMetalSampler::~HgiMetalSampler()
{
  if (_label)
  {
    _label->release();
    _label = nil;
  }

  if (_samplerId != nil)
  {
    _samplerId->release();
    _samplerId = nil;
  }
}

uint64_t
HgiMetalSampler::GetRawResource() const
{
  return (uint64_t)_samplerId;
}

MTL::SamplerState *
HgiMetalSampler::GetSamplerId() const
{
  return _samplerId;
}

PXR_NAMESPACE_CLOSE_SCOPE
