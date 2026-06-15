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
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/tuple.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "Tf/pyResultConversions.h"

#include "UsdShade/shaderDefUtils.h"
#include "UsdShade/shader.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdShadeShaderDefUtils()
{
    scope thisScope = class_<UsdShadeShaderDefUtils>("ShaderDefUtils", no_init)
        .def("GetDiscoveryResults", 
             &UsdShadeShaderDefUtils::GetDiscoveryResults,
             (arg("shaderDef"), arg("sourceUri")),
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetDiscoveryResults")
        .def("GetProperties", 
             &UsdShadeShaderDefUtils::GetProperties,
             arg("shaderDef"),
             return_value_policy<TfPySequenceToList>())
        .staticmethod("GetProperties")
        .def("GetPrimvarNamesMetadataString", 
             &UsdShadeShaderDefUtils::GetPrimvarNamesMetadataString,
             (arg("metadata"), arg("shaderDef")))
        .staticmethod("GetPrimvarNamesMetadataString")
    ;
}
