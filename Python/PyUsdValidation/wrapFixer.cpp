//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "UsdValidation/fixer.h"
#include "UsdValidation/error.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdValidationFixer()
{
    class_<UsdValidationFixer>("ValidationFixer", no_init)
        .add_property("name",
            make_function(
                +[](const UsdValidationFixer &fixer) { 
                      return fixer.GetName(); 
                },
                return_value_policy<return_by_value>()))
        .add_property("description",
            make_function(
                +[](const UsdValidationFixer &fixer) { 
                    return fixer.GetDescription(); 
                },
                return_value_policy<return_by_value>()))
        .add_property("errorName",
            make_function(
                +[](const UsdValidationFixer &fixer) { 
                    return fixer.GetErrorName(); 
                },
                return_value_policy<return_by_value>()))
        .add_property("keywords",
            make_function(
                +[](const UsdValidationFixer &fixer) { 
                    return fixer.GetKeywords(); 
                },
                return_value_policy<TfPySequenceToList>()))
        .def("IsAssociatedWithErrorName", 
             &UsdValidationFixer::IsAssociatedWithErrorName, (arg("errorName")))
        .def("HasKeyword", 
             &UsdValidationFixer::HasKeyword, (arg("keyword")))
        .def("CanApplyFix", 
             &UsdValidationFixer::CanApplyFix,
             (arg("error"), arg("editTarget"), 
              arg("timeCode") = UsdTimeCode::Default()))
        .def("ApplyFix", 
             &UsdValidationFixer::ApplyFix,
             (arg("error"), arg("editTarget"), 
              arg("timeCode") = UsdTimeCode::Default()));

    TfPyRegisterStlSequencesFromPython<const UsdValidationFixer*>();
}
