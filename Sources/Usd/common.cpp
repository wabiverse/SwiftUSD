//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/enum.h"
#include "Tf/envSetting.h"
#include "pxr/pxrns.h"

#include "Usd/common.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_ENV_SETTING(USD_SHADING_MODEL,
                      "usdRi",
                      "Set to usdRi when models can interchange UsdShade prims.");

TF_REGISTRY_FUNCTION(TfEnum)
{
  TF_ADD_ENUM_NAME(UsdListPosition::UsdListPositionFrontOfPrependList,
                   "The front of the prepend list.");
  TF_ADD_ENUM_NAME(UsdListPosition::UsdListPositionBackOfPrependList,
                   "The back of the prepend list.");
  TF_ADD_ENUM_NAME(UsdListPosition::UsdListPositionFrontOfAppendList,
                   "The front of the append list.");
  TF_ADD_ENUM_NAME(UsdListPosition::UsdListPositionBackOfAppendList,
                   "The back of the append list.");

  TF_ADD_ENUM_NAME(UsdLoadPolicy::UsdLoadPolicyWithDescendants, "Load prim and all descendants");
  TF_ADD_ENUM_NAME(UsdLoadPolicy::UsdLoadPolicyWithoutDescendants, "Load prim and no descendants");
}

PXR_NAMESPACE_CLOSE_SCOPE
