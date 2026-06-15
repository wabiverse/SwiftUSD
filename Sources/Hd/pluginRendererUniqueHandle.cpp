//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Hd/pluginRendererUniqueHandle.h"

#include "Hd/rendererPlugin.h"
#include "Hd/renderer.h"

PXR_NAMESPACE_OPEN_SCOPE

HdPluginRendererUniqueHandle::HdPluginRendererUniqueHandle() = default;

HdPluginRendererUniqueHandle::HdPluginRendererUniqueHandle(
    const std::nullptr_t &)
{
}

HdPluginRendererUniqueHandle::HdPluginRendererUniqueHandle(
    HdPluginRendererUniqueHandle &&other) = default;

HdPluginRendererUniqueHandle::HdPluginRendererUniqueHandle(
    HdRendererPluginHandle plugin,
    std::unique_ptr<HdRenderer> renderer)
  : _plugin(std::move(plugin))
  , _renderer(std::move(renderer))
{
}

HdPluginRendererUniqueHandle::~HdPluginRendererUniqueHandle() = default;

HdPluginRendererUniqueHandle &
HdPluginRendererUniqueHandle::operator=(
    HdPluginRendererUniqueHandle &&other) = default;

HdPluginRendererUniqueHandle &
HdPluginRendererUniqueHandle::operator=(
    const std::nullptr_t &)
{
    _renderer = nullptr;
    _plugin = nullptr;
    
    return *this;
}

TfToken
HdPluginRendererUniqueHandle::GetPluginId() const
{
    if (_plugin) {
        return _plugin->GetPluginId();
    }
    
    return TfToken();
}

PXR_NAMESPACE_CLOSE_SCOPE
