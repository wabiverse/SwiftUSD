//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Exec/nodeRecompilationInfo.h"

#include "Exec/inputKey.h"

#include "Tf/token.h"
#include "Vdf/input.h"
#include "Vdf/node.h"

PXR_NAMESPACE_OPEN_SCOPE

TfSmallVector<const Exec_InputKey *, 1>
Exec_NodeRecompilationInfo::GetInputKeys(const VdfInput &input) const
{
    TfSmallVector<const Exec_InputKey *, 1> matchingInputKeys;
    const TfToken &inputName = input.GetName();
    const TfType inputType = input.GetSpec().GetType();

    for (const Exec_InputKey &inputKey : _inputKeys->Get()) {
        if (inputKey.inputName == inputName &&
            inputKey.resultType == inputType) {
            matchingInputKeys.push_back(&inputKey);
        }
    }
    
    if (!TF_VERIFY(!matchingInputKeys.empty(),
        "Recompilation could not obtain input keys for '%s' on node '%s'",
        input.GetName().GetText(),
        input.GetNode().GetDebugName().c_str())) {
    }

    return matchingInputKeys;
}

PXR_NAMESPACE_CLOSE_SCOPE
