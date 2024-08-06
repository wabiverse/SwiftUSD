//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
////////////////////////////////////////////////////////////////////////

#include "Tf/registryManager.h"
#include "Tf/scriptModuleLoader.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfScriptModuleLoader)
{
  // List of direct dependencies for this library.
  const std::vector<TfToken> reqs = {
      TfToken("arch"), TfToken("cameraUtil"), TfToken("garch"),    TfToken("gf"),
      TfToken("glf"),  TfToken("hd"),         TfToken("hdsi"),     TfToken("hdx"),
      TfToken("hgi"),  TfToken("hio"),        TfToken("plug"),     TfToken("pxOsd"),
      TfToken("sdf"),  TfToken("sdr"),        TfToken("tf"),       TfToken("trace"),
      TfToken("usd"),  TfToken("usdGeom"),    TfToken("usdHydra"), TfToken("usdImaging"),
      TfToken("vt"),   TfToken("work")};
  TfScriptModuleLoader::GetInstance().RegisterLibrary(
      TfToken("usdImagingGL"), TfToken("pxr.UsdImagingGL"), reqs);
}

PXR_NAMESPACE_CLOSE_SCOPE
