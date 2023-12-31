//
// Copyright 2016 Pixar
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
#include "Usd/debugCodes.h"
#include <pxr/pxrns.h>

#include "Tf/debug.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfDebug) {
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_AUTO_APPLY_API_SCHEMAS,
                              "USD API schema auto application details");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_CHANGES, "USD change processing");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_CLIPS, "USD clip details");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_COMPOSITION, "USD composition details");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_DATA_BD, "USD BD file format traces");
  TF_DEBUG_ENVIRONMENT_SYMBOL(
      USD_DATA_BD_TRY, "USD BD call traces. Prints names, errors and results.");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_INSTANCING, "USD instancing diagnostics");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_PATH_RESOLUTION,
                              "USD path resolution diagnostics");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_PAYLOADS, "USD payload load/unload messages");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_PRIM_LIFETIMES,
                              "USD prim ctor/dtor messages");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_SCHEMA_REGISTRATION,
                              "USD schema registration details.");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_STAGE_CACHE, "USD stage cache details");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_STAGE_LIFETIMES,
                              "USD stage ctor/dtor messages");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_STAGE_OPEN, "USD stage opening details");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_STAGE_INSTANTIATION_TIME,
                              "USD stage instantiation timing");
  TF_DEBUG_ENVIRONMENT_SYMBOL(USD_VALIDATE_VARIABILITY,
                              "USD attribute variability validation");
  TF_DEBUG_ENVIRONMENT_SYMBOL(
      USD_VALUE_RESOLUTION,
      "USD trace of layers inspected as values are resolved");
}

PXR_NAMESPACE_CLOSE_SCOPE
