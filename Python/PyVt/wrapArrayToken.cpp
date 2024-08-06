//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Vt/typeHeaders.h"
#include "Vt/wrapArray.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayToken()
{
  VtWrapArray<VtArray<TfToken>>();
}
