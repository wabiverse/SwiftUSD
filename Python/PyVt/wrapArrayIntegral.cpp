//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#define NUMERIC_OPERATORS
#define MOD_OPERATOR

#include "Tf/preprocessorUtilsLite.h"
#include "Vt/typeHeaders.h"
#include "Vt/wrapArray.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayIntegral()
{
  TF_PP_SEQ_FOR_EACH(VT_WRAP_ARRAY, ~, VT_INTEGRAL_BUILTIN_VALUE_TYPES);
}
