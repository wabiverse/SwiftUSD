//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file debugCodes.cpp

#include "HioOpenVDB/debugCodes.h"

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(HIOOPENVDB_DEBUG_TEXTURE, "HioVDB texture loading");
}

PXR_NAMESPACE_CLOSE_SCOPE
