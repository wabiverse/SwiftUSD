//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "pxr/pxrns.h"
#include "Gf/limits.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapLimits()
{
    scope().attr("MIN_VECTOR_LENGTH") = GF_MIN_VECTOR_LENGTH;
    scope().attr("MIN_ORTHO_TOLERANCE") = GF_MIN_ORTHO_TOLERANCE;
}
