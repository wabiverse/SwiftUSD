//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdUtils/registeredVariantSet.h"

#include "Tf/pyResultConversions.h"
#include "Tf/pyEnum.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapRegisteredVariantSet()
{
    scope registeredVariantSet =
        class_<UsdUtilsRegisteredVariantSet>(
                        "RegisteredVariantSet", 
                        "Info for registered variant set",
                        no_init)
            .def_readonly("name", &UsdUtilsRegisteredVariantSet::name)
            .def_readonly("selectionExportPolicy", &UsdUtilsRegisteredVariantSet::selectionExportPolicy)
    ;
    
    typedef UsdUtilsRegisteredVariantSet::SelectionExportPolicy SelectionExportPolicy;
    enum_<SelectionExportPolicy>("SelectionExportPolicy")
        .value("IfAuthored", SelectionExportPolicy::IfAuthored)
        .value("Always", SelectionExportPolicy::Always)
        .value("Never", SelectionExportPolicy::Never)
    ;
    
}
