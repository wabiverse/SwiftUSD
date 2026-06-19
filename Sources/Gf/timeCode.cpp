//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Gf/timeCode.h"
#include "Tf/registryManager.h"
#include "Tf/type.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType) {
    TfType::Define<GfTimeCode>();
}

std::ostream&
operator<<(std::ostream& out, const GfTimeCode& tc)
{
    return out << tc.GetValue();
}

PXR_NAMESPACE_CLOSE_SCOPE
