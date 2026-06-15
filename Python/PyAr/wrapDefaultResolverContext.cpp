//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_by_value.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "pxr/pxrns.h"
#include "Ar/defaultResolverContext.h"
#include "Ar/pyResolverContext.h"
#include "Tf/pyUtils.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static std::string
_Repr(const ArDefaultResolverContext& ctx)
{
    std::string repr = TF_PY_REPR_PREFIX;
    repr += "DefaultResolverContext(";
    if (!ctx.GetSearchPath().empty()) {
        repr += TfPyRepr(ctx.GetSearchPath());
    }
    repr += ")";
    return repr;
}

static size_t
_Hash(const ArDefaultResolverContext& ctx)
{
    return hash_value(ctx);
}

void
wrapDefaultResolverContext()
{
    using This = ArDefaultResolverContext;

    class_<This>
        ("DefaultResolverContext", no_init)
        .def(init<>())
        .def(init<const std::vector<std::string>&>(
                arg("searchPaths")))

        .def(self == self)
        .def(self != self)

        .def("GetSearchPath", &This::GetSearchPath,
             return_value_policy<return_by_value>())

        .def("__str__", &This::GetAsString)
        .def("__repr__", &_Repr)
        .def("__hash__", &_Hash)
        ;

    ArWrapResolverContextForPython<This>();
}
