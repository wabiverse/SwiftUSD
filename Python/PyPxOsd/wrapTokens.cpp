//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "PxOsd/tokens.h"
#include "pxr/pxrns.h"

#include "Tf/pyStaticTokens.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapTokens()
{
  TF_PY_WRAP_PUBLIC_TOKENS("OpenSubdivTokens", PxOsdOpenSubdivTokens, PXOSD_OPENSUBDIV_TOKENS);
}
