//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/registryManager.h"
#include "Tf/scriptModuleLoader.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfScriptModuleLoader)
{
  // List of direct dependencies for this library.
  const std::vector<TfToken> reqs = {TfToken("arch"),
                                     TfToken("gf"),
                                     TfToken("plug"),
                                     TfToken("tf"),
                                     TfToken("trace"),
                                     TfToken("vt")};
  TfScriptModuleLoader::GetInstance().RegisterLibrary(TfToken("ts"), TfToken("pxr.Ts"), reqs);
}

PXR_NAMESPACE_CLOSE_SCOPE
