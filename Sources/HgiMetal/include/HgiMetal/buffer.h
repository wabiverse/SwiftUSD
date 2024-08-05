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
#ifndef PXR_IMAGING_HGI_METAL_BUFFER_H
#define PXR_IMAGING_HGI_METAL_BUFFER_H

#include <Metal/Metal.hpp>

#include "Hgi/buffer.h"
#include "HgiMetal/api.h"
#include <pxr/pxrns.h>

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

  MTL::Buffer *GetBufferId() const
  {
    return _bufferId;
  }

 private:
  HgiMetalBuffer() = delete;
  HgiMetalBuffer &operator=(const HgiMetalBuffer &) = delete;
  HgiMetalBuffer(const HgiMetalBuffer &) = delete;

  MTL::Buffer *_bufferId;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
