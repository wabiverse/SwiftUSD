//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Sdr/debugCodes.h"
#include "pxr/pxrns.h"

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(SDR_TYPE_CONFORMANCE,
                              "Diagnostcs from parsing "
                              "and conforming default values for Sdr and Sdf type conformance");
}

PXR_NAMESPACE_CLOSE_SCOPE
