//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Sdf/valueTypeName.h"
#include "Sdf/valueTypePrivate.h"

#include "Sdf/abstractData.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

namespace {

template <typename C, typename V>
bool
IsValueIn(const C& container, V value)
{
    for (const auto& element : container) {
        if (element == value) {
            return true;
        }
    }
    return false;
}

} // anonymous namespace


//
// SdfTupleDimensions
//

bool
SdfTupleDimensions::operator==(const SdfTupleDimensions& rhs) const
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

SdfValueTypeName::SdfValueTypeName() :
    _impl(Sdf_ValueTypePrivate::GetEmptyTypeName())
{
    // Do nothing
}

SdfValueTypeName::SdfValueTypeName(const Sdf_ValueTypeImpl* impl) : _impl(impl)
{
    // Do nothing
}

TfToken
SdfValueTypeName::GetAsToken() const
{
    return _impl->name;
}

const TfType&
SdfValueTypeName::GetType() const
{
    return _impl->type->type;
}

bool
SdfValueTypeName::CanRepresent(VtValue const &val) const
{
    if (GetType() == val.GetType()) {
        return true;
    }
    return IsArray() && val.IsArrayEditValued() &&
        TfSafeTypeCompare(GetDefaultValue()
                          .GetElementTypeid(), val.GetElementTypeid());
}

bool
SdfValueTypeName::CanRepresent(SdfAbstractDataConstValue const &val) const
{
    if (TfSafeTypeCompare(GetType().GetTypeid(), val.valueType)) {
        return true;
    }
    return IsArray() && val.isArrayEdit &&
        TfSafeTypeCompare(GetDefaultValue()
                          .GetElementTypeid(), val.elementValueType);
}

const std::string& 
SdfValueTypeName::GetCPPTypeName() const
{
    return _impl->type->cppTypeName;
}

const TfToken&
SdfValueTypeName::GetRole() const
{
    return _impl->type->role;
}

const VtValue&
SdfValueTypeName::GetDefaultValue() const
{
    return _impl->type->value;
}

const TfEnum&
SdfValueTypeName::GetDefaultUnit() const
{
    return _impl->type->unit;
}

SdfValueTypeName
SdfValueTypeName::GetScalarType() const
{
    return SdfValueTypeName(_impl->scalar);
}

SdfValueTypeName
SdfValueTypeName::GetArrayType() const
{
    return SdfValueTypeName(_impl->array);
}

bool
SdfValueTypeName::IsScalar() const
{
    return *this && _impl == _impl->scalar;
}

bool
SdfValueTypeName::IsArray() const
{
    return *this && _impl == _impl->array;
}

SdfTupleDimensions
SdfValueTypeName::GetDimensions() const
{
    return _impl->type->dim;
}

bool
SdfValueTypeName::operator==(const SdfValueTypeName& rhs) const
{
    // Do equality comparisons on core type to ensure that
    // equivalent type names from different registries compare
    // equal. The registry ensures that type and role are
    // the only things we need to look at here.
    return (_impl->type->type == rhs._impl->type->type && 
            _impl->type->role == rhs._impl->type->role);
}

bool
SdfValueTypeName::operator==(const std::string& rhs) const
{
    return IsValueIn(_impl->type->aliases, rhs);
}

bool
SdfValueTypeName::operator==(const TfToken& rhs) const
{
    return IsValueIn(_impl->type->aliases, rhs);
}

size_t
SdfValueTypeName::GetHash() const
{
    // See comment in operator==.
    return TfHash::Combine(
        _impl->type->type,
        _impl->type->role
    );
}

bool
SdfValueTypeName::_IsEmpty() const
{
    return _impl == Sdf_ValueTypePrivate::GetEmptyTypeName();
}

std::vector<TfToken>
SdfValueTypeName::GetAliasesAsTokens() const
{
    return _impl->type->aliases;
}

std::ostream&
operator<<(std::ostream& s, const SdfValueTypeName& typeName)
{
    return s << typeName.GetAsToken().GetString();
}

