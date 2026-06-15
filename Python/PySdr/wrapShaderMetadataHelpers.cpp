//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Sdr/shaderMetadataHelpers.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

// Python has no equivalent notion of namespaces in C++, so
// use an empty class as a namespace standin for Python.
class _MetadataHelpers{};

static tuple
_ParseSdfValue(const std::string& valueStr,
               const SdrShaderPropertyConstPtr& property) {
    std::string err;
    VtValue value = ShaderMetadataHelpers::ParseSdfValue(valueStr, property,
                                                         &err);
    return pxr_boost::python::make_tuple(value, err);
}

} // anonymous namespace

void wrapShaderMetadataHelpers()
{
    class_<_MetadataHelpers>("MetadataHelpers")
        .def("ParseSdfValue", _ParseSdfValue);
}
