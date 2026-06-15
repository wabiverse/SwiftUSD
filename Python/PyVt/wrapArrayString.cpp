//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#define ADDITION_OPERATOR

#include "pxr/pxrns.h"
#include "Vt/typeHeaders.h"
#include "Vt/wrapArray.h"
#include "Vt/wrapArrayEdit.h"

#include <string>
using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayString() {
    VtWrapArray<VtArray<string> >();
    VtWrapArrayEdit<VtArrayEdit<string> >();
}
