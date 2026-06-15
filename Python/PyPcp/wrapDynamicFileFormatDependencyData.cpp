//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Pcp/dynamicFileFormatDependencyData.h"
#include "Tf/pyResultConversions.h"
#include "Vt/value.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void 
wrapDynamicFileFormatDependencyData()
{
    using This = PcpDynamicFileFormatDependencyData;
    class_<This>("DynamicFileFormatDependencyData", no_init)     
        .def("GetRelevantFieldNames",
             make_function(&This::GetRelevantFieldNames,
                           return_value_policy< TfPySequenceToList >()))
        .def("GetRelevantAttributeNames",
             make_function(&This::GetRelevantAttributeNames,
                           return_value_policy< TfPySequenceToList >()))
        .def("CanFieldChangeAffectFileFormatArguments", 
             &This::CanFieldChangeAffectFileFormatArguments)
        .def("CanAttributeDefaultValueChangeAffectFileFormatArguments", 
             &This::CanAttributeDefaultValueChangeAffectFileFormatArguments)
        .def("IsEmpty", &This::IsEmpty)
        ;
}
