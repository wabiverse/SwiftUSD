//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Sdr/filesystemDiscoveryHelpers.h"
#include "Tf/pyResultConversions.h"
#include "Tf/weakPtr.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/tuple.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static SdrShaderNodeDiscoveryResultVec
_WrapFsHelpersDiscoverShaderNodes(
    const SdrStringVec& searchPaths,
    const SdrStringVec& allowedExtensions,
    bool followSymlinks,
    const TfWeakPtr<SdrDiscoveryPluginContext>& context)
{
    return SdrFsHelpersDiscoverShaderNodes(searchPaths,
                                           allowedExtensions,
                                           followSymlinks,
                                           get_pointer(context));
}

static object
_WrapFsHelpersSplitShaderIdentifier(const TfToken &identifier)
{
    TfToken function, name;
    SdrVersion version;
    if (SdrFsHelpersSplitShaderIdentifier(identifier,
            &function, &name, &version)) {
        return pxr_boost::python::make_tuple(function, name, version);
    } else {
        return object();
    }
}

void wrapFilesystemDiscoveryHelpers()
{
    class_<SdrDiscoveryUri>("DiscoveryUri")
        .def(init<SdrDiscoveryUri>())
        .def_readwrite("uri", &SdrDiscoveryUri::uri)
        .def_readwrite("resolvedUri", &SdrDiscoveryUri::resolvedUri)
    ;

    def("FsHelpersSplitShaderIdentifier", _WrapFsHelpersSplitShaderIdentifier,
        arg("identifier"));
    def("FsHelpersDiscoverShaderNodes", _WrapFsHelpersDiscoverShaderNodes,
        (args("searchPaths"),
        args("allowedExtensions"),
        args("followSymlinks") = true,
        args("context") = TfWeakPtr<SdrDiscoveryPluginContext>()));
    def("FsHelpersDiscoverFiles", SdrFsHelpersDiscoverFiles,
        (args("searchPaths"),
        args("allowedExtensions"),
        args("followSymlinks") = true),
        return_value_policy<TfPySequenceToList>());
}
