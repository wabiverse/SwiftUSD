//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdHydra/discoveryPlugin.h"

#include "Plug/plugin.h"
#include "Plug/thisPlugin.h"

#include "Tf/diagnostic.h"
#include "Tf/fileUtils.h"
#include "Tf/stringUtils.h"

#include "Ar/resolver.h"
#include "Ar/resolverContext.h"
#include "Ar/resolverContextBinder.h"

#include "Usd/attribute.h"
#include "Usd/stage.h"

#include "UsdShade/shader.h"
#include "UsdShade/shaderDefUtils.h"
#include "UsdShade/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

static std::string _GetShaderResourcePath(char const *resourceName = "")
{
  static PlugPluginPtr plugin = PLUG_THIS_PLUGIN;
  const std::string path = PlugFindPluginResource(plugin,
                                                  TfStringCatPaths("shaders", resourceName));

  TF_VERIFY(!path.empty(), "Could not find shader resource: %s\n", resourceName);

  return path;
}

const NdrStringVec &UsdHydraDiscoveryPlugin::GetSearchURIs() const
{
  static const NdrStringVec searchPaths{_GetShaderResourcePath()};
  return searchPaths;
}

NdrNodeDiscoveryResultVec UsdHydraDiscoveryPlugin::DiscoverNodes(const Context &context)
{
  NdrNodeDiscoveryResultVec result;

  static std::string shaderDefsFile = _GetShaderResourcePath("shaderDefs.usda");
  if (shaderDefsFile.empty())
    return result;

  auto resolverContext = ArGetResolver().CreateDefaultContextForAsset(shaderDefsFile);

  const UsdStageRefPtr stage = UsdStage::Open(shaderDefsFile, resolverContext);

  if (!stage) {
    TF_RUNTIME_ERROR("Could not open file '%s' on a USD stage.", shaderDefsFile.c_str());
    return result;
  }

  ArResolverContextBinder binder(resolverContext);
  const TfToken discoveryType(ArGetResolver().GetExtension(shaderDefsFile));

  auto rootPrims = stage->GetPseudoRoot().GetChildren();
  for (const auto &shaderDef : rootPrims) {
    UsdShadeShader shader(shaderDef);
    if (!shader) {
      continue;
    }

    auto discoveryResults = UsdShadeShaderDefUtils::GetNodeDiscoveryResults(shader,
                                                                            shaderDefsFile);

    result.insert(result.end(), discoveryResults.begin(), discoveryResults.end());

    if (discoveryResults.empty()) {
      TF_RUNTIME_ERROR(
          "Found shader definition <%s> with no valid "
          "discovery results. This is likely because there are no "
          "resolvable info:sourceAsset values.",
          shaderDef.GetPath().GetText());
    }
  }

  return result;
}

NDR_REGISTER_DISCOVERY_PLUGIN(UsdHydraDiscoveryPlugin);

PXR_NAMESPACE_CLOSE_SCOPE
