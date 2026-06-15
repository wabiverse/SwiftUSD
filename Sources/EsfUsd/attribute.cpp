//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "EsfUsd/attribute.h"

#include "EsfUsd/attributeQuery.h"
#include "EsfUsd/stageData.h"

#include "Esf/attribute.h"
#include "Sdf/valueTypeName.h"
#include "Usd/attribute.h"
#include "Usd/attributeQuery.h"

PXR_NAMESPACE_OPEN_SCOPE

// EsfAttribute should not reserve more space than necessary.
static_assert(sizeof(EsfUsd_Attribute) == sizeof(EsfAttribute));

EsfUsd_Attribute::~EsfUsd_Attribute() = default;

SdfValueTypeName
EsfUsd_Attribute::_GetValueTypeName() const
{
    return _GetWrapped().GetTypeName();
}

EsfAttributeQuery
EsfUsd_Attribute::_GetQuery() const
{
    return {
        std::in_place_type<EsfUsd_AttributeQuery>,
        UsdAttributeQuery(_GetWrapped())
    };
}

SdfPathVector
EsfUsd_Attribute::_GetConnections() const
{
    return EsfUsdStageData::GetOutgoingConnections(
        _GetWrapped().GetStage(), _GetWrapped().GetPath());
}

PXR_NAMESPACE_CLOSE_SCOPE
