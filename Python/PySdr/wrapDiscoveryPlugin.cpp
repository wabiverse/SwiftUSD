//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/declarePtrs.h"
#include "Tf/pyPtrHelpers.h"
#include "Sdr/discoveryPlugin.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static void wrapDiscoveryPluginContext()
{
    typedef SdrDiscoveryPluginContext This;
    typedef TfWeakPtr<SdrDiscoveryPluginContext> ThisPtr;

    class_<This, ThisPtr, noncopyable>("DiscoveryPluginContext", no_init)
        .def(TfPyWeakPtr())
        .def("GetShadingSystem", pure_virtual(&This::GetShadingSystem))
        .def("GetSourceType", pure_virtual(&This::GetSourceType))
        ;
}

void wrapDiscoveryPlugin()
{
    typedef SdrDiscoveryPlugin This;
    typedef SdrDiscoveryPluginPtr ThisPtr;

    return_value_policy<copy_const_reference> copyRefPolicy;

    class_<This, ThisPtr, noncopyable>("DiscoveryPlugin", no_init)
        .def(TfPyWeakPtr())
        .def("DiscoverShaderNodes", pure_virtual(&This::DiscoverShaderNodes))
        .def("GetSearchURIs", pure_virtual(&This::GetSearchURIs), copyRefPolicy)
        ;

    wrapDiscoveryPluginContext();
}
