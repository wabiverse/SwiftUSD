//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/resolveInfo.h"
#include "Tf/pyEnum.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_internal_reference.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdResolveInfo()
{
    class_<UsdResolveInfo>("ResolveInfo")
        .def("GetSource", &UsdResolveInfo::GetSource)
        .def("HasAuthoredValueOpinion",
             &UsdResolveInfo::HasAuthoredValueOpinion)
        .def("HasAuthoredValue",
             &UsdResolveInfo::HasAuthoredValue)
        .def("GetNode", &UsdResolveInfo::GetNode)
        .def("ValueIsBlocked", &UsdResolveInfo::ValueIsBlocked)
        .def("ValueSourceMightBeTimeVarying",
             &UsdResolveInfo::ValueSourceMightBeTimeVarying)
        .def("HasNextWeakerInfo",
             &UsdResolveInfo::HasNextWeakerInfo)
        .def("GetNextWeakerInfo",
             &UsdResolveInfo::GetNextWeakerInfo,
             return_internal_reference<>())
        ;

    TfPyWrapEnum<UsdResolveInfoSource>();
}
