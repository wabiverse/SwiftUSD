//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdf/valueTypeName.h"
#include "Sdf/valueTypePrivate.h"
#include "pxr/pxrns.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

namespace {

template<typename C, typename V> bool IsValueIn(const C &container, V value)
{
  for (const auto &element : container) {
    if (element == value) {
      return true;
    }
  }
  return false;
}

}  // anonymous namespace

//
// SdfTupleDimensions
//

bool SdfTupleDimensions::operator==(const SdfTupleDimensions &rhs) const
{
  if (size != rhs.size) {
    return false;
  }
  if (size >= 1 && d[0] != rhs.d[0]) {
    return false;
  }
  if (size >= 2 && d[1] != rhs.d[1]) {
    return false;
  }
  return true;
}

//
// SdfValueTypeName
//

SdfValueTypeName::SdfValueTypeName() : _impl(Sdf_ValueTypePrivate::GetEmptyTypeName())
{
  // Do nothing
}

SdfValueTypeName::SdfValueTypeName(const Sdf_ValueTypeImpl *impl) : _impl(impl)
{
  // Do nothing
}

TfToken SdfValueTypeName::GetAsToken() const
{
  return _impl->name;
}

const TfType &SdfValueTypeName::GetType() const
{
  return _impl->type->type;
}

const std::string &SdfValueTypeName::GetCPPTypeName() const
{
  return _impl->type->cppTypeName;
}

const TfToken &SdfValueTypeName::GetRole() const
{
  return _impl->type->role;
}

const VtValue &SdfValueTypeName::GetDefaultValue() const
{
  return _impl->type->value;
}

const TfEnum &SdfValueTypeName::GetDefaultUnit() const
{
  return _impl->type->unit;
}

SdfValueTypeName SdfValueTypeName::GetScalarType() const
{
  return SdfValueTypeName(_impl->scalar);
}

SdfValueTypeName SdfValueTypeName::GetArrayType() const
{
  return SdfValueTypeName(_impl->array);
}

bool SdfValueTypeName::IsScalar() const
{
  return *this && _impl == _impl->scalar;
}

bool SdfValueTypeName::IsArray() const
{
  return *this && _impl == _impl->array;
}

SdfTupleDimensions SdfValueTypeName::GetDimensions() const
{
  return _impl->type->dim;
}

bool SdfValueTypeName::operator==(const SdfValueTypeName &rhs) const
{
  // Do equality comparisons on core type to ensure that
  // equivalent type names from different registries compare
  // equal. The registry ensures that type and role are
  // the only things we need to look at here.
  return (_impl->type->type == rhs._impl->type->type &&
          _impl->type->role == rhs._impl->type->role);
}

bool SdfValueTypeName::operator==(const std::string &rhs) const
{
  return IsValueIn(_impl->type->aliases, rhs);
}

bool SdfValueTypeName::operator==(const TfToken &rhs) const
{
  return IsValueIn(_impl->type->aliases, rhs);
}

size_t SdfValueTypeName::GetHash() const
{
  // See comment in operator==.
  return TfHash::Combine(_impl->type->type, _impl->type->role);
}

bool SdfValueTypeName::_IsEmpty() const
{
  return _impl == Sdf_ValueTypePrivate::GetEmptyTypeName();
}

std::vector<TfToken> SdfValueTypeName::GetAliasesAsTokens() const
{
  return _impl->type->aliases;
}

std::ostream &operator<<(std::ostream &s, const SdfValueTypeName &typeName)
{
  return s << typeName.GetAsToken().GetString();
}

PXR_NAMESPACE_CLOSE_SCOPE
