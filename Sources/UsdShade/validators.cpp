//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdr/registry.h"
#include "Sdr/shaderProperty.h"
#include "Tf/stringUtils.h"
#include "Tf/token.h"
#include "Usd/prim.h"
#include "Usd/schemaRegistry.h"
#include "Usd/validationError.h"
#include "Usd/validationRegistry.h"
#include "Usd/validator.h"
#include "UsdShade/shader.h"
#include "UsdShade/validatorTokens.h"

#include <algorithm>
#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

static UsdValidationErrorVector _ShaderPropertyTypeConformance(const UsdPrim &usdPrim)
{
  if (!(usdPrim && usdPrim.IsInFamily<UsdShadeShader>(UsdSchemaRegistry::VersionPolicy::All))) {
    return {};
  }
  UsdShadeShader shader(usdPrim);
  if (!shader) {
    return {};
  }

  const TfTokenVector expectedImplSource = {
      UsdShadeTokens->id, UsdShadeTokens->sourceAsset, UsdShadeTokens->sourceCode};

  const TfToken implSource = shader.GetImplementationSource();
  if (std::find(expectedImplSource.begin(), expectedImplSource.end(), implSource) ==
      expectedImplSource.end())
  {
    const UsdValidationErrorSites implSourceErrorSite = {UsdValidationErrorSite(
        usdPrim.GetStage(), shader.GetImplementationSourceAttr().GetPath())};
    return {UsdValidationError(UsdValidationErrorType::Error,
                               implSourceErrorSite,
                               TfStringPrintf("Shader <%s> has invalid "
                                              "implementation source '%s'.",
                                              usdPrim.GetPath().GetText(),
                                              implSource.GetText()))};
  }

  const std::vector<std::string> sourceTypes = shader.GetSourceTypes();
  if (sourceTypes.empty() && implSource != UsdShadeTokens->id) {
    const UsdValidationErrorSites primErrorSite = {
        UsdValidationErrorSite(usdPrim.GetStage(), usdPrim.GetPath())};
    return {UsdValidationError(
        UsdValidationErrorType::Error,
        primErrorSite,
        TfStringPrintf("Shader <%s> has no sourceType.", usdPrim.GetPath().GetText()))};
  }

  UsdValidationErrorVector errors;
  std::unordered_map<TfToken, SdrShaderPropertyConstPtr, TfToken::HashFunctor>
      propNameToPropertyMap;
  if (sourceTypes.empty() && implSource == UsdShadeTokens->id) {
    TfToken shaderId;
    if (shader.GetShaderId(&shaderId)) {
      // Single shaderNode, just emplace all properties, no need to find
      // anything.
      if (SdrShaderNodeConstPtr sdrShaderNode =
              SdrRegistry::GetInstance().GetShaderNodeByIdentifier(shaderId))
      {
        for (const TfToken &propName : sdrShaderNode->GetInputNames()) {
          if (const SdrShaderPropertyConstPtr sdrProp = sdrShaderNode->GetShaderInput(propName)) {
            propNameToPropertyMap.emplace(propName, sdrProp);
          }
        }
      }
      else {
        const UsdValidationErrorSites shaderIdErrorSite = {
            UsdValidationErrorSite(usdPrim.GetStage(), shader.GetIdAttr().GetPath())};
        return {UsdValidationError(UsdValidationErrorType::Error,
                                   shaderIdErrorSite,
                                   TfStringPrintf("shaderId '%s' specified on shader prim "
                                                  "<%s> not found in sdrRegistry.",
                                                  shaderId.GetText(),
                                                  usdPrim.GetPath().GetText()))};
      }
    }
  }
  else {
    // Use the SdrShaderNode::CheckPropertyCompliance to find if these do
    // not match, then report a ValidationError as a warning, since asset
    // authors have no control on fixing the shaders.
    std::vector<SdrShaderNodeConstPtr> shaderNodesFromSourceTypes;

    // We need to gather all unique inputs from all sdrShaderNodes queried
    // using multiple sourceTypes.
    for (const auto &sourceType : sourceTypes) {
      if (SdrShaderNodeConstPtr sdrShaderNode = shader.GetShaderNodeForSourceType(
              TfToken(sourceType)))
      {
        shaderNodesFromSourceTypes.push_back(sdrShaderNode);

        for (const TfToken &propName : sdrShaderNode->GetInputNames()) {
          // Check if property has already been added to the map.
          if (propNameToPropertyMap.find(propName) == propNameToPropertyMap.end()) {
            if (const SdrShaderPropertyConstPtr sdrProp = sdrShaderNode->GetShaderInput(propName))
            {
              propNameToPropertyMap.emplace(propName, sdrProp);
            }
          }
        }
      }
      else {
        UsdValidationErrorSites sourceTypeSites;
        for (const auto &sourceTypeProp :
             usdPrim.GetPropertiesInNamespace(SdfPath::JoinIdentifier("info", sourceType)))
        {
          sourceTypeSites.emplace_back(usdPrim.GetStage(), sourceTypeProp.GetPath());
        }
        errors.emplace_back(UsdValidationErrorType::Error,
                            sourceTypeSites,
                            TfStringPrintf("sourceType '%s' specified on shader prim "
                                           "<%s> not found in sdrRegistry.",
                                           sourceType.c_str(),
                                           usdPrim.GetPath().GetText()));
      }
    }
    SdrShaderNode::ComplianceResults sdrShaderComplianceResults =
        SdrShaderNode::CheckPropertyCompliance(shaderNodesFromSourceTypes);
    const UsdValidationErrorSites sdrWarnSite = {
        UsdValidationErrorSite(usdPrim.GetStage(), usdPrim.GetPath())};
    for (const auto &entry : sdrShaderComplianceResults) {
      // need this for getting the error message!
      std::vector<std::string> shaderNames;
      shaderNames.reserve(entry.second.size());
      for (const auto &shaderName : entry.second) {
        shaderNames.push_back(shaderName.GetString());
      }
      errors.emplace_back(UsdValidationErrorType::Warn,
                          sdrWarnSite,
                          TfStringPrintf("Shader nodes '%s' have incompatible property "
                                         "'%s'.",
                                         TfStringJoin(shaderNames).c_str(),
                                         entry.first.GetText()));
    }
  }

  // Get ground truth data about inputName to types from sdrNode
  const auto sdrPropnameToSdfType = [&propNameToPropertyMap]() {
    std::unordered_map<TfToken, SdfValueTypeName, TfToken::HashFunctor> map;
    for (const auto &prop : propNameToPropertyMap) {
      map.emplace(prop.first, prop.second->GetTypeAsSdfType().first);
    }
    return map;
  }();

  // Compare ground truth data with the inputs on UsdShadeShader prim
  for (const UsdShadeInput &input : shader.GetInputs(false)) {
    const TfToken baseName = input.GetBaseName();
    if (sdrPropnameToSdfType.find(baseName) != sdrPropnameToSdfType.end()) {
      const SdfValueTypeName &expectedSdrInputType = sdrPropnameToSdfType.at(baseName);
      const SdfValueTypeName usdInputType = input.GetTypeName();
      if (usdInputType != expectedSdrInputType) {
        const UsdValidationErrorSites inputErrorSite = {
            UsdValidationErrorSite(usdPrim.GetStage(), input.GetAttr().GetPath())};
        errors.emplace_back(UsdValidationErrorType::Error,
                            inputErrorSite,
                            TfStringPrintf("Incorrect type for %s. "
                                           "Expected '%s'; got '%s'.",
                                           input.GetAttr().GetPath().GetText(),
                                           expectedSdrInputType.GetAsToken().GetText(),
                                           usdInputType.GetAsToken().GetText()));
      }
    }
  }
  return errors;
}

TF_REGISTRY_FUNCTION(UsdValidationRegistry)
{
  UsdValidationRegistry &registry = UsdValidationRegistry::GetInstance();

  registry.RegisterPluginValidator(UsdShadeValidatorNameTokens->shaderSdrCompliance,
                                   _ShaderPropertyTypeConformance);
}

PXR_NAMESPACE_CLOSE_SCOPE
