//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "Ar/packageResolver.h"

#include "Tf/registryManager.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<ArPackageResolver>();
}

ArPackageResolver::ArPackageResolver() {}

ArPackageResolver::~ArPackageResolver() {}

PXR_NAMESPACE_CLOSE_SCOPE
