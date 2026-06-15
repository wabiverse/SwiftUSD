//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Plug/plugin.h"
#include "Js/converter.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"
#include "Tf/iterator.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#include <string>

using std::string;
using std::vector;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static dict
_ConvertDict( const JsObject & dictionary )
{
    dict result;
    TF_FOR_ALL(i, dictionary) {
        const string & key = i->first;
        const JsValue & val = i->second;

        result[key] = JsConvertToContainerType<object, dict>(val);
    }
    return result;
}

static dict
_GetMetadata(PlugPluginPtr plugin)
{
    return _ConvertDict(plugin->GetMetadata());
}

static dict
_GetMetadataForType(PlugPluginPtr plugin, const TfType &type)
{
    return _ConvertDict(plugin->GetMetadataForType(type));
}

} // anonymous namespace 

void wrapPlugin()
{
    typedef PlugPlugin This;
    typedef PlugPluginPtr ThisPtr;

    class_<This, ThisPtr, noncopyable> ( "Plugin", no_init )
        .def(TfPyWeakPtr())
        .def("Load", &This::Load)

        .add_property("isLoaded", &This::IsLoaded)
        .add_property("isPythonModule", &This::IsPythonModule)
        .add_property("isResource", &This::IsResource)

        .add_property("metadata", _GetMetadata)

        .add_property("name",
                      make_function(&This::GetName,
                                    return_value_policy<return_by_value>()))
        .add_property("path",
                      make_function(&This::GetPath,
                                    return_value_policy<return_by_value>()))
        .add_property("resourcePath",
                      make_function(&This::GetResourcePath,
                                    return_value_policy<return_by_value>()))

        .def("GetMetadataForType", _GetMetadataForType)
        .def("DeclaresType", &This::DeclaresType,
             (arg("type"), 
              arg("includeSubclasses") = false))

        .def("MakeResourcePath", &This::MakeResourcePath)
        .def("FindPluginResource", &This::FindPluginResource,
             (arg("path"), 
              arg("verify") = true))
        ;
        TfPyRegisterStlSequencesFromPython<PlugPluginPtr>();

    // The call to JsConvertToContainerType in _ConvertDict creates
    // vectors of pxr_boost::python::objects for array values, so register
    // a converter that turns that vector into a Python list.
    pxr_boost::python::to_python_converter<std::vector<object>,
        TfPySequenceToPython<std::vector<object> > >();
}
