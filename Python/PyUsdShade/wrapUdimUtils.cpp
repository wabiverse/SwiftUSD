//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/tuple.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdShade/udimUtils.h"


PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdShadeUdimUtils()
{
    class_<UsdShadeUdimUtils>("UdimUtils", no_init)
        .def("IsUdimIdentifier", 
            UsdShadeUdimUtils::IsUdimIdentifier,
            (arg("identifier")))
        .staticmethod("IsUdimIdentifier")

        .def("ResolveUdimTilePaths", 
            UsdShadeUdimUtils::ResolveUdimTilePaths,
            (arg("udimPath"), arg("layer")))
        .staticmethod("ResolveUdimTilePaths")

        .def("ReplaceUdimPattern",
            UsdShadeUdimUtils::ReplaceUdimPattern,
            (arg("identifierWithPattern"), arg("replacement")))
        .staticmethod("ReplaceUdimPattern")

        .def("ResolveUdimPath",
            UsdShadeUdimUtils::ResolveUdimPath,
            (arg("udimPath"), arg("layer")))
        .staticmethod("ResolveUdimPath")
        ;

}