const SdfValueTypeName&
SdfGetValueTypeName(SdfValueTypeNameType type)
{
    switch (type) {
        case SdfValueTypeNameType::SdfValueTypeNameTypeBool:             return SdfValueTypeNames->Bool;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUChar:            return SdfValueTypeNames->UChar;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt:              return SdfValueTypeNames->Int;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUInt:             return SdfValueTypeNames->UInt;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt64:            return SdfValueTypeNames->Int64;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUInt64:           return SdfValueTypeNames->UInt64;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf:             return SdfValueTypeNames->Half;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat:            return SdfValueTypeNames->Float;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble:           return SdfValueTypeNames->Double;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTimeCode:         return SdfValueTypeNames->TimeCode;
        case SdfValueTypeNameType::SdfValueTypeNameTypeString:           return SdfValueTypeNames->String;
        case SdfValueTypeNameType::SdfValueTypeNameTypeToken:            return SdfValueTypeNames->Token;
        case SdfValueTypeNameType::SdfValueTypeNameTypeAsset:            return SdfValueTypeNames->Asset;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt2:             return SdfValueTypeNames->Int2;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt3:             return SdfValueTypeNames->Int3;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt4:             return SdfValueTypeNames->Int4;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf2:            return SdfValueTypeNames->Half2;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf3:            return SdfValueTypeNames->Half3;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf4:            return SdfValueTypeNames->Half4;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat2:           return SdfValueTypeNames->Float2;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat3:           return SdfValueTypeNames->Float3;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat4:           return SdfValueTypeNames->Float4;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble2:          return SdfValueTypeNames->Double2;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble3:          return SdfValueTypeNames->Double3;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble4:          return SdfValueTypeNames->Double4;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3h:          return SdfValueTypeNames->Point3h;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3f:          return SdfValueTypeNames->Point3f;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3d:          return SdfValueTypeNames->Point3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3h:         return SdfValueTypeNames->Vector3h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3f:         return SdfValueTypeNames->Vector3f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3d:         return SdfValueTypeNames->Vector3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3h:         return SdfValueTypeNames->Normal3h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3f:         return SdfValueTypeNames->Normal3f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3d:         return SdfValueTypeNames->Normal3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3h:          return SdfValueTypeNames->Color3h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3f:          return SdfValueTypeNames->Color3f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3d:          return SdfValueTypeNames->Color3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4h:          return SdfValueTypeNames->Color4h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4f:          return SdfValueTypeNames->Color4f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4d:          return SdfValueTypeNames->Color4d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuath:            return SdfValueTypeNames->Quath;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuatf:            return SdfValueTypeNames->Quatf;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuatd:            return SdfValueTypeNames->Quatd;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix2d:         return SdfValueTypeNames->Matrix2d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix3d:         return SdfValueTypeNames->Matrix3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix4d:         return SdfValueTypeNames->Matrix4d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFrame4d:          return SdfValueTypeNames->Frame4d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2h:       return SdfValueTypeNames->TexCoord2h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2f:       return SdfValueTypeNames->TexCoord2f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2d:       return SdfValueTypeNames->TexCoord2d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3h:       return SdfValueTypeNames->TexCoord3h;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3f:       return SdfValueTypeNames->TexCoord3f;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3d:       return SdfValueTypeNames->TexCoord3d;
        case SdfValueTypeNameType::SdfValueTypeNameTypeOpaque:           return SdfValueTypeNames->Opaque;
        case SdfValueTypeNameType::SdfValueTypeNameTypeGroup:            return SdfValueTypeNames->Group;
        case SdfValueTypeNameType::SdfValueTypeNameTypePathExpression:   return SdfValueTypeNames->PathExpression;
        case SdfValueTypeNameType::SdfValueTypeNameTypeBoolArray:        return SdfValueTypeNames->BoolArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUCharArray:       return SdfValueTypeNames->UCharArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeIntArray:         return SdfValueTypeNames->IntArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUIntArray:        return SdfValueTypeNames->UIntArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt64Array:       return SdfValueTypeNames->Int64Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeUInt64Array:      return SdfValueTypeNames->UInt64Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalfArray:        return SdfValueTypeNames->HalfArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloatArray:       return SdfValueTypeNames->FloatArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDoubleArray:      return SdfValueTypeNames->DoubleArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTimeCodeArray:    return SdfValueTypeNames->TimeCodeArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeStringArray:      return SdfValueTypeNames->StringArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTokenArray:       return SdfValueTypeNames->TokenArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeAssetArray:       return SdfValueTypeNames->AssetArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt2Array:        return SdfValueTypeNames->Int2Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt3Array:        return SdfValueTypeNames->Int3Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeInt4Array:        return SdfValueTypeNames->Int4Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf2Array:       return SdfValueTypeNames->Half2Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf3Array:       return SdfValueTypeNames->Half3Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeHalf4Array:       return SdfValueTypeNames->Half4Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat2Array:      return SdfValueTypeNames->Float2Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat3Array:      return SdfValueTypeNames->Float3Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFloat4Array:      return SdfValueTypeNames->Float4Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble2Array:     return SdfValueTypeNames->Double2Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble3Array:     return SdfValueTypeNames->Double3Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypeDouble4Array:     return SdfValueTypeNames->Double4Array;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3hArray:     return SdfValueTypeNames->Point3hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3fArray:     return SdfValueTypeNames->Point3fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypePoint3dArray:     return SdfValueTypeNames->Point3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3hArray:    return SdfValueTypeNames->Vector3hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3fArray:    return SdfValueTypeNames->Vector3fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeVector3dArray:    return SdfValueTypeNames->Vector3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3hArray:    return SdfValueTypeNames->Normal3hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3fArray:    return SdfValueTypeNames->Normal3fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3dArray:    return SdfValueTypeNames->Normal3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3hArray:     return SdfValueTypeNames->Color3hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3fArray:     return SdfValueTypeNames->Color3fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor3dArray:     return SdfValueTypeNames->Color3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4hArray:     return SdfValueTypeNames->Color4hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4fArray:     return SdfValueTypeNames->Color4fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeColor4dArray:     return SdfValueTypeNames->Color4dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuathArray:       return SdfValueTypeNames->QuathArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuatfArray:       return SdfValueTypeNames->QuatfArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeQuatdArray:       return SdfValueTypeNames->QuatdArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix2dArray:    return SdfValueTypeNames->Matrix2dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix3dArray:    return SdfValueTypeNames->Matrix3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix4dArray:    return SdfValueTypeNames->Matrix4dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeFrame4dArray:     return SdfValueTypeNames->Frame4dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2hArray:  return SdfValueTypeNames->TexCoord2hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2fArray:  return SdfValueTypeNames->TexCoord2fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2dArray:  return SdfValueTypeNames->TexCoord2dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3hArray:  return SdfValueTypeNames->TexCoord3hArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3fArray:  return SdfValueTypeNames->TexCoord3fArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3dArray:  return SdfValueTypeNames->TexCoord3dArray;
        case SdfValueTypeNameType::SdfValueTypeNameTypePathExpressionArray: return SdfValueTypeNames->PathExpressionArray;
    }
}

PXR_NAMESPACE_CLOSE_SCOPE
