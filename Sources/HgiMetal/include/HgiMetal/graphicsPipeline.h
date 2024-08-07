//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_PIPELINE_H
#define PXR_IMAGING_HGI_METAL_PIPELINE_H

#include "Hgi/graphicsCmdsDesc.h"
#include "Hgi/graphicsPipeline.h"
#include "pxr/pxrns.h"

#include "HgiMetal/api.h"

#include <Foundation/Foundation.hpp>
#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

class HgiMetal;

/// \class HgiMetalPipeline
///
/// Metal implementation of HgiGraphicsPipeline.
///
class HgiMetalGraphicsPipeline final : public HgiGraphicsPipeline {
 public:
  HGIMETAL_API
  HgiMetalGraphicsPipeline(HgiMetal *hgi, HgiGraphicsPipelineDesc const &desc);

  HGIMETAL_API
  ~HgiMetalGraphicsPipeline() override;

  /// Apply pipeline state
  HGIMETAL_API
  void BindPipeline(MTL::RenderCommandEncoder* renderEncoder);

 private:
  HgiMetalGraphicsPipeline() = delete;
  HgiMetalGraphicsPipeline &operator=(const HgiMetalGraphicsPipeline &) = delete;
  HgiMetalGraphicsPipeline(const HgiMetalGraphicsPipeline &) = delete;

  void _CreateVertexDescriptor();
  void _CreateDepthStencilState(HgiMetal *hgi);
  void _CreateRenderPipelineState(HgiMetal *hgi);

  MTL::VertexDescriptor *_vertexDescriptor;
  MTL::DepthStencilState* _depthStencilState;
  MTL::RenderPipelineState* _renderPipelineState;
  MTL::Buffer* _constantTessFactors;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
