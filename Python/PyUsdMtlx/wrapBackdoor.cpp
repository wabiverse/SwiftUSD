//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "UsdMtlx/backdoor.h"
#include "Usd/stage.h"
#include "Tf/makePyConstructor.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdMtlxBackdoor()
{
    def("_TestString", UsdMtlx_TestString,
        (arg("buffer"), arg("nodeGraphs") = false),
        return_value_policy<TfPyRefPtrFactory<>>());
    def("_TestFile", UsdMtlx_TestFile,
        (arg("pathname"), arg("nodeGraphs") = false),
        return_value_policy<TfPyRefPtrFactory<>>());
}
