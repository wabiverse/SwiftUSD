//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_SAMPLER_H
#define PXR_IMAGING_HGI_METAL_SAMPLER_H

#include "Hgi/sampler.h"

#include "HgiMetal/api.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

class HgiMetal;

///
/// \class HgiMetalSampler
///
/// Metal implementation of HgiSampler
///
class HgiMetalSampler final : public HgiSampler {
 public:
  HGIMETAL_API
  HgiMetalSampler(HgiMetal *hgi, HgiSamplerDesc const &desc);

  HGIMETAL_API
  ~HgiMetalSampler() override;

  HGIMETAL_API
  uint64_t GetRawResource() const override;

  HGIMETAL_API
  MTL::SamplerState* GetSamplerId() const;

 private:
  HgiMetalSampler() = delete;
  HgiMetalSampler &operator=(const HgiMetalSampler &) = delete;
  HgiMetalSampler(const HgiMetalSampler &) = delete;

 private:
  MTL::SamplerState* _samplerId;
  NS::String *_label;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
