//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Tf/pyModule.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
    TF_WRAP(UsdValidationRegistry);
    TF_WRAP(UsdValidationTimeRange);
    TF_WRAP(UsdValidationValidator);
    TF_WRAP(UsdValidationFixer);
    TF_WRAP(UsdValidationError);
    TF_WRAP(UsdValidationContext);
    TF_WRAP(UsdValidationNotice);
}
