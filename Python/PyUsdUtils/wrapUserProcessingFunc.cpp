//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyResultConversions.h"
#include "Tf/pyFunction.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdUtils/userProcessingFunc.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUserProcessingFunc()
{
    TfPyFunctionFromPython<UsdUtilsProcessingFunc>();
    
    typedef UsdUtilsDependencyInfo This;

    class_<This>("DependencyInfo", init<>())
        .def(init<const This&>())
        .def(init<const std::string &>())
        .def(init<const std::string &, const std::vector<std::string>>())
        .add_property("assetPath", make_function(&This::GetAssetPath,
            return_value_policy<return_by_value>()))
        .add_property("dependencies", make_function(&This::GetDependencies,
            return_value_policy<TfPySequenceToList>()))
    ;
}
