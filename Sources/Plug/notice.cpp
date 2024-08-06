//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Plug/notice.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<PlugNotice::Base, TfType::Bases<TfNotice>>();
  TfType::Define<PlugNotice::DidRegisterPlugins, TfType::Bases<PlugNotice::Base>>();
}

////////////////////////////////////////////////////////////

PlugNotice::Base::~Base() {}

////////////////////////////////////////////////////////////

PlugNotice::DidRegisterPlugins::DidRegisterPlugins(const PlugPluginPtrVector &newPlugins)
    : _plugins(newPlugins)
{
}

PlugNotice::DidRegisterPlugins::~DidRegisterPlugins() {}

PXR_NAMESPACE_CLOSE_SCOPE
