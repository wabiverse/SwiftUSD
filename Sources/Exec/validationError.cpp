//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Exec/validationError.h"

#include "Tf/enum.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfEnum)
{
    TF_ADD_ENUM_NAME(
        ExecValidationErrorType::DataDependencyCycle, "Data Dependency Cycle");
}

PXR_NAMESPACE_CLOSE_SCOPE
