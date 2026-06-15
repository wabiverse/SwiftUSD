//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "EsfUsd/relationship.h"

#include "Esf/relationship.h"
#include "Usd/relationship.h"

PXR_NAMESPACE_OPEN_SCOPE

// EsfRelationship should not reserve more space than necessary.
static_assert(sizeof(EsfUsd_Relationship) == sizeof(EsfRelationship));

EsfUsd_Relationship::~EsfUsd_Relationship() = default;

SdfPathVector
EsfUsd_Relationship::_GetTargets() const
{
    SdfPathVector targets;
    _GetWrapped().GetTargets(&targets);
    return targets;
}

PXR_NAMESPACE_CLOSE_SCOPE
