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
#include "UsdLux/pluginLightFilter.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/types.h"
#include "Sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdLuxPluginLightFilter,
        TfType::Bases< UsdLuxLightFilter > >();
    
    // Register the usd prim typename as an alias under UsdSchemaBase. This
    // enables one to call
    // TfType::Find<UsdSchemaBase>().FindDerivedByName("PluginLightFilter")
    // to find TfType<UsdLuxPluginLightFilter>, which is how IsA queries are
    // answered.
    TfType::AddAlias<UsdSchemaBase, UsdLuxPluginLightFilter>("PluginLightFilter");
}

/* virtual */
UsdLuxPluginLightFilter::~UsdLuxPluginLightFilter()
{
}

/* static */
UsdLuxPluginLightFilter
UsdLuxPluginLightFilter::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdLuxPluginLightFilter();
    }
    return UsdLuxPluginLightFilter(stage->GetPrimAtPath(path));
}

/* static */
UsdLuxPluginLightFilter
UsdLuxPluginLightFilter::Define(
    const UsdStagePtr &stage, const SdfPath &path)
{
    static TfToken usdPrimTypeName("PluginLightFilter");
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdLuxPluginLightFilter();
    }
    return UsdLuxPluginLightFilter(
        stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind UsdLuxPluginLightFilter::_GetSchemaKind() const
{
    return UsdLuxPluginLightFilter::schemaKind;
}

/* static */
const TfType &
UsdLuxPluginLightFilter::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdLuxPluginLightFilter>();
    return tfType;
}

/* static */
bool 
UsdLuxPluginLightFilter::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdLuxPluginLightFilter::_GetTfType() const
{
    return _GetStaticTfType();
}

/*static*/
const TfTokenVector&
UsdLuxPluginLightFilter::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames;
    static TfTokenVector allNames =
        UsdLuxLightFilter::GetSchemaAttributeNames(true);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

PXR_NAMESPACE_CLOSE_SCOPE

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
//
// Just remember to wrap code in the appropriate delimiters:
// 'PXR_NAMESPACE_OPEN_SCOPE', 'PXR_NAMESPACE_CLOSE_SCOPE'.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

PXR_NAMESPACE_OPEN_SCOPE

UsdShadeNodeDefAPI 
UsdLuxPluginLightFilter::GetNodeDefAPI() const
{
    return UsdShadeNodeDefAPI(GetPrim());
}

PXR_NAMESPACE_CLOSE_SCOPE
