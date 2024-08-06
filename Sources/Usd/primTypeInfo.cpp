//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/primTypeInfo.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdPrimTypeInfo::UsdPrimTypeInfo(_TypeId &&typeId)
    : _typeId(std::move(typeId)), _primDefinition(nullptr)
{
  // Helper for initializing the schema type from either the mapped type
  // name or the prim type name.
  auto _SetSchemaType = [this](const TfToken &typeName) {
    // Empty type name returns false.
    if (typeName.IsEmpty()) {
      return false;
    }
    _schemaType = UsdSchemaRegistry::GetConcreteTypeFromSchemaTypeName(typeName);
    if (_schemaType) {
      _schemaTypeName = typeName;
    }
    // Return true even if the schema type is invalid since the type name
    // is not empty.
    return true;
  };

  // Set the schema type using the mapped type name over the prim type
  // name if we have a mapped type name.
  _SetSchemaType(_typeId.mappedTypeName) || _SetSchemaType(_typeId.primTypeName);
}

const UsdPrimDefinition *UsdPrimTypeInfo::_FindOrCreatePrimDefinition() const
{
  const UsdPrimDefinition *primDef = nullptr;
  const UsdSchemaRegistry &reg = UsdSchemaRegistry::GetInstance();
  if (_typeId.appliedAPISchemas.empty()) {
    // With no applied schemas we can just get the concrete typed prim
    // definition from the schema registry. Prim definitions for all
    // concrete types are created with the schema registry when it is
    // instantiated so if the type exists, the definition will be there.
    primDef = reg.FindConcretePrimDefinition(_schemaTypeName);
    if (!primDef) {
      // For invalid types, we use the empty prim definition so we don't
      // have to check again.
      primDef = reg.GetEmptyPrimDefinition();
    }
    // Cache the prim definition pointer. The schema registry created the
    // prim definition and will continue to own it so the pointer value
    // will be constant. Thus, we don't have to check if another thread
    // cached it first as all threads would store the same pointer.
    _primDefinition.store(primDef, std::memory_order_relaxed);
  }
  else {
    // If we have applied schemas, then we need ask the schema registry to
    // compose a prim definition for us from the list of types. The schema
    // registry does NOT take ownership of this new prim definition; this
    // type info will own it instead.
    std::unique_ptr<UsdPrimDefinition> composedPrimDef = reg.BuildComposedPrimDefinition(
        _schemaTypeName, _typeId.appliedAPISchemas);
    // Try to cache the new prim definition, but if another thread beat us
    // to it, we'll use its definition instead and just let ours get
    // deleted.
    if (_primDefinition.compare_exchange_strong(
            primDef, composedPrimDef.get(), std::memory_order_acq_rel))
    {
      // Since we succeeded, transfer ownership of the new prim definition
      // to this type info.
      _ownedPrimDefinition = std::move(composedPrimDef);
      primDef = _ownedPrimDefinition.get();
    }
  }
  return primDef;
}

/*static*/
const UsdPrimTypeInfo &UsdPrimTypeInfo::GetEmptyPrimType()
{
  static const UsdPrimTypeInfo empty;
  return empty;
}

PXR_NAMESPACE_CLOSE_SCOPE
