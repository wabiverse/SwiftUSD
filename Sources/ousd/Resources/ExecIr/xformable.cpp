//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "ExecIr/xformable.h"
#include "Usd/schemaRegistry.h"
#include "Usd/typed.h"

#include "Sdf/types.h"
#include "Sdf/assetPath.h"

PXR_NAMESPACE_OPEN_SCOPE

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<ExecIrXformable,
        TfType::Bases< UsdTyped > >();

    // Register the usd prim typename as an alias under UsdSchemaBase. This
    // enables one to call
    // TfType::Find<UsdSchemaBase>().FindDerivedByName("ExecIrXformable")
    // to find TfType<ExecIrXformable>, which is how IsA queries are
    // answered.
    TfType::AddAlias<UsdSchemaBase, ExecIrXformable>("ExecIrXformable");
}

/* virtual */
ExecIrXformable::~ExecIrXformable()
{
}

/* static */
ExecIrXformable
ExecIrXformable::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return ExecIrXformable();
    }
    return ExecIrXformable(stage->GetPrimAtPath(path));
}

/* static */
ExecIrXformable
ExecIrXformable::Define(
    const UsdStagePtr &stage, const SdfPath &path)
{
    static TfToken usdPrimTypeName("ExecIrXformable");
    if (!stage) {
        TF_CODING_ERROR("Invalid stage");
        return ExecIrXformable();
    }
    return ExecIrXformable(
        stage->DefinePrim(path, usdPrimTypeName));
}

/* virtual */
UsdSchemaKind ExecIrXformable::_GetSchemaKind() const
{
    return ExecIrXformable::schemaKind;
}

/* static */
const TfType &
ExecIrXformable::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<ExecIrXformable>();
    return tfType;
}

/* static */
bool
ExecIrXformable::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
ExecIrXformable::_GetTfType() const
{
    return _GetStaticTfType();
}

/*static*/
const TfTokenVector&
ExecIrXformable::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames;
    static TfTokenVector allNames =
        UsdTyped::GetSchemaAttributeNames(true);

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
