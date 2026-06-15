//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/resolveTarget.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdResolveTarget()
{
    class_<UsdResolveTarget>("ResolveTarget")
        .def(init<>())
        .def("GetPrimIndex", &UsdResolveTarget::GetPrimIndex, 
             return_value_policy<return_by_value>())
        .def("GetStartNode", &UsdResolveTarget::GetStartNode)
        .def("GetStartLayer", &UsdResolveTarget::GetStartLayer)
        .def("GetStopNode", &UsdResolveTarget::GetStopNode)
        .def("GetStopLayer", &UsdResolveTarget::GetStopLayer)
        .def("IsNull", &UsdResolveTarget::IsNull)
        ;
}
