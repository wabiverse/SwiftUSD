//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "UsdUtils/conditionalAbortDiagnosticDelegate.h"

#include "Tf/pyResultConversions.h"

#include <iostream>
#include <string>

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/list.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/tuple.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapConditionalAbortDiagnosticDelegate()
{
    using ErrorFilters = UsdUtilsConditionalAbortDiagnosticDelegateErrorFilters;
    class_<ErrorFilters>("ConditionalAbortDiagnosticDelegateErrorFilters",
            init<std::vector<std::string>, std::vector<std::string>>())
        .def(init<>())
        .def("GetCodePathFilters", &ErrorFilters::GetCodePathFilters, 
                return_value_policy<TfPySequenceToList>())
        .def("GetStringFilters", &ErrorFilters::GetStringFilters,
                return_value_policy<TfPySequenceToList>())
        .def("SetStringFilters", &ErrorFilters::SetStringFilters,
                args("stringFilters"))
        .def("SetCodePathFilters", &ErrorFilters::SetCodePathFilters,
                args("codePathFilters"));

    using This = UsdUtilsConditionalAbortDiagnosticDelegate;
    class_<This, noncopyable>("ConditionalAbortDiagnosticDelegate",
            init<ErrorFilters, ErrorFilters>());
}
