//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Pcp/debugCodes.h"
#include "Arch/functionLite.h"
#include "Tf/debug.h"
#include "Tf/registryManager.h"
#include "Tf/stringUtils.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_CHANGES, "Pcp change processing");
  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_DEPENDENCIES, "Pcp dependencies");

  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_PRIM_INDEX,
                              "Print debug output to terminal during prim indexing");

  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_PRIM_INDEX_GRAPHS,
                              "Write graphviz 'dot' files during prim indexing "
                              "(requires PCP_PRIM_INDEX)");

  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_PRIM_INDEX_GRAPHS_MAPPINGS,
                              "Include namespace mappings in graphviz files generated "
                              "during prim indexing (requires PCP_PRIM_INDEX_GRAPHS)");

  TF_DEBUG_ENVIRONMENT_SYMBOL(PCP_NAMESPACE_EDIT, "Pcp namespace edits");
}

PXR_NAMESPACE_CLOSE_SCOPE
