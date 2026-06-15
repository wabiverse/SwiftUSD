//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Glf/diagnostic.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapDiagnostic()
{    
    def("RegisterDefaultDebugOutputMessageCallback",
        &GlfRegisterDefaultDebugOutputMessageCallback);

    class_<GlfGLQueryObject, noncopyable>("GLQueryObject")
        .def("Begin", &GlfGLQueryObject::Begin)
        .def("BeginPrimitivesGenerated", &GlfGLQueryObject::BeginPrimitivesGenerated)
        .def("BeginTimeElapsed", &GlfGLQueryObject::BeginTimeElapsed)
        .def("BeginSamplesPassed", &GlfGLQueryObject::BeginSamplesPassed)
        .def("End", &GlfGLQueryObject::End)
        .def("GetResult", &GlfGLQueryObject::GetResult)
        .def("GetResultNoWait", &GlfGLQueryObject::GetResultNoWait)

        ;
}
