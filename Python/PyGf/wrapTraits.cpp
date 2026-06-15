//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Gf/traits.h"
#include "Tf/type.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapTraits()
{
    def("IsFloatingPointType",
        (bool (*)(const TfType&))GfIsFloatingPointType,
        arg("type"),
        "Return True if the TfType represents a floating-point type "
        "(double, float, or GfHalf).");
}
