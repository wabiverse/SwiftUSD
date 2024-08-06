//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/pyEnum.h"
#include "Usd/interpolation.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdInterpolationType()
{
  TfPyWrapEnum<UsdInterpolationType>();
}
