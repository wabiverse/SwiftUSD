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
  const std::vector<TfToken> reqs = {TfToken("plug"),
                                     TfToken("sdf"),
                                     TfToken("tf"),
                                     TfToken("trace"),
                                     TfToken("usd"),
                                     TfToken("usdGeom"),
                                     TfToken("vt"),
                                     TfToken("work")};
  TfScriptModuleLoader::GetInstance().RegisterLibrary(
      TfToken("usdVol"), TfToken("pxr.UsdVol"), reqs);
}

PXR_NAMESPACE_CLOSE_SCOPE
