//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Glf/drawTarget.h"

#include "Tf/makePyConstructor.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyEnum.h"

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

namespace {

static GlfDrawTargetRefPtr _NewDrawTarget(
    GfVec2i const & size)
{
    return GlfDrawTarget::New(size);
}

static GlfDrawTargetRefPtr _NewDrawTarget2(
    unsigned int width, unsigned int height)
{
    return GlfDrawTarget::New(GfVec2i(width, height));
}

} // anonymous namespace 

void wrapDrawTarget()
{
    typedef GlfDrawTarget This;
    typedef GlfDrawTargetPtr ThisPtr;
    
    class_<This, ThisPtr, noncopyable>("DrawTarget", no_init)
        .def(TfPyRefAndWeakPtr())
        .def("__init__",TfMakePyConstructor(&_NewDrawTarget))
        .def("__init__",TfMakePyConstructor(&_NewDrawTarget2))
        .def("AddAttachment", &This::AddAttachment)
        .def("Bind", &This::Bind)
        .def("Unbind", &This::Unbind)
        .def("WriteToFile", 
            &This::WriteToFile, (
             arg("attachment"),
             arg("filename"),
             arg("viewMatrix") = GfMatrix4d(1),
             arg("projectionMatrix") = GfMatrix4d(1)))
        
        ;
}
