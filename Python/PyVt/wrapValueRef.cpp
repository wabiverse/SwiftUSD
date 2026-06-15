//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Vt/valueRef.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static VtValue
_test_ValueRefFromPython(VtValueRef valueRef)
{
    return valueRef;
}

void wrapValueRef()
{
    def("_test_ValueRefFromPython", _test_ValueRefFromPython);
}
