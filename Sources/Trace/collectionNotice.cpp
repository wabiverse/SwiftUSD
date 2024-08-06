//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Trace/collectionNotice.h"

#include "Tf/registryManager.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<TraceCollectionAvailable, TfType::Bases<TfNotice>>();
}

TraceCollectionAvailable::~TraceCollectionAvailable() {}

PXR_NAMESPACE_CLOSE_SCOPE
