//
// Copyright 2019 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "hdPrman/debugCodes.h"

#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug)
{
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_PRIMVARS, "Primvars");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_MATERIALS, "Materials");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_DUMP_MATERIALX_OSL_SHADER,
                              "Print MaterialX Generated Osl Shaders");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_LIGHT_LINKING, "Light linking");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_LIGHT_LIST, "Light list");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_VSTRUCTS, "Vstruct expansion");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_LIGHT_FILTER_LINKING, "Light filter linking");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_IMAGE_ASSET_RESOLVE, "Resolved image asset paths");
  TF_DEBUG_ENVIRONMENT_SYMBOL(HDPRMAN_INSTANCERS, "Instancers");
}

PXR_NAMESPACE_CLOSE_SCOPE
