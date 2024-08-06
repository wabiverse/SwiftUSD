//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ndr/discoveryPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register this plugin type with Tf
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<NdrDiscoveryPlugin>();
}

NdrDiscoveryPlugin::NdrDiscoveryPlugin()
{
  // nothing yet
}

NdrDiscoveryPlugin::~NdrDiscoveryPlugin()
{
  // nothing yet
}

PXR_NAMESPACE_CLOSE_SCOPE
