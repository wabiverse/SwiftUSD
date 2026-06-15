//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdAbc/alembicTest.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdAbcAlembicTest()
{
    def("_TestAlembic", UsdAbc_TestAlembic, arg("pathname"));
    def("_WriteAlembic", UsdAbc_WriteAlembic,
        (arg("srcPathname"), arg("dstPathname")));
}
