//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/bakeSkinning.h"

#include "Usd/primRange.h"
#include "UsdSkel/cache.h"
#include "UsdSkel/root.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdSkelBakeSkinning()
{
  def("BakeSkinning",
      ((bool (*)(const UsdSkelRoot &, const GfInterval &)) & UsdSkelBakeSkinning),
      (arg("root"), arg("interval") = GfInterval::GetFullInterval()));

  def("BakeSkinning",
      ((bool (*)(const UsdPrimRange &, const GfInterval &)) & UsdSkelBakeSkinning),
      (arg("range"), arg("interval") = GfInterval::GetFullInterval()));
}
