//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/interpolation.h"
#include "pxr/pxrns.h"

#include "Tf/enum.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfEnum)
{
  TF_ADD_ENUM_NAME(UsdInterpolationTypeHeld, "Held");
  TF_ADD_ENUM_NAME(UsdInterpolationTypeLinear, "Linear");
}

PXR_NAMESPACE_CLOSE_SCOPE
