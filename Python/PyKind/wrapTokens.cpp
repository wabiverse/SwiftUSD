//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Kind/registry.h"
#include "Tf/pyStaticTokens.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapTokens()
{
  TF_PY_WRAP_PUBLIC_TOKENS("Tokens", KindTokens, KIND_TOKENS);
}
