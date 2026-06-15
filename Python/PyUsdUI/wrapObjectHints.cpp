//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "UsdUI/objectHints.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyStaticTokens.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <vector>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdUIObjectHints()
{
    TF_PY_WRAP_PUBLIC_TOKENS(
        "HintKeys", UsdUIHintKeys, USDUI_HINT_KEYS);

    using This = UsdUIObjectHints;

    class_<This> clsObj("ObjectHints");
    clsObj
        .def(init<UsdObject>(arg("obj")))

        .def(self == self)
        .def(self != self)
        .def(!self)

        .def("GetObject", &This::GetObject,
             return_value_policy<return_by_value>())

        .def("GetDisplayName", &This::GetDisplayName)
        .def("SetDisplayName", &This::SetDisplayName,
             arg("name"))

        .def("GetHidden", &This::GetHidden)
        .def("SetHidden", &This::SetHidden,
             arg("hidden"))
        ;

    TfPyRegisterStlSequencesFromPython<This>();
    to_python_converter<
        std::vector<This>,
        TfPySequenceToPython<std::vector<This>>>();
}
