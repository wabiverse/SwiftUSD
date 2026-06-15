//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Glf/texture.h"

#include "Tf/makePyConstructor.h"
#include "Tf/pyPtrHelpers.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/bases.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/overloads.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapTexture()
{    
    typedef GlfTexture This;
    typedef GlfTexturePtr ThisPtr;

    class_<This, ThisPtr, noncopyable>(
        "Texture", no_init)
        .def("GetTextureMemoryAllocated", &This::GetTextureMemoryAllocated)
        .staticmethod("GetTextureMemoryAllocated")

        .add_property( "memoryUsed", make_function(
                &This::GetMemoryUsed,
                return_value_policy<return_by_value>()))

        .add_property( "memoryRequested", make_function(
                &This::GetMemoryRequested,
                return_value_policy<return_by_value>()),
                &This::SetMemoryRequested)

        .add_property( "minFilterSupported", make_function(
                &This::IsMinFilterSupported,
                return_value_policy<return_by_value>()))

        .add_property( "magFilterSupported", make_function(
                &This::IsMagFilterSupported,
                return_value_policy<return_by_value>()))
        ;
}
