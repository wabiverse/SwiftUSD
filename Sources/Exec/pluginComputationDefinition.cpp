//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Exec/pluginComputationDefinition.h"

#include "Exec/callbackNode.h"
#include "Exec/program.h"

#include "Tf/delegatedCountPtr.h"
#include "Vdf/connectorSpecs.h"

#include <utility>

PXR_NAMESPACE_OPEN_SCOPE

Exec_PluginComputationDefinition::Exec_PluginComputationDefinition(
    TfType resultType,
    const TfToken &computationName,
    ExecCallbackFn &&callback,
    Exec_InputKeyVectorRefPtr &&inputKeys,
    std::unique_ptr<ExecDispatchesOntoSchemas> &&dispatchesOntoSchemas)
    : Exec_ComputationDefinition(
        resultType,
        computationName)
    , _callback(std::move(callback))
    , _inputKeys(inputKeys)
    , _dispatchesOntoSchemas(std::move(dispatchesOntoSchemas))
{
}

Exec_PluginComputationDefinition::~Exec_PluginComputationDefinition() = default;

bool
Exec_PluginComputationDefinition::IsDispatched() const
{
    return static_cast<bool>(_dispatchesOntoSchemas);
}

const ExecDispatchesOntoSchemas &
Exec_PluginComputationDefinition::GetDispatchesOntoSchemas() const
{
    if (_dispatchesOntoSchemas) {
        return *_dispatchesOntoSchemas;
    }

    TF_CODING_ERROR(
        "Attempt to access dispatched-on schemas for a non-dispatched "
        "computation '%s'", GetComputationName().GetText());
    static const ExecDispatchesOntoSchemas empty;
    return empty;
}

Exec_InputKeyVectorConstRefPtr
Exec_PluginComputationDefinition::GetInputKeys(
    const EsfObjectInterface &,
    EsfJournal *) const
{
    return _inputKeys;
}

VdfNode *
Exec_PluginComputationDefinition::CompileNode(
    const EsfObjectInterface &providerObject,
    const TfToken &,
    EsfJournal *const nodeJournal,
    Exec_Program *const program) const
{
    if (!nodeJournal) {
        TF_CODING_ERROR("Null nodeJournal");
        return nullptr;
    }
    if (!program) {
        TF_CODING_ERROR("Null program");
        return nullptr;
    }

    VdfInputSpecs inputSpecs;
    inputSpecs.Reserve(_inputKeys->Get().size());
    for (const Exec_InputKey &inputKey : _inputKeys->Get()) {
        inputSpecs.ReadConnector(inputKey.resultType, inputKey.inputName);
    }

    VdfOutputSpecs outputSpecs;
    outputSpecs.Connector(
        GetResultType(
            providerObject, /* disambiguatingId */ TfToken(), nodeJournal),
        VdfTokens->out);

    return program->CreateNode<Exec_CallbackNode>(
        *nodeJournal,
        inputSpecs,
        outputSpecs,
        _callback);
}

PXR_NAMESPACE_CLOSE_SCOPE
