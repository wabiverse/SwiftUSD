//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdVol/particleFieldKernelBaseAPI.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/types.h"
#include "Sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdVolParticleFieldKernelBaseAPI,
        TfType::Bases< UsdAPISchemaBase > >();
    
}

/* virtual */
UsdVolParticleFieldKernelBaseAPI::~UsdVolParticleFieldKernelBaseAPI()
{
}

/* static */
UsdVolParticleFieldKernelBaseAPI
UsdVolParticleFieldKernelBaseAPI::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdVolParticleFieldKernelBaseAPI();
    }
    return UsdVolParticleFieldKernelBaseAPI(stage->GetPrimAtPath(path));
}


/* virtual */
UsdSchemaKind UsdVolParticleFieldKernelBaseAPI::_GetSchemaKind() const
{
    return UsdVolParticleFieldKernelBaseAPI::schemaKind;
}

/* static */
bool
UsdVolParticleFieldKernelBaseAPI::CanApply(
    const UsdPrim &prim, std::string *whyNot)
{
    return prim.CanApplyAPI<UsdVolParticleFieldKernelBaseAPI>(whyNot);
}

/* static */
UsdVolParticleFieldKernelBaseAPI
UsdVolParticleFieldKernelBaseAPI::Apply(const UsdPrim &prim)
{
    if (prim.ApplyAPI<UsdVolParticleFieldKernelBaseAPI>()) {
        return UsdVolParticleFieldKernelBaseAPI(prim);
    }
    return UsdVolParticleFieldKernelBaseAPI();
}

/* static */
const TfType &
UsdVolParticleFieldKernelBaseAPI::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdVolParticleFieldKernelBaseAPI>();
    return tfType;
}

/* static */
bool 
UsdVolParticleFieldKernelBaseAPI::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdVolParticleFieldKernelBaseAPI::_GetTfType() const
{
    return _GetStaticTfType();
}

/*static*/
const TfTokenVector&
UsdVolParticleFieldKernelBaseAPI::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames;
    static TfTokenVector allNames =
        UsdAPISchemaBase::GetSchemaAttributeNames(true);

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
