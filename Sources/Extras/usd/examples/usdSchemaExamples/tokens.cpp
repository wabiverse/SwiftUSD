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
#include "./tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdSchemaExamplesTokensType::UsdSchemaExamplesTokensType()
    : complexString("complexString", TfToken::Immortal),
      intAttr("intAttr", TfToken::Immortal),
      paramsMass("params:mass", TfToken::Immortal),
      paramsVelocity("params:velocity", TfToken::Immortal),
      paramsVolume("params:volume", TfToken::Immortal),
      target("target", TfToken::Immortal),
      ComplexPrim("ComplexPrim", TfToken::Immortal),
      ParamsAPI("ParamsAPI", TfToken::Immortal),
      SimplePrim("SimplePrim", TfToken::Immortal),
      allTokens({complexString,
                 intAttr,
                 paramsMass,
                 paramsVelocity,
                 paramsVolume,
                 target,
                 ComplexPrim,
                 ParamsAPI,
                 SimplePrim})
{
}

TfStaticData<UsdSchemaExamplesTokensType> UsdSchemaExamplesTokens;

PXR_NAMESPACE_CLOSE_SCOPE
