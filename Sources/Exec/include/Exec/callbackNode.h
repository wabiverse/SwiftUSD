//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_EXEC_EXEC_CALLBACK_NODE_H
#define PXR_EXEC_EXEC_CALLBACK_NODE_H

#include "pxr/pxrns.h"

#include "Exec/api.h"

#include "Exec/types.h"

#include "Vdf/node.h"

PXR_NAMESPACE_OPEN_SCOPE

class VdfContext;
class VdfInputSpecs;
class VdfOutputSpecs;

/// Execution node that invokes a provided callback.
class Exec_CallbackNode : public VdfNode
{
public:
    Exec_CallbackNode(
        VdfNetwork *network,
        const VdfInputSpecs &inputSpecs,
        const VdfOutputSpecs &outputSpecs,
        const ExecCallbackFn &callback)
        : VdfNode(network, inputSpecs, outputSpecs)
        , _callback(callback)
    {}

    void Compute(const VdfContext &context) const override;

private:
    ExecCallbackFn _callback;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif