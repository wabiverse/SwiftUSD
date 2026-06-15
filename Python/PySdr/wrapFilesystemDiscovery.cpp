//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/declarePtrs.h"
#include "Tf/makePyConstructor.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyFunction.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Sdr/declare.h"
#include "Sdr/discoveryPlugin.h"
#include "Sdr/filesystemDiscovery.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;
using namespace TfPyContainerConversions;

namespace {

static _SdrFilesystemDiscoveryPluginRefPtr New()
{
    return TfCreateRefPtr(
        new _SdrFilesystemDiscoveryPlugin()
    );
}

static
_SdrFilesystemDiscoveryPluginRefPtr
NewWithFilter(_SdrFilesystemDiscoveryPlugin::Filter filter)
{
    return TfCreateRefPtr(
        new _SdrFilesystemDiscoveryPlugin(std::move(filter))
    );
}

// This is testing discovery from Python.  We need a discovery context
// but Python can't normally create one.  We implement a dummy context
// for just that purpose.
class _SdrContext : public SdrDiscoveryPluginContext {
public:
    ~_SdrContext() override = default;

    TfToken GetShadingSystem(const TfToken& discoveryType) const override
    {
        return discoveryType;
    }

    static TfRefPtr<_SdrContext> New()
    {
        return TfCreateRefPtr(new _SdrContext);
    }
};

void wrapFilesystemDiscoveryContext()
{
    typedef _SdrContext This;
    typedef TfWeakPtr<_SdrContext> ThisPtr;

    class_<This, ThisPtr, bases<SdrDiscoveryPluginContext>, noncopyable>(
        "Context", no_init)
        .def(TfPyRefAndWeakPtr())
        .def(TfMakePyConstructor(This::New))
        ;
}

}

void wrapFilesystemDiscovery()
{
    typedef _SdrFilesystemDiscoveryPlugin This;
    typedef _SdrFilesystemDiscoveryPluginPtr ThisPtr;

    return_value_policy<copy_const_reference> copyRefPolicy;
    from_python_sequence<std::vector<ThisPtr>, variable_capacity_policy>();

    TfPyFunctionFromPython<bool(SdrShaderNodeDiscoveryResult&)>();

    scope s =
    class_<This, ThisPtr, bases<SdrDiscoveryPlugin>, noncopyable>(
        "_FilesystemDiscoveryPlugin", no_init)
        .def(TfPyRefAndWeakPtr())
        .def(TfMakePyConstructor(New))
        .def(TfMakePyConstructor(NewWithFilter))
        .def("DiscoverShaderNodes", &This::DiscoverShaderNodes,
            return_value_policy<TfPySequenceToList>())
        .def("GetSearchURIs", &This::GetSearchURIs, copyRefPolicy)
        ;

    wrapFilesystemDiscoveryContext();
}
