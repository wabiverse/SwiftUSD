//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "pxr/pxrns.h"
#include "Ar/defaultResolver.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void
wrapDefaultResolver()
{
    using This = ArDefaultResolver;

    class_<This, bases<ArResolver>, noncopyable>
        ("DefaultResolver", no_init)

        .def("SetDefaultSearchPath", &This::SetDefaultSearchPath,
             args("searchPath"))
        .staticmethod("SetDefaultSearchPath")
        ;
}
