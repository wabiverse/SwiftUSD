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

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED


PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;


void wrapUsdSkelBakeSkinning()
{
    def("BakeSkinning", ((bool (*)(const UsdSkelRoot&,
                                   const GfInterval&))&UsdSkelBakeSkinning),
        (arg("root"), arg("interval")=GfInterval::GetFullInterval()));

    def("BakeSkinning", ((bool (*)(const UsdPrimRange&,
                                   const GfInterval&))&UsdSkelBakeSkinning),
        (arg("range"), arg("interval")=GfInterval::GetFullInterval()));

}
