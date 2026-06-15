//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Plug/testPlugBase.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/args.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include "Tf/makePyConstructor.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyContainerConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

template <class T>
void wrap_TestPlugBase(const std::string & name)
{
    typedef T This;
    typedef TfWeakPtr<T> ThisPtr;
    class_<This, ThisPtr, noncopyable> ( name.c_str(), no_init )
        .def(TfPyRefAndWeakPtr())
        .def(TfMakePyConstructor(&This::New))

        // Expose Manufacture as another initializer.
        .def(TfMakePyConstructor(&This::Manufacture))

        .def("GetTypeName", &This::GetTypeName)

        .def("TestAcceptPluginSequence", &This::TestAcceptPluginSequence,
             (arg("plugins")));

        ;
}

} // anonymous namespace 

void wrap_TestPlugBase()
{
    wrap_TestPlugBase<_TestPlugBase1>("_TestPlugBase1");
    wrap_TestPlugBase<_TestPlugBase2>("_TestPlugBase2");
    wrap_TestPlugBase<_TestPlugBase3>("_TestPlugBase3");
    wrap_TestPlugBase<_TestPlugBase4>("_TestPlugBase4");
}
