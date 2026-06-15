//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "UsdUI/propertyHints.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/implicit.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <vector>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdUIPropertyHints()
{
    using This = UsdUIPropertyHints;

    class_<This, bases<UsdUIObjectHints>>
        clsObj("PropertyHints");
    clsObj
        .def(init<UsdProperty>(arg("prop")))

        .def("GetProperty", &This::GetProperty,
             return_value_policy<return_by_value>())

        .def("GetDisplayGroup", &This::GetDisplayGroup)
        .def("SetDisplayGroup", &This::SetDisplayGroup,
             arg("group"))

        .def("GetShownIf", &This::GetShownIf)
        .def("SetShownIf", &This::SetShownIf,
             arg("shownIf"))
        ;

    TfPyRegisterStlSequencesFromPython<This>();
    to_python_converter<
        std::vector<This>,
        TfPySequenceToPython<std::vector<This>>>();
}
