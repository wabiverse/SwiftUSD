//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkelImaging/package.h"

#include "Plug/plugin.h"
#include "Plug/thisPlugin.h"
#include "Tf/diagnostic.h"
#include "Tf/fileUtils.h"
#include "Tf/stringUtils.h"

PXR_NAMESPACE_OPEN_SCOPE

static TfToken _GetShaderPath(char const *shader)
{
  static PlugPluginPtr plugin = PLUG_THIS_PLUGIN;
  const std::string path = PlugFindPluginResource(plugin, TfStringCatPaths("shaders", shader));
  TF_VERIFY(!path.empty(), "Could not find shader: %s\n", shader);

  return TfToken(path);
}

TfToken UsdSkelImagingPackageSkinningShader()
{
  static TfToken skinningShader = _GetShaderPath("skinning.glslfx");
  return skinningShader;
}

PXR_NAMESPACE_CLOSE_SCOPE
