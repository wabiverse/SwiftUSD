//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "EsfUsd/property.h"

#include "Esf/attribute.h"
#include "Esf/relationship.h"
#include "Usd/attribute.h"
#include "Usd/relationship.h"

PXR_NAMESPACE_OPEN_SCOPE

// EsfProperty should not reserve more space than necessary.
static_assert(sizeof(EsfUsd_Property) == sizeof(EsfProperty));

template <class InterfaceType, class UsdPropertyType>
EsfUsd_PropertyImpl<InterfaceType, UsdPropertyType>::~EsfUsd_PropertyImpl()
    = default;

template <class InterfaceType, class UsdPropertyType>
TfToken
EsfUsd_PropertyImpl<InterfaceType, UsdPropertyType>::_GetBaseName() const
{
    return this->_GetWrapped().GetBaseName();
}

template <class InterfaceType, class UsdPropertyType>
TfToken
EsfUsd_PropertyImpl<InterfaceType, UsdPropertyType>::_GetNamespace() const
{
    return this->_GetWrapped().GetNamespace();
}

// Explicit template instantiations
template class EsfUsd_PropertyImpl<EsfAttributeInterface, UsdAttribute>;
template class EsfUsd_PropertyImpl<EsfPropertyInterface, UsdProperty>;
template class EsfUsd_PropertyImpl<EsfRelationshipInterface, UsdRelationship>;

PXR_NAMESPACE_CLOSE_SCOPE
