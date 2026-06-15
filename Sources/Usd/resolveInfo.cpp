//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/resolveInfo.h"
#include "Tf/enum.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE


TF_REGISTRY_FUNCTION(TfEnum)
{
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceNone,
                     "No value");
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceFallback,
                     "Built-in fallback value");
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceDefault,
                     "Attribute default value");
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceTimeSamples,
                     "Attribute time samples");
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceValueClips,
                     "Value clips");
    TF_ADD_ENUM_NAME(UsdResolveInfoSourceSpline,
                     "Spline value");
}

UsdResolveInfo *
UsdResolveInfo::_AddNextWeakerInfo()
{
    if (!TF_VERIFY(!_nextWeaker,
                   "Cannot add weaker info to a UsdResolveInfo that already "
                   "has it.")) {
        return this;
    }
    _nextWeaker = std::make_shared<UsdResolveInfo>();
    return _nextWeaker.get();
}

PXR_NAMESPACE_CLOSE_SCOPE

