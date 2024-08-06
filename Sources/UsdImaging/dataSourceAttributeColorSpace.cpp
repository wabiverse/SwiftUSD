//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/dataSourceAttributeColorSpace.h"

#include "Hd/dataSourceLocator.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdImagingDataSourceAttributeColorSpace::UsdImagingDataSourceAttributeColorSpace(
    const UsdAttribute &usdAttr)
    : _usdAttr(usdAttr)
{
}

PXR_NAMESPACE_CLOSE_SCOPE
