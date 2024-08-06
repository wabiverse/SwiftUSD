//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
/// \file debugCodes.cpp

#include "Hgi/debugCodes.h"

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(HGI_DEBUG_DEVICE_CAPABILITIES,
                              "Hgi report when device capabilities are initialized and dump "
                              "contents");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HGI_DEBUG_INSTANCE_CREATION,
                              "Hgi report when attempting to create an Hgi instance");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HGI_DEBUG_IS_SUPPORTED,
                              "Hgi debug info when IsBackendSupported() is false");
}

PXR_NAMESPACE_CLOSE_SCOPE
