//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "HdStorm/rendererPlugin.h"

#include "HdSt/renderDelegate.h"
#include "Hd/rendererPluginRegistry.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  HdRendererPluginRegistry::Define<HdStormRendererPlugin>();
}

HdRenderDelegate *HdStormRendererPlugin::CreateRenderDelegate()
{
  return new HdStRenderDelegate();
}

HdRenderDelegate *HdStormRendererPlugin::CreateRenderDelegate(HdRenderSettingsMap const &settingsMap)
{
  return new HdStRenderDelegate(settingsMap);
}

void HdStormRendererPlugin::DeleteRenderDelegate(HdRenderDelegate *renderDelegate)
{
  delete renderDelegate;
}

bool HdStormRendererPlugin::IsSupported(bool gpuEnabled) const
{
  const bool support = gpuEnabled && HdStRenderDelegate::IsSupported();
  if (!support) {
    TF_DEBUG(HD_RENDERER_PLUGIN)
        .Msg("hdStorm renderer plugin unsupported: %s\n",
             gpuEnabled ? "hgi unsupported" : "no gpu");
  }
  return support;
}

PXR_NAMESPACE_CLOSE_SCOPE
