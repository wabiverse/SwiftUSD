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
#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

#include "Tf/diagnostic.h"

#include "HgiMetal/computePipeline.h"
#include "HgiMetal/conversions.h"
#include "HgiMetal/diagnostic.h"
#include "HgiMetal/hgi.h"
#include "HgiMetal/resourceBindings.h"
#include "HgiMetal/shaderFunction.h"
#include "HgiMetal/shaderProgram.h"

PXR_NAMESPACE_OPEN_SCOPE

HgiMetalComputePipeline::HgiMetalComputePipeline(HgiMetal *hgi, HgiComputePipelineDesc const &desc)
    : HgiComputePipeline(desc)
{
  MTL::ComputePipelineDescriptor *stateDesc = MTL::ComputePipelineDescriptor::alloc()->init();

  // Create a new compute pipeline state object
  HGIMETAL_DEBUG_LABEL(stateDesc, _descriptor.debugName.c_str());

  HgiMetalShaderProgram const *metalProgram = static_cast<HgiMetalShaderProgram *>(
      _descriptor.shaderProgram.Get());

  stateDesc->setComputeFunction(metalProgram->GetComputeFunction());

  NS::Error *error = NULL;
  _computePipelineState = hgi->GetPrimaryDevice()->newComputePipelineState(
      stateDesc, MTL::PipelineOptionNone, nil, &error);
  stateDesc->release();

  if (!_computePipelineState) {
    NS::String *err = error->localizedDescription();
    TF_WARN("Failed to create compute pipeline state, error %s", err->utf8String());
  }
}

HgiMetalComputePipeline::~HgiMetalComputePipeline() {}

void HgiMetalComputePipeline::BindPipeline(MTL::ComputeCommandEncoder *computeEncoder)
{
  computeEncoder->setComputePipelineState(_computePipelineState);
}

MTL::ComputePipelineState *HgiMetalComputePipeline::GetMetalPipelineState()
{
  return _computePipelineState;
}

PXR_NAMESPACE_CLOSE_SCOPE
