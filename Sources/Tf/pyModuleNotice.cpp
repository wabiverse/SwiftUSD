//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyModuleNotice.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<TfPyModuleWasLoaded, TfType::Bases<TfNotice>>();
}

TfPyModuleWasLoaded::~TfPyModuleWasLoaded() {}

PXR_NAMESPACE_CLOSE_SCOPE
