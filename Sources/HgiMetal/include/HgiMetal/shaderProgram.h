//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HGI_METAL_SHADERPROGRAM_H
#define PXR_IMAGING_HGI_METAL_SHADERPROGRAM_H

#include "Hgi/shaderProgram.h"

#include "HgiMetal/api.h"
#include "HgiMetal/shaderFunction.h"

#include <vector>

#include <Metal/Metal.hpp>

PXR_NAMESPACE_OPEN_SCOPE

///
/// \class HgiMetalShaderProgram
///
/// Metal implementation of HgiShaderProgram
///
class HgiMetalShaderProgram final : public HgiShaderProgram {
 public:
  HGIMETAL_API
  ~HgiMetalShaderProgram() noexcept override;

  HGIMETAL_API
  bool IsValid() const override;

  HGIMETAL_API
  std::string const &GetCompileErrors() override;

  HGIMETAL_API
  HgiShaderFunctionHandleVector const &GetShaderFunctions() const override;

  HGIMETAL_API
  size_t GetByteSizeOfResource() const override;

  HGIMETAL_API
  uint64_t GetRawResource() const override;

  HGIMETAL_API
  MTL::Function* GetVertexFunction() const
  {
    return _vertexFunction;
  }

  HGIMETAL_API
  MTL::Function* GetFragmentFunction() const
  {
    return _fragmentFunction;
  }

  HGIMETAL_API
  MTL::Function* GetComputeFunction() const
  {
    return _computeFunction;
  }

  HGIMETAL_API
  MTL::Function* GetPostTessVertexFunction() const
  {
    return _postTessVertexFunction;
  }

  HGIMETAL_API
  MTL::Function* GetPostTessControlFunction() const
  {
    return _postTessControlFunction;
  }

 protected:
  friend class HgiMetal;

  HGIMETAL_API
  HgiMetalShaderProgram(HgiShaderProgramDesc const &desc);

 private:
  HgiMetalShaderProgram() = delete;
  HgiMetalShaderProgram &operator=(const HgiMetalShaderProgram &) = delete;
  HgiMetalShaderProgram(const HgiMetalShaderProgram &) = delete;

 private:
  std::string _errors;

  MTL::Function* _vertexFunction;
  MTL::Function* _fragmentFunction;
  MTL::Function* _computeFunction;
  MTL::Function* _postTessVertexFunction;
  MTL::Function* _postTessControlFunction;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
