//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#define NUMERIC_OPERATORS

#include "pxr/pxrns.h"
#include "Vt/typeHeaders.h"
#include "Vt/types.h"
#include "Vt/valueFromPython.h"
#include "Vt/wrapArray.h"
#include "Vt/wrapArrayEdit.h"
#include "Tf/preprocessorUtilsLite.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayTimeCode() {
    TF_PP_SEQ_FOR_EACH(VT_WRAP_ARRAY, ~, VT_TIMECODE_VALUE_TYPES);
    TF_PP_SEQ_FOR_EACH(VT_WRAP_ARRAY_EDIT, ~, VT_TIMECODE_VALUE_TYPES);
}
