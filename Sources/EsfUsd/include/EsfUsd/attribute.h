//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_EXEC_ESF_USD_ATTRIBUTE_H
#define PXR_EXEC_ESF_USD_ATTRIBUTE_H

#include "pxr/pxrns.h"

#include "EsfUsd/property.h"

#include "Esf/attribute.h"
#include "Esf/attributeQuery.h"
#include "Usd/attribute.h"

PXR_NAMESPACE_OPEN_SCOPE

/// Implementation of EsfAttributeInterface that wraps a UsdAttribute.
class EsfUsd_Attribute
    : public EsfUsd_PropertyImpl<EsfAttributeInterface, UsdAttribute>
{
public:
    ~EsfUsd_Attribute() override;

    /// Copies the provided \p attribute into this instance.
    EsfUsd_Attribute(const UsdAttribute &attribute)
        : EsfUsd_PropertyImpl<EsfAttributeInterface, UsdAttribute>(
            attribute) {}

    /// Moves the provided \p attribute into this instance.
    EsfUsd_Attribute(UsdAttribute &&attribute)
        : EsfUsd_PropertyImpl<EsfAttributeInterface, UsdAttribute>(
            std::move(attribute)) {}

private:
    // EsfAttributeInterface implementation.
    SdfValueTypeName _GetValueTypeName() const final;
    EsfAttributeQuery _GetQuery() const final;
    SdfPathVector _GetConnections() const final;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
