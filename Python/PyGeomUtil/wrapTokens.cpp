//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "GeomUtil/tokens.h"

#include "Tf/pyStaticTokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapTokens()
{
    TF_PY_WRAP_PUBLIC_TOKENS(
        "InterpolationTokens",
        GeomUtilInterpolationTokens, GEOMUTIL_INTERPOLATION_TOKENS);
}

