//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Sdf/timeCode.h"
#include "Sdf/layerOffset.h"

#include "Tf/registryManager.h"
#include "Tf/type.h"

#include "Vt/array.h"
#include "Vt/arrayEdit.h"
#include "Vt/value.h"
#include "Vt/valueTransform.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

// Register this class with the TfType registry
// Array registration included to facilitate Sdf/Types and Sdf/ParserHelpers
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<SdfTimeCode>();
    TfType::Define< VtArray<SdfTimeCode> >();
    TfType::Define< VtArrayEdit<SdfTimeCode> >();
}

TF_REGISTRY_FUNCTION(VtValue)
{
    VtValue::RegisterSimpleBidirectionalCast<double, SdfTimeCode>();
    VtRegisterTransform(
        +[](SdfTimeCode const &timeCode, SdfLayerOffset const &offset) {
            return offset * timeCode;
        });
}

std::ostream& 
operator<<(std::ostream& out, const SdfTimeCode& ap)
{
    return out << ap.GetValue();
}

PXR_NAMESPACE_CLOSE_SCOPE
