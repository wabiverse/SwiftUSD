//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/debugNotice.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<TfDebugSymbolsChangedNotice, TfType::Bases<TfNotice>>();
  TfType::Define<TfDebugSymbolEnableChangedNotice, TfType::Bases<TfNotice>>();
}

TfDebugSymbolsChangedNotice::~TfDebugSymbolsChangedNotice() {}
TfDebugSymbolEnableChangedNotice::~TfDebugSymbolEnableChangedNotice() {}

PXR_NAMESPACE_CLOSE_SCOPE
