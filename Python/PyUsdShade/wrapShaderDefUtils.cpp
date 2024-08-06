//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>
#include <boost/python/scope.hpp>
#include <boost/python/tuple.hpp>

#include "Tf/pyResultConversions.h"

#include "UsdShade/shader.h"
#include "UsdShade/shaderDefUtils.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdShadeShaderDefUtils()
{
  scope thisScope = class_<UsdShadeShaderDefUtils>("ShaderDefUtils", no_init)
                        .def("GetNodeDiscoveryResults",
                             &UsdShadeShaderDefUtils::GetNodeDiscoveryResults,
                             (arg("shaderDef"), arg("sourceUri")),
                             return_value_policy<TfPySequenceToList>())
                        .staticmethod("GetNodeDiscoveryResults")
                        .def("GetShaderProperties",
                             &UsdShadeShaderDefUtils::GetShaderProperties,
                             arg("shaderDef"),
                             return_value_policy<TfPySequenceToList>())
                        .staticmethod("GetShaderProperties")
                        .def("GetPrimvarNamesMetadataString",
                             &UsdShadeShaderDefUtils::GetPrimvarNamesMetadataString,
                             (arg("metadata"), arg("shaderDef")))
                        .staticmethod("GetPrimvarNamesMetadataString");
}
