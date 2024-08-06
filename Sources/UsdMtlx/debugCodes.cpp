//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdMtlx/debugCodes.h"
#include "pxr/pxrns.h"

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(USDMTLX_READER, "UsdMtlx reader details");
}

PXR_NAMESPACE_CLOSE_SCOPE
