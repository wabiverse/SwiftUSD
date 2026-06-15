//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_EXEC_ESF_USD_SCENE_ADAPTER_H
#define PXR_EXEC_ESF_USD_SCENE_ADAPTER_H

/// \file

#include "pxr/pxrns.h"

#include "EsfUsd/api.h"

#include "Esf/attribute.h"
#include "Esf/object.h"
#include "Esf/prim.h"
#include "Esf/property.h"
#include "Esf/stage.h"
#include "Usd/attribute.h"
#include "Usd/common.h"
#include "Usd/object.h"
#include "Usd/prim.h"
#include "Usd/property.h"

PXR_NAMESPACE_OPEN_SCOPE

/// Family of static factory methods that produce abstract scene objects from
/// USD scene objects.
///
/// The underlying implementations of the scene object interfaces are not
/// exported by EsfUsd. Clients can only obtain abstract scene objects by using
/// this class.
///
struct EsfUsdSceneAdapter
{
    static ESFUSD_API
    EsfStage AdaptStage(const UsdStageConstRefPtr &stage);

    static ESFUSD_API
    EsfStage AdaptStage(UsdStageConstRefPtr &&stage);

    static ESFUSD_API
    EsfObject AdaptObject(const UsdObject &object);

    static ESFUSD_API
    EsfObject AdaptObject(UsdObject &&object);

    static ESFUSD_API
    EsfPrim AdaptPrim(const UsdPrim &prim);

    static ESFUSD_API
    EsfPrim AdaptPrim(UsdPrim &&prim);

    static ESFUSD_API
    EsfProperty AdaptProperty(const UsdProperty &property);

    static ESFUSD_API
    EsfProperty AdaptProperty(UsdProperty &&property);

    static ESFUSD_API
    EsfAttribute AdaptAttribute(const UsdAttribute &attribute);

    static ESFUSD_API
    EsfAttribute AdaptAttribute(UsdAttribute &&attribute);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif