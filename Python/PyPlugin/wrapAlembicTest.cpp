//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include <boost/python/def.hpp>

#include "Plugin/usdAbc/alembicTest.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdAbcAlembicTest()
{
  def("_TestAlembic", UsdAbc_TestAlembic, arg("pathname"));
  def("_WriteAlembic", UsdAbc_WriteAlembic, (arg("srcPathname"), arg("dstPathname")));
}
