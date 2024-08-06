//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HF_DIAGNOSTIC_H
#define PXR_IMAGING_HF_DIAGNOSTIC_H

#include "Tf/diagnostic.h"
#include "Tf/stringUtils.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

///
/// Issues a warning with a message.  This differs from just calling TF_WARN
/// in that it tags the warning as actually needing to be a validation error,
/// and a place holder for when we develop a true validation system where we
/// can plumb this information back to the application.
///
#define HF_VALIDATION_WARN(id, ...) \
  TF_WARN("Invalid Hydra prim '%s': %s", id.GetText(), TfStringPrintf(__VA_ARGS__).c_str())

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HF_DIAGNOSTIC_H
