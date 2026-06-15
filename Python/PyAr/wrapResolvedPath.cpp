//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "Ar/resolvedPath.h"

#include "Tf/pyUtils.h"
#include "Tf/stringUtils.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/implicit.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static std::string
_Repr(const ArResolvedPath& p)
{
    return TfStringPrintf(
        "%sResolvedPath(%s)",
        TF_PY_REPR_PREFIX.c_str(), 
        !p ? "" : TfStringPrintf("'%s'", p.GetPathString().c_str()).c_str());
}

static bool
_IsValid(const ArResolvedPath& p)
{
    return static_cast<bool>(p);
}

void
wrapResolvedPath()
{
    using This = ArResolvedPath;

    class_<This>("ResolvedPath")
        .def(init<>())
        .def(init<const std::string&>())

        .def(self == self)
        .def(self != self)
        .def(self < self)
        .def(self > self)
        .def(self <= self)
        .def(self >= self)

        .def(self == std::string())
        .def(self != std::string())
        .def(self < std::string())
        .def(self > std::string())
        .def(self <= std::string())
        .def(self >= std::string())

        .def("__bool__", _IsValid)
        .def("__hash__", &This::GetHash)
        .def("__repr__", &_Repr)
        .def("__str__", &This::GetPathString,
             return_value_policy<return_by_value>())

        .def("GetPathString", &This::GetPathString,
             return_value_policy<return_by_value>())
        ;

    implicitly_convertible<This, std::string>();
}
