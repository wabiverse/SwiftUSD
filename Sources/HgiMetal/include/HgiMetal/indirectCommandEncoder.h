//
// Copyright 2022 Pixar
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
#ifndef PXR_IMAGING_HGI_METAL_INDIRECT_COMMAND_ENCODER_H
#define PXR_IMAGING_HGI_METAL_INDIRECT_COMMAND_ENCODER_H

#include "Hgi/indirectCommandEncoder.h"
#include "HgiMetal/api.h"
#include "HgiMetal/stepFunctions.h"
#include <pxr/pxrns.h>

#include <Metal/Metal.hpp>

#include <map>
#include <mutex>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class Hgi;
struct HgiIndirectCommands;
class HgiMetal;
class HgiMetalGraphicsPipeline;
class HgiMetalResourceBindings;
class HgiMetalVertexBufferBindings;

/// \class HgiMetalIndirectCommandEncoder
///
/// Metal implementation of Indirect Command Buffers.
///
class HgiMetalIndirectCommandEncoder final : public HgiIndirectCommandEncoder {
 public:
  HGIMETAL_API
  HgiMetalIndirectCommandEncoder(Hgi *hgi);

  HGIMETAL_API
  HgiIndirectCommandsUniquePtr EncodeDraw(HgiComputeCmds *computeCmds,
                                          HgiGraphicsPipelineHandle const &pipeline,
                                          HgiResourceBindingsHandle const &resourceBindings,
                                          HgiVertexBufferBindingVector const &vertexBindings,
                                          HgiBufferHandle const &drawParameterBuffer,
                                          uint32_t drawBufferByteOffset,
                                          uint32_t drawCount,
                                          uint32_t stride) override;

  HGIMETAL_API
  HgiIndirectCommandsUniquePtr EncodeDrawIndexed(
      HgiComputeCmds *computeCmds,
      HgiGraphicsPipelineHandle const &pipeline,
      HgiResourceBindingsHandle const &resourceBindings,
      HgiVertexBufferBindingVector const &vertexBindings,
      HgiBufferHandle const &indexBuffer,
      HgiBufferHandle const &drawParameterBuffer,
      uint32_t drawBufferByteOffset,
      uint32_t drawCount,
      uint32_t stride,
      uint32_t patchBaseVertexByteOffset) override;

  HGIMETAL_API
  void ExecuteDraw(HgiGraphicsCmds *gfxCmds, HgiIndirectCommands const *commands) override;

 private:
  HgiMetalIndirectCommandEncoder &operator=(const HgiMetalIndirectCommandEncoder &) = delete;
  HgiMetalIndirectCommandEncoder(const HgiMetalIndirectCommandEncoder &) = delete;

  struct FunctionState {
    MTL::Function *function;
    MTL::ComputePipelineState *pipelineState;
    MTL::ArgumentEncoder *argumentEncoder;
  };

  HGIMETAL_API
  FunctionState _GetFunction(HgiGraphicsPipelineDesc const &pipelineDesc, bool isIndexed);

  HGIMETAL_API
  HgiIndirectCommandsUniquePtr _EncodeDraw(HgiComputeCmds *computeCmds,
                                           HgiGraphicsPipelineHandle const &pipeline,
                                           HgiResourceBindingsHandle const &resourceBindings,
                                           HgiVertexBufferBindingVector const &bindings,
                                           HgiBufferHandle const &indexBuffer,
                                           uint32_t drawBufferByteOffset,
                                           uint32_t drawCount,
                                           uint32_t stride,
                                           uint32_t patchBaseVertexByteOffset);

  HGIMETAL_API
  MTL::IndirectCommandBuffer *_AllocateCommandBuffer(uint32_t drawCount);

  HGIMETAL_API
  MTL::Buffer *_AllocateArgumentBuffer(uint32_t encodedLength);

  HgiMetal *_hgi;
  MTL::Device *_device;
  MTL::Library *_library;
  std::vector<FunctionState> _functions;
  MTL::ResourceOptions _bufferStorageMode;
  MTL::Buffer *_triangleTessFactors;
  MTL::Buffer *_quadTessFactors;

  using FreeCommandBuffers = std::multimap<uint32_t, MTL::IndirectCommandBuffer *>;
  using FreeArgumentBuffers = std::multimap<uint32_t, MTL::Buffer *>;

  std::mutex _poolMutex;
  FreeCommandBuffers _commandBufferPool;
  FreeArgumentBuffers _argumentBufferPool;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
