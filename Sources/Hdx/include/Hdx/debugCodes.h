//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDX_DEBUG_CODES_H
#define PXR_IMAGING_HDX_DEBUG_CODES_H

#include "Hdx/version.h"
#include "Tf/debug.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEBUG_CODES(

    HDX_DEBUG_DUMP_SHADOW_TEXTURES,
    HDX_DISABLE_ALPHA_TO_COVERAGE,
    HDX_INTERSECT,
    HDX_SELECTION_SETUP

);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HDX_DEBUG_CODES_H
