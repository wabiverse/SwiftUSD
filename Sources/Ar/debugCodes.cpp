//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ar/debugCodes.h"
#include "pxr/pxrns.h"

#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(AR_RESOLVER_INIT,
                              "Print debug output during asset resolver initialization");
}

PXR_NAMESPACE_CLOSE_SCOPE
