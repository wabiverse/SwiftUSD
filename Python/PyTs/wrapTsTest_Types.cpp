//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Ts/tsTest_Types.h"
#include "Ts/spline.h"
#include "Tf/pyContainerConversions.h"
#include "Vt/value.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/extract.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include <sstream>
#include <string>
#include <cstdio>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;


// Return a full-precision python repr for a double value.
static std::string
_HexFloatRepr(const double num)
{
    // XXX: work around std::hexfloat apparently not working in our libstdc++ as
    // of this writing.
    char buf[100];
    sprintf(buf, "float.fromhex('%a')", num);
    return std::string(buf);
}

static std::string
_SampleRepr(const TsTest_Sample &sample)
{
    std::ostringstream result;

    result << "Ts.TsTest_Sample("
           << _HexFloatRepr(sample.time)
           << ", " << _HexFloatRepr(sample.value)
           << ")";

    return result.str();
}

static 
TsSpline
_TestTsSplineToVtValueFromPython(VtValue val) {
    if (!val.IsHolding<TsSpline>()) {
        TF_CODING_ERROR("VtValue did not hold a TsSpline.");
        // Default Spline, but we are interested in the coding error so we
        // don't care.
        return TsSpline();
    }

    return val.UncheckedGet<TsSpline>();
}

void wrapTsTest_Types()
{
    class_<TsTest_Sample>("TsTest_Sample")
        // Default init is not suppressed, so automatically created.
        .def(init<double, double>())
        .def(init<const TsTest_Sample&>())
        .def("__repr__", &_SampleRepr)
        .def_readwrite("time", &TsTest_Sample::time)
        .def_readwrite("value", &TsTest_Sample::value)
        ;

    def("_TestTsSplineToVtValueFromPython", 
        _TestTsSplineToVtValueFromPython);

    to_python_converter<
        TsTest_SampleVec,
        TfPySequenceToPython<TsTest_SampleVec>>();
    TfPyContainerConversions::from_python_sequence<
        TsTest_SampleVec,
        TfPyContainerConversions::variable_capacity_policy>();
}
