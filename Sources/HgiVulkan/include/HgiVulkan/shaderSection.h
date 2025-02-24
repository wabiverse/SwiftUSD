//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_IMAGING_HGIVULKAN_SHADERSECTION_H
#define PXR_IMAGING_HGIVULKAN_SHADERSECTION_H

#include "Hgi/shaderFunctionDesc.h"
#include "Hgi/shaderSection.h"
#include "HgiVulkan/api.h"

#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

/// \class HgiVulkanShaderSection
///
/// Base class for Vulkan code sections. The generator holds these
///
class HgiVulkanShaderSection : public HgiShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanShaderSection(const std::string &identifier,
                                  const HgiShaderSectionAttributeVector &attributes = {},
                                  const std::string &storageQualifier = std::string(),
                                  const std::string &defaultValue = std::string(),
                                  const std::string &arraySize = std::string(),
                                  const std::string &blockInstanceIdentifier = std::string());

  HGIVULKAN_API
  ~HgiVulkanShaderSection() override;

  HGIVULKAN_API
  void WriteDeclaration(std::ostream &ss) const override;
  HGIVULKAN_API
  void WriteParameter(std::ostream &ss) const override;

  HGIVULKAN_API
  virtual bool VisitGlobalIncludes(std::ostream &ss);
  HGIVULKAN_API
  virtual bool VisitGlobalMacros(std::ostream &ss);
  HGIVULKAN_API
  virtual bool VisitGlobalStructs(std::ostream &ss);
  HGIVULKAN_API
  virtual bool VisitGlobalMemberDeclarations(std::ostream &ss);
  HGIVULKAN_API
  virtual bool VisitGlobalFunctionDefinitions(std::ostream &ss);

 protected:
  const std::string _storageQualifier;
  const std::string _arraySize;

 private:
  HgiVulkanShaderSection() = delete;
  HgiVulkanShaderSection &operator=(const HgiVulkanShaderSection &) = delete;
  HgiVulkanShaderSection(const HgiVulkanShaderSection &) = delete;
};

using HgiVulkanShaderSectionPtrVector = std::vector<HgiVulkanShaderSection *>;

/// \class HgiVulkanMacroShaderSection
///
/// A ShaderSection for defining macros.
/// Accepts raw strings and dumps it to the global scope under includes
///
class HgiVulkanMacroShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanMacroShaderSection(const std::string &macroDeclaration,
                                       const std::string &macroComment);

  HGIVULKAN_API
  ~HgiVulkanMacroShaderSection() override;

  HGIVULKAN_API
  bool VisitGlobalMacros(std::ostream &ss) override;

 private:
  HgiVulkanMacroShaderSection() = delete;
  HgiVulkanMacroShaderSection &operator=(const HgiVulkanMacroShaderSection &) = delete;
  HgiVulkanMacroShaderSection(const HgiVulkanMacroShaderSection &) = delete;

  const std::string _macroComment;
};

/// \class HgiVulkanMemberShaderSection
///
/// Declares a member in global scope, for declaring instances of structs, constant
/// params etc - it's quite flexible in it's writing capabilities
///
class HgiVulkanMemberShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanMemberShaderSection(
      const std::string &identifier,
      const std::string &typeName,
      const HgiInterpolationType interpolation,
      const HgiSamplingType sampling,
      const HgiStorageType storage,
      const HgiShaderSectionAttributeVector &attributes,
      const std::string &storageQualifier,
      const std::string &defaultValue = std::string(),
      const std::string &arraySize = std::string(),
      const std::string &blockInstanceIdentifier = std::string());

  HGIVULKAN_API
  ~HgiVulkanMemberShaderSection() override;

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

  HGIVULKAN_API
  void WriteType(std::ostream &ss) const override;

  HGIVULKAN_API
  void WriteInterpolation(std::ostream &ss) const;

  HGIVULKAN_API
  void WriteSampling(std::ostream &ss) const;

  HGIVULKAN_API
  void WriteStorage(std::ostream &ss) const;

 private:
  HgiVulkanMemberShaderSection() = delete;
  HgiVulkanMemberShaderSection &operator=(const HgiVulkanMemberShaderSection &) = delete;
  HgiVulkanMemberShaderSection(const HgiVulkanMemberShaderSection &) = delete;

  std::string _typeName;
  HgiInterpolationType _interpolation;
  HgiSamplingType _sampling;
  HgiStorageType _storage;
};

using HgiVulkanMemberShaderSectionPtrVector = std::vector<HgiVulkanMemberShaderSection *>;

