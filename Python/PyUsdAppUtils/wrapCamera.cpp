//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "UsdAppUtils/camera.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED


PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;


void
wrapCamera()
{
    def(
        "GetCameraAtPath",
        UsdAppUtilsGetCameraAtPath,
        (arg("stage"), arg("cameraPath")));
}
