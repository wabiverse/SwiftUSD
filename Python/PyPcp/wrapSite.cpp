//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Pcp/site.h"
#include "Tf/stringUtils.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static std::string
_PcpSiteStr(const PcpSite& x)
{
    return TfStringify(x);
}

static std::string
_PcpLayerStackSiteStr(const PcpLayerStackSite& x)
{
    return TfStringify(x);
}

} // anonymous namespace 

void wrapSite()
{    
    class_<PcpSite>
        ("Site", "", no_init)
        .add_property("layerStack", 
                      make_getter(&PcpSite::layerStackIdentifier,
                                  return_value_policy<return_by_value>()),
                      make_setter(&PcpSite::layerStackIdentifier))
        .add_property("path", 
                      make_getter(&PcpSite::path,
                                  return_value_policy<return_by_value>()),
                      make_setter(&PcpSite::path))
        .def("__str__", &_PcpSiteStr)
        ;

    class_<PcpLayerStackSite>
        ("LayerStackSite", "", no_init)
        .add_property("layerStack", 
                      make_getter(&PcpLayerStackSite::layerStack,
                                  return_value_policy<return_by_value>()),
                      make_setter(&PcpLayerStackSite::layerStack))
        .add_property("path", 
                      make_getter(&PcpLayerStackSite::path,
                                  return_value_policy<return_by_value>()),
                      make_setter(&PcpLayerStackSite::path))
        .def("__str__", &_PcpLayerStackSiteStr)
        ;
}
