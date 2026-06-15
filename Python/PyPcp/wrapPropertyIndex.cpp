//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Pcp/propertyIndex.h"
#include "Pcp/primIndex.h"
#include "Pcp/cache.h"

#include "Tf/pyResultConversions.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static SdfPropertySpecHandleVector
_WrapPropertyStack(const PcpPropertyIndex& propIndex)
{
    const PcpPropertyRange range = propIndex.GetPropertyRange();
    return SdfPropertySpecHandleVector(range.first, range.second);
}

static SdfPropertySpecHandleVector
_WrapLocalPropertyStack(const PcpPropertyIndex& propIndex)
{
    const PcpPropertyRange range = 
        propIndex.GetPropertyRange(/* localOnly= */ true);
    return SdfPropertySpecHandleVector(range.first, range.second);
}

static pxr_boost::python::tuple
_WrapBuildPrimPropertyIndex(
    const SdfPath &path, const PcpCache &cache, const PcpPrimIndex &primIndex)
{
    PcpErrorVector errors;
    PcpPropertyIndex propIndex;
    PcpBuildPrimPropertyIndex(path, cache, primIndex, &propIndex, &errors);

    return pxr_boost::python::make_tuple(
        pxr_boost::python::object(propIndex), errors);
}

} // anonymous namespace 

void
wrapPropertyIndex()
{
    typedef PcpPropertyIndex This;

    def("BuildPrimPropertyIndex", _WrapBuildPrimPropertyIndex);

    class_<This>
        ("PropertyIndex", "", no_init)
        .add_property("propertyStack", _WrapPropertyStack)
        .add_property("localPropertyStack", _WrapLocalPropertyStack)
        .add_property("localErrors", 
                      make_function(&This::GetLocalErrors,
                                    return_value_policy<TfPySequenceToList>()))
        ;
}
