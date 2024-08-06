//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_BUFFER_H
#define PXR_IMAGING_HGI_METAL_BUFFER_H

#include <Metal/Metal.hpp>

#include "Hgi/buffer.h"
#include "HgiMetal/api.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class HgiMetal;

/// \class HgiMetalBuffer
///
/// Represents a Metal GPU buffer resource.
///
class HgiMetalBuffer final : public HgiBuffer {
 public:
  HGIMETAL_API
  HgiMetalBuffer(HgiMetal *hgi, HgiBufferDesc const &desc);

  HGIMETAL_API
  ~HgiMetalBuffer() override;

  HGIMETAL_API
  size_t GetByteSizeOfResource() const override;

  HGIMETAL_API
  uint64_t GetRawResource() const override;

  HGIMETAL_API
  void *GetCPUStagingAddress() override;

  MTL::Buffer* GetBufferId() const
  {
    return _bufferId;
  }

 private:
  HgiMetalBuffer() = delete;
  HgiMetalBuffer &operator=(const HgiMetalBuffer &) = delete;
  HgiMetalBuffer(const HgiMetalBuffer &) = delete;

  MTL::Buffer* _bufferId;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
