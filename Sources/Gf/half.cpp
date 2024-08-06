//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Gf/half.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<GfHalf>();
}

PXR_NAMESPACE_CLOSE_SCOPE
