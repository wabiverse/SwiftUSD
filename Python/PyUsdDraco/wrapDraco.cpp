//
// Copyright 2019 Google LLC
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include <UsdDraco/writer.h>

#include "pxr/pxrns.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdDraco()
{
    def("_WriteDraco", UsdDraco_WriteDraco,
        (arg("mesh"),
         arg("fileName"),
         arg("qp"),
         arg("qt"),
         arg("qn"),
         arg("cl"),
         arg("preservePolygons"),
         arg("preservePositionOrder"),
         arg("preserveHoles")));
    def("_PrimvarSupported", UsdDraco_PrimvarSupported,
        (arg("primvar")));
}
