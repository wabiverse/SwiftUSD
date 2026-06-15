//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#define NUMERIC_OPERATORS

#include "pxr/pxrns.h"
#include "Vt/typeHeaders.h"
#include "Vt/wrapArray.h"
#include "Vt/wrapArrayEdit.h"
#include "Tf/preprocessorUtilsLite.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayFloat() {
    TF_PP_SEQ_FOR_EACH(VT_WRAP_ARRAY, ~,
                       VT_FLOATING_POINT_BUILTIN_VALUE_TYPES);
    TF_PP_SEQ_FOR_EACH(VT_WRAP_ARRAY_EDIT, ~,
                       VT_FLOATING_POINT_BUILTIN_VALUE_TYPES);
}
