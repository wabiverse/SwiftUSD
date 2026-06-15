//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Sdf/pathExpression.h"
#include "Vt/array.h"
#include "Vt/wrapArray.h"
#include "Vt/wrapArrayEdit.h"
#include "Vt/valueFromPython.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace Vt_WrapArray {
    template <>
    std::string GetVtArrayName< VtArray<SdfPathExpression> >() {
        return "PathExpressionArray";
    }
}

template<>
SdfPathExpression VtZero() {
    return SdfPathExpression();
}

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayPathExpression() {
    VtWrapArray<VtArray<SdfPathExpression> >();
    VtValueFromPythonLValue<VtArray<SdfPathExpression> >();
    VtWrapArrayEdit<VtArrayEdit<SdfPathExpression> >();
    VtValueFromPythonLValue<VtArrayEdit<SdfPathExpression> >();
}