/// \class HgiVulkanBlockShaderSection
///
/// For writing out uniform blocks, defines them in the global member declerations.
///
class HgiVulkanBlockShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanBlockShaderSection(const std::string &identifier,
                                       const HgiShaderFunctionParamDescVector &parameters);

  HGIVULKAN_API
  ~HgiVulkanBlockShaderSection() override;

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

 private:
  const HgiShaderFunctionParamDescVector _parameters;
};

/// \class HgiVulkanMemberShaderSection
///
/// Declares OpenGL textures, and their cross language function
///
class HgiVulkanTextureShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanTextureShaderSection(const std::string &identifier,
                                         const uint32_t layoutIndex,
                                         const uint32_t dimensions,
                                         const HgiFormat format,
                                         const HgiShaderTextureType textureType,
                                         const uint32_t arraySize,
                                         const bool writable,
                                         const HgiShaderSectionAttributeVector &attributes,
                                         const std::string &defaultValue = std::string());

  HGIVULKAN_API
  ~HgiVulkanTextureShaderSection() override;

  HGIVULKAN_API
  void WriteType(std::ostream &ss) const override;

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;
  HGIVULKAN_API
  bool VisitGlobalFunctionDefinitions(std::ostream &ss) override;

 private:
  HgiVulkanTextureShaderSection() = delete;
  HgiVulkanTextureShaderSection &operator=(const HgiVulkanTextureShaderSection &) = delete;
  HgiVulkanTextureShaderSection(const HgiVulkanTextureShaderSection &) = delete;

  void _WriteSamplerType(std::ostream &ss) const;
  void _WriteSampledDataType(std::ostream &ss) const;

  const uint32_t _dimensions;
  const HgiFormat _format;
  const HgiShaderTextureType _textureType;
  const uint32_t _arraySize;
  const bool _writable;
  static const std::string _storageQualifier;
};

/// \class HgiVulkanBufferShaderSection
///
/// Declares Vulkan buffers, and their cross language function
///
class HgiVulkanBufferShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanBufferShaderSection(const std::string &identifier,
                                        const uint32_t layoutIndex,
                                        const std::string &type,
                                        const HgiBindingType binding,
                                        const std::string arraySize,
                                        const bool writable,
                                        const HgiShaderSectionAttributeVector &attributes);

  HGIVULKAN_API
  ~HgiVulkanBufferShaderSection() override;

  HGIVULKAN_API
  void WriteType(std::ostream &ss) const override;

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

 private:
  HgiVulkanBufferShaderSection() = delete;
  HgiVulkanBufferShaderSection &operator=(const HgiVulkanBufferShaderSection &) = delete;
  HgiVulkanBufferShaderSection(const HgiVulkanBufferShaderSection &) = delete;

  const std::string _type;
  const HgiBindingType _binding;
  const std::string _arraySize;
  const bool _writable;
};

/// \class HgiVulkanKeywordShaderSection
///
/// Declares reserved Vulkan shader inputs, and their cross language function
///
class HgiVulkanKeywordShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanKeywordShaderSection(const std::string &identifier,
                                         const std::string &type,
                                         const std::string &keyword);

  HGIVULKAN_API
  ~HgiVulkanKeywordShaderSection() override;

  HGIVULKAN_API
  void WriteType(std::ostream &ss) const override;

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

 private:
  HgiVulkanKeywordShaderSection() = delete;
  HgiVulkanKeywordShaderSection &operator=(const HgiVulkanKeywordShaderSection &) = delete;
  HgiVulkanKeywordShaderSection(const HgiVulkanKeywordShaderSection &) = delete;

  const std::string _type;
  const std::string _keyword;
};

/// \class HgiVulkanInterstageBlockShaderSection
///
/// Defines and writes out an interstage interface block
///
class HgiVulkanInterstageBlockShaderSection final : public HgiVulkanShaderSection {
 public:
  HGIVULKAN_API
  explicit HgiVulkanInterstageBlockShaderSection(
      const std::string &blockIdentifier,
      const std::string &blockInstanceIdentifier,
      const HgiShaderSectionAttributeVector &attributes,
      const std::string &qualifier,
      const std::string &arraySize,
      const HgiVulkanMemberShaderSectionPtrVector &members);

  HGIVULKAN_API
  bool VisitGlobalMemberDeclarations(std::ostream &ss) override;

 private:
  HgiVulkanInterstageBlockShaderSection() = delete;
  HgiVulkanInterstageBlockShaderSection &operator=(const HgiVulkanInterstageBlockShaderSection &) =
      delete;
  HgiVulkanInterstageBlockShaderSection(const HgiVulkanInterstageBlockShaderSection &) = delete;

  const std::string _qualifier;
  const HgiVulkanMemberShaderSectionPtrVector _members;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
