//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include <locale>

#include "UsdRi/rmanUtilities.h"

#include "Tf/token.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_by_value.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdRiRmanUtilities()
{
    def("ConvertToRManInterpolateBoundary", (int (*)(const TfToken &))
        UsdRiConvertToRManInterpolateBoundary,
        return_value_policy<return_by_value>());
    def("ConvertFromRManInterpolateBoundary", (const TfToken & (*)(int))
        UsdRiConvertFromRManInterpolateBoundary,
        return_value_policy<return_by_value>());

    def("ConvertToRManFaceVaryingLinearInterpolation",
        (int (*)(const TfToken &))
        UsdRiConvertToRManFaceVaryingLinearInterpolation,
        return_value_policy<return_by_value>());
    def("ConvertFromRManFaceVaryingLinearInterpolation",
        (const TfToken & (*)(int))
        UsdRiConvertFromRManFaceVaryingLinearInterpolation,
        return_value_policy<return_by_value>());

    def("ConvertRManSetSpecificationToListOp",
        &UsdRiConvertRManSetSpecificationToListOp);
    def("DoesAttributeUseSetSpecification",
        &UsdRiDoesAttributeUseSetSpecification);
}
