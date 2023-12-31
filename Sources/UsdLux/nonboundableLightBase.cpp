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
#include "UsdLux/nonboundableLightBase.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/types.h"
#include "Sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdLuxNonboundableLightBase,
        TfType::Bases< UsdGeomXformable > >();
    
}

/* virtual */
UsdLuxNonboundableLightBase::~UsdLuxNonboundableLightBase()
{
}

/* static */
UsdLuxNonboundableLightBase
UsdLuxNonboundableLightBase::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdLuxNonboundableLightBase();
    }
    return UsdLuxNonboundableLightBase(stage->GetPrimAtPath(path));
}


/* virtual */
UsdSchemaKind UsdLuxNonboundableLightBase::_GetSchemaKind() const
{
    return UsdLuxNonboundableLightBase::schemaKind;
}

/* static */
const TfType &
UsdLuxNonboundableLightBase::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdLuxNonboundableLightBase>();
    return tfType;
}

/* static */
bool 
UsdLuxNonboundableLightBase::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdLuxNonboundableLightBase::_GetTfType() const
{
    return _GetStaticTfType();
}

/*static*/
const TfTokenVector&
UsdLuxNonboundableLightBase::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames;
    static TfTokenVector allNames =
        UsdGeomXformable::GetSchemaAttributeNames(true);

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

UsdAttribute
UsdLuxNonboundableLightBase::GetIntensityAttr() const
{
    return LightAPI().GetIntensityAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateIntensityAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateIntensityAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetExposureAttr() const
{
    return LightAPI().GetExposureAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateExposureAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateExposureAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetDiffuseAttr() const
{
    return LightAPI().GetDiffuseAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateDiffuseAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateDiffuseAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetSpecularAttr() const
{
    return LightAPI().GetSpecularAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateSpecularAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateSpecularAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetNormalizeAttr() const
{
    return LightAPI().GetNormalizeAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateNormalizeAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateNormalizeAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetColorAttr() const
{
    return LightAPI().GetColorAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateColorAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateColorAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetEnableColorTemperatureAttr() const
{
    return LightAPI().GetEnableColorTemperatureAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateEnableColorTemperatureAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateEnableColorTemperatureAttr(
        defaultValue, writeSparsely);
}

UsdAttribute
UsdLuxNonboundableLightBase::GetColorTemperatureAttr() const
{
    return LightAPI().GetColorTemperatureAttr();
}

UsdAttribute
UsdLuxNonboundableLightBase::CreateColorTemperatureAttr(
    VtValue const &defaultValue, bool writeSparsely) const
{
    return LightAPI().CreateColorTemperatureAttr(
        defaultValue, writeSparsely);
}

UsdRelationship
UsdLuxNonboundableLightBase::GetFiltersRel() const
{
    return LightAPI().GetFiltersRel();
}

UsdRelationship
UsdLuxNonboundableLightBase::CreateFiltersRel() const
{
    return LightAPI().CreateFiltersRel();
}

UsdLuxLightAPI 
UsdLuxNonboundableLightBase::LightAPI() const
{
    return UsdLuxLightAPI(GetPrim());
}

PXR_NAMESPACE_CLOSE_SCOPE
