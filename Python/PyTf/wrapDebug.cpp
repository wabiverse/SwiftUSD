//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Arch/fileSystem.h"
#include "Tf/debug.h"

// XXX: This include is a hack to avoid build errors due to
// incompatible macro definitions in pyport.h on macOS.
#include <locale>

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static void
_SetOutputFile(object const &file)
{
    int filefd = PyObject_AsFileDescriptor(file.ptr());
    if (filefd == ArchFileNo(stdout)) {
        TfDebug::SetOutputFile(stdout);
    }
    else if (filefd == ArchFileNo(stderr)) {
        TfDebug::SetOutputFile(stderr);
    }
    else {
        // reports an error indicating correct usage, either stdout or stderr
        TfDebug::SetOutputFile(NULL);
    }
}

} // anonymous namespace 

void wrapDebug()
{
    typedef TfDebug This;

    class_<This>("Debug", no_init)
        .def("SetDebugSymbolsByName", &This::SetDebugSymbolsByName,
             ( arg("pattern"), arg("value") ))
        .staticmethod("SetDebugSymbolsByName")

        .def("IsDebugSymbolNameEnabled", &This::IsDebugSymbolNameEnabled)
        .staticmethod("IsDebugSymbolNameEnabled")

        .def("GetDebugSymbolDescriptions", &This::GetDebugSymbolDescriptions)
        .staticmethod("GetDebugSymbolDescriptions")

        .def("GetDebugSymbolNames", &This::GetDebugSymbolNames)
        .staticmethod("GetDebugSymbolNames")

        .def("GetDebugSymbolDescription", &This::GetDebugSymbolDescription)
        .staticmethod("GetDebugSymbolDescription")

        .def("SetOutputFile", _SetOutputFile)
        .staticmethod("SetOutputFile")

        ;
}
