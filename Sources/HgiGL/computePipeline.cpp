//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/diagnostic.h"

#include "HgiGL/computePipeline.h"
#include "HgiGL/conversions.h"
#include "HgiGL/diagnostic.h"
#include "HgiGL/resourceBindings.h"
#include "HgiGL/shaderFunction.h"
#include "HgiGL/shaderProgram.h"

PXR_NAMESPACE_OPEN_SCOPE

HgiGLComputePipeline::HgiGLComputePipeline(HgiComputePipelineDesc const &desc)
    : HgiComputePipeline(desc)
{
}

HgiGLComputePipeline::~HgiGLComputePipeline() = default;

void HgiGLComputePipeline::BindPipeline()
{
  //
  // Shader program
  //
  HgiGLShaderProgram *glProgram = static_cast<HgiGLShaderProgram *>(
      _descriptor.shaderProgram.Get());
  if (glProgram) {
    glUseProgram(glProgram->GetProgramId());
  }

  HGIGL_POST_PENDING_GL_ERRORS();
}

PXR_NAMESPACE_CLOSE_SCOPE
