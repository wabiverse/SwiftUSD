//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Plug/debugCodes.h"
#include "Tf/debug.h"
#include "Tf/registryManager.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(PLUG_LOAD, "Plugin loading");
  TF_DEBUG_ENVIRONMENT_SYMBOL(PLUG_REGISTRATION, "Plugin registration");
  TF_DEBUG_ENVIRONMENT_SYMBOL(PLUG_LOAD_IN_SECONDARY_THREAD,
                              "Plugins loaded from non-main threads");
  TF_DEBUG_ENVIRONMENT_SYMBOL(PLUG_INFO_SEARCH, "Plugin info file search");
}

PXR_NAMESPACE_CLOSE_SCOPE
