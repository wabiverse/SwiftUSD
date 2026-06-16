//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "UsdLux/blackbody.h"
#include "Tf/pyModule.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
    pxr_boost::python::def("BlackbodyTemperatureAsRgb",
                       UsdLuxBlackbodyTemperatureAsRgb);

    // Generated Schema classes.  Do not remove or edit the following line.
    #include <UsdLux/generatedSchema.module.h>
}
