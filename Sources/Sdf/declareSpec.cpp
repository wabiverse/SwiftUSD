//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Sdf/attributeSpec.h"
#include "Sdf/primSpec.h"
#include "Sdf/propertySpec.h"
#include "Sdf/pseudoRootSpec.h"
#include "Sdf/relationshipSpec.h"
#include "Sdf/schema.h"
#include "Sdf/spec.h"
#include "Sdf/types.h"
#include "Sdf/variantSpec.h"
#include "Sdf/variantSetSpec.h"

#include "Tf/type.h"

// This file contains all required type definitions and spec registrations
// for Sdf spec types. We register all spec types in one go to avoid potential
// timing related issues with multi-threaded TfRegistryFunction subscriptions.
// By performing all registrations in a single registry function we can be sure
// that everything is fully registered when a call to
// SubscribeTo<SdfSpecTypeRegistration> is complete.

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<SdfSpec>();
    TfType::Define<SdfPropertySpec, TfType::Bases<SdfSpec> >();   
    TfType::Define<SdfPrimSpec, TfType::Bases<SdfSpec> >();
    TfType::Define<SdfVariantSpec, TfType::Bases<SdfSpec> >();
    TfType::Define<SdfVariantSetSpec, TfType::Bases<SdfSpec> >();
    TfType::Define<SdfPseudoRootSpec, TfType::Bases<SdfPrimSpec> >();
    TfType::Define<SdfAttributeSpec, TfType::Bases<SdfPropertySpec> >();
    TfType::Define<SdfRelationshipSpec, TfType::Bases<SdfPropertySpec> >();
}  

TF_REGISTRY_FUNCTION(SdfSpecTypeRegistration)
{
    SdfSpecTypeRegistration::RegisterAbstractSpecType<SdfSchema, SdfSpec>();
    SdfSpecTypeRegistration::RegisterAbstractSpecType<
        SdfSchema, SdfPropertySpec>();
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfPrimSpec>
        (SdfSpecTypePrim);
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfVariantSpec>
        (SdfSpecTypeVariant);
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfVariantSetSpec>
        (SdfSpecTypeVariantSet);
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfPseudoRootSpec>
        (SdfSpecTypePseudoRoot);
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfAttributeSpec>
        (SdfSpecTypeAttribute);
    SdfSpecTypeRegistration::RegisterSpecType<SdfSchema, SdfRelationshipSpec>
        (SdfSpecTypeRelationship);

}

PXR_NAMESPACE_CLOSE_SCOPE
