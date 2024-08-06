//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_DEBUG_CODES_H
#define PXR_USD_USD_DEBUG_CODES_H

#include "Tf/debug.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEBUG_CODES(USD_AUTO_APPLY_API_SCHEMAS,
               USD_CHANGES,
               USD_CLIPS,
               USD_COMPOSITION,
               USD_INSTANCING,
               USD_PATH_RESOLUTION,
               USD_PAYLOADS,
               USD_PRIM_LIFETIMES,
               USD_SCHEMA_REGISTRATION,
               USD_STAGE_CACHE,
               USD_STAGE_LIFETIMES,
               USD_STAGE_OPEN,
               USD_STAGE_INSTANTIATION_TIME,
               USD_VALUE_RESOLUTION,
               USD_VALIDATE_VARIABILITY

);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_USD_DEBUG_CODES_H
