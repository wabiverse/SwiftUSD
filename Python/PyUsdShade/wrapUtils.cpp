//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/enum.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/tuple.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdShade/utils.h"
#include "UsdShade/connectableAPI.h"
#include "UsdShade/input.h"
#include "UsdShade/output.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static object 
_GetBaseNameAndType(const TfToken &fullName)
{
    const auto &result = UsdShadeUtils::GetBaseNameAndType(fullName);
    return make_tuple(result.first, result.second);
}

} // anonymous namespace 

void wrapUsdShadeUtils()
{
    UsdShadeAttributeVector (*GetValueProducingAttributes_Input)(
        const UsdShadeInput &input, bool includeAuthoredValues) = 
            &UsdShadeUtils::GetValueProducingAttributes;
    UsdShadeAttributeVector (*GetValueProducingAttributes_Output)(
        const UsdShadeOutput &output, bool includeAuthoredValues) = 
            &UsdShadeUtils::GetValueProducingAttributes;

    scope thisScope = class_<UsdShadeUtils>("Utils", no_init)
        .def("GetPrefixForAttributeType", 
            UsdShadeUtils::GetPrefixForAttributeType)
        .staticmethod("GetPrefixForAttributeType")

        .def("GetConnectedSourcePath", 
             UsdShadeUtils::GetConnectedSourcePath, 
             (arg("connectionSourceInfo")))
        .staticmethod("GetConnectedSourcePath")

        .def("GetBaseNameAndType", _GetBaseNameAndType)
        .staticmethod("GetBaseNameAndType")

        .def("GetType", UsdShadeUtils::GetType)
        .staticmethod("GetType")

        .def("GetFullName", UsdShadeUtils::GetFullName)
        .staticmethod("GetFullName")

        .def("GetValueProducingAttributes", GetValueProducingAttributes_Input,
            (arg("input"), arg("shaderOutputsOnly")=false))
        .def("GetValueProducingAttributes", GetValueProducingAttributes_Output,
            (arg("output"), arg("shaderOutputsOnly")=false))
        .staticmethod("GetValueProducingAttributes")
        ;

}
