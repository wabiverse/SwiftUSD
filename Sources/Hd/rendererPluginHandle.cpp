//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Hd/rendererPluginHandle.h"

#include "Hd/pluginRenderDelegateUniqueHandle.h"
#include "Hd/rendererPlugin.h"
#include "Hd/rendererPluginRegistry.h"

PXR_NAMESPACE_OPEN_SCOPE

HdRendererPluginHandle::HdRendererPluginHandle(const HdRendererPluginHandle &other)
    : _plugin(other._plugin)
{
  if (_plugin) {
    HdRendererPluginRegistry::GetInstance().AddPluginReference(_plugin);
  }
}

HdRendererPluginHandle::~HdRendererPluginHandle()
{
  HdRendererPluginRegistry::GetInstance().ReleasePlugin(_plugin);
}

HdRendererPluginHandle &HdRendererPluginHandle::operator=(const HdRendererPluginHandle &other)
{
  HdRendererPluginRegistry::GetInstance().ReleasePlugin(_plugin);
  _plugin = other._plugin;
  if (_plugin) {
    HdRendererPluginRegistry::GetInstance().AddPluginReference(_plugin);
  }
  return *this;
}

HdRendererPluginHandle &HdRendererPluginHandle::operator=(const std::nullptr_t &)
{
  *this = HdRendererPluginHandle();
  return *this;
}

PXR_NAMESPACE_CLOSE_SCOPE
