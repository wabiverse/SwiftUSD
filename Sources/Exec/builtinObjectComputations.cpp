//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Exec/builtinObjectComputations.h"

#include "Exec/builtinComputations.h"
#include "Exec/metadataInputNode.h"
#include "Exec/privateBuiltinComputations.h"
#include "Exec/program.h"
#include "Vdf/context.h"
#include "Vdf/inputVector.h"

#include "Tf/diagnosticLite.h"
#include "Tf/type.h"
#include "Esf/object.h"
#include "Sdf/path.h"

PXR_NAMESPACE_OPEN_SCOPE

//
// computeMetadata
//

Exec_ComputeMetadataComputationDefinition::
Exec_ComputeMetadataComputationDefinition()
    : Exec_ComputationDefinition(
        TfType::GetUnknownType(),
        Exec_PrivateBuiltinComputations->computeMetadata)
{
}

Exec_ComputeMetadataComputationDefinition::
~Exec_ComputeMetadataComputationDefinition() = default;

TfType
Exec_ComputeMetadataComputationDefinition::GetResultType(
    const EsfObjectInterface &providerObject,
    const TfToken &disambiguatingId,
    EsfJournal *const journal) const
{
    return providerObject.GetMetadataValueType(disambiguatingId);
}

TfType
Exec_ComputeMetadataComputationDefinition::GetExtractionType(
    const EsfObjectInterface &providerObject) const
{
    TF_VERIFY(false, "Extracting metdata values directly is not supported.");
    return TfType();
}

Exec_InputKeyVectorConstRefPtr
Exec_ComputeMetadataComputationDefinition::GetInputKeys(
    const EsfObjectInterface &providerObject,
    EsfJournal *) const
{
    return Exec_InputKeyVector::GetEmptyVector();
}

VdfNode *
Exec_ComputeMetadataComputationDefinition::CompileNode(
    const EsfObjectInterface &providerObject,
    const TfToken &disambiguatingId,
    EsfJournal *const nodeJournal,
    Exec_Program *const program) const
{
    if (!TF_VERIFY(nodeJournal, "Null nodeJournal")) {
        return nullptr;
    }
    if (!TF_VERIFY(program, "Null program")) {
        return nullptr;
    }
    if (!providerObject.IsValidMetadataKey(disambiguatingId)) {
        TF_CODING_ERROR(
            "Skipping compilation of input node for invalid metadata key '%s'",
            disambiguatingId.GetText());
        return nullptr;
    }

    return program->CreateNode<Exec_MetadataInputNode>(
        *nodeJournal,
        providerObject.AsObject(),
        disambiguatingId,
        GetResultType(providerObject, disambiguatingId, nodeJournal));
}

//
// computePath
//

Exec_ComputePathComputationDefinition::
Exec_ComputePathComputationDefinition()
    : Exec_ComputationDefinition(
        TfType::Find<SdfPath>(),
        ExecBuiltinComputations->computePath)
{
}

Exec_ComputePathComputationDefinition::
~Exec_ComputePathComputationDefinition() = default;

Exec_InputKeyVectorConstRefPtr
Exec_ComputePathComputationDefinition::GetInputKeys(
    const EsfObjectInterface &providerObject,
    EsfJournal *) const
{
    return Exec_InputKeyVector::GetEmptyVector();
}

VdfNode *
Exec_ComputePathComputationDefinition::CompileNode(
    const EsfObjectInterface &providerObject,
    const TfToken &disambiguatingId,
    EsfJournal *const nodeJournal,
    Exec_Program *const program) const
{
    if (!TF_VERIFY(nodeJournal, "Null nodeJournal")) {
        return nullptr;
    }
    if (!TF_VERIFY(program, "Null program")) {
        return nullptr;
    }

    // We provide a path value by creating a VdfInputVector because each unique
    // value corresponds to a different object, so there's no need for the kind
    // of sharing we do for Exec_ConstantValueNode.

    // Get the path before creating the node, so that we update the journal.
    SdfPath path = providerObject.GetPath(nodeJournal);

    // Create the input vector and set the data.
    VdfInputVector<SdfPath> *const node =
        program->CreateNode<VdfInputVector<SdfPath>>(*nodeJournal, /* size */ 1);
    node->SetValue(0, std::move(path));

    return node;
}

PXR_NAMESPACE_CLOSE_SCOPE
