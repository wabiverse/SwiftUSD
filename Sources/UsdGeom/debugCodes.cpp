//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/debugCodes.h"
#include "pxr/pxrns.h"

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(USDGEOM_EXTENT,
                              "Reports when Boundable "
                              "extents are computed dynamically because no cached authored "
                              "attribute is present in the scene.");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USDGEOM_BBOX, "UsdGeom bounding box computation");
}

PXR_NAMESPACE_CLOSE_SCOPE
