//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_IMAGING_HGIVULKAN_SHADERGENERATOR_H
#define PXR_IMAGING_HGIVULKAN_SHADERGENERATOR_H

#include "Hgi/shaderGenerator.h"
#include "HgiVulkan/api.h"
#include "HgiVulkan/shaderSection.h"

PXR_NAMESPACE_OPEN_SCOPE

class Hgi;

using HgiVulkanShaderSectionUniquePtrVector = std::vector<std::unique_ptr<HgiVulkanShaderSection>>;

/// \class HgiVulkanShaderGenerator
///
/// Takes in a descriptor and spits out GLSL code through it's execute function.
///
class HgiVulkanShaderGenerator final : public HgiShaderGenerator {
 public:
  HGIVULKAN_API
  explicit HgiVulkanShaderGenerator(Hgi const *hgi, const HgiShaderFunctionDesc &descriptor);

  // This is not commonly consumed by the end user, but is available.
  HGIVULKAN_API
  HgiVulkanShaderSectionUniquePtrVector *GetShaderSections();

  template<typename SectionType, typename... T> SectionType *CreateShaderSection(T &&...t);

 protected:
  HGIVULKAN_API
  void _Execute(std::ostream &ss) override;

 private:
  HgiVulkanShaderGenerator() = delete;
  HgiVulkanShaderGenerator &operator=(const HgiVulkanShaderGenerator &) = delete;
  HgiVulkanShaderGenerator(const HgiVulkanShaderGenerator &) = delete;

  void _WriteVersion(std::ostream &ss);

  void _WriteExtensions(std::ostream &ss);

  void _WriteMacros(std::ostream &ss);

  void _WriteConstantParams(const HgiShaderFunctionParamDescVector &parameters);

  void _WriteTextures(const HgiShaderFunctionTextureDescVector &textures);

  void _WriteBuffers(const HgiShaderFunctionBufferDescVector &buffers);

  // For writing shader inputs and outputs who are very similarly written
  void _WriteInOuts(const HgiShaderFunctionParamDescVector &parameters,
                    const std::string &qualifier);
  void _WriteInOutBlocks(const HgiShaderFunctionParamBlockDescVector &parameterBlocks,
                         const std::string &qualifier);

  HgiVulkanShaderSectionUniquePtrVector _shaderSections;
  Hgi const *_hgi;
  uint32_t _textureBindIndexStart;
  uint32_t _inLocationIndex;
  uint32_t _outLocationIndex;
  std::vector<std::string> _shaderLayoutAttributes;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
