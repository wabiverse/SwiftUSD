//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "UsdUI/primHints.h"

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

void wrapUsdUIPrimHints()
{
    using This = UsdUIPrimHints;

    class_<This, bases<UsdUIObjectHints>> clsObj("PrimHints");
    clsObj
        .def(init<UsdPrim>(arg("prim")))

        .def("GetPrim", &This::GetPrim,
             return_value_policy<return_by_value>())

        .def("GetDisplayGroupsExpanded",
             &This::GetDisplayGroupsExpanded)
        .def("SetDisplayGroupsExpanded",
             &This::SetDisplayGroupsExpanded,
             arg("expanded"))

        .def("GetDisplayGroupExpanded",
             &This::GetDisplayGroupExpanded)
        .def("SetDisplayGroupExpanded",
             &This::SetDisplayGroupExpanded,
             (arg("group"),
              arg("expanded")))

        .def("GetDisplayGroupsShownIf",
             &This::GetDisplayGroupsShownIf)
        .def("SetDisplayGroupsShownIf",
             &This::SetDisplayGroupsShownIf,
             arg("expanded"))

        .def("GetDisplayGroupShownIf",
             &This::GetDisplayGroupShownIf)
        .def("SetDisplayGroupShownIf",
             &This::SetDisplayGroupShownIf,
             (arg("group"),
              arg("shownIf")))
        ;

    TfPyRegisterStlSequencesFromPython<This>();
    to_python_converter<
        std::vector<This>,
        TfPySequenceToPython<std::vector<This>>>();
}
