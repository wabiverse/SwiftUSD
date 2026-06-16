//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Gf/interval.h"
#include "Usd/timeCode.h"

#include "UsdValidation/timeRange.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/make_constructor.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdValidationTimeRange()
{
    class_<UsdValidationTimeRange>("ValidationTimeRange")
        .def(init<const UsdTimeCode &>(
            args("timeCode")))
        .def(init<const GfInterval &, bool>(
            (args("interval"), args("includeTimeCodeDefault") = false)))
        .def("IncludesTimeCodeDefault", 
             &UsdValidationTimeRange::IncludesTimeCodeDefault)
        .def("GetInterval", &UsdValidationTimeRange::GetInterval);
}
