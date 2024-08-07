//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_SDF_TYPES_H
#define PXR_USD_SDF_TYPES_H

/// \file sdf/types.h
/// Basic Sdf data types

#include "Sdf/api.h"
#include "Sdf/assetPath.h"
#include "Sdf/declareHandles.h"
#include "Sdf/listOp.h"
#include "Sdf/opaqueValue.h"
#include "Sdf/pathExpression.h"
#include "Sdf/timeCode.h"
#include "Sdf/valueTypeName.h"
#include "pxr/pxrns.h"

#include "Arch/demangle.h"
#include "Arch/inttypes.h"
#include "Arch/pragmas.h"
#include "Gf/half.h"
#include "Gf/matrix2d.h"
#include "Gf/matrix3d.h"
#include "Gf/matrix4d.h"
#include "Gf/quatd.h"
#include "Gf/quatf.h"
#include "Gf/quath.h"
#include "Gf/vec2d.h"
#include "Gf/vec2f.h"
#include "Gf/vec2h.h"
#include "Gf/vec2i.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"
#include "Gf/vec3h.h"
#include "Gf/vec3i.h"
#include "Gf/vec4d.h"
#include "Gf/vec4f.h"
#include "Gf/vec4h.h"
#include "Gf/vec4i.h"
#include "Tf/enum.h"
#include "Tf/preprocessorUtilsLite.h"
#include "Tf/staticTokens.h"
#include "Tf/token.h"
#include "Tf/type.h"
#include "Vt/array.h"
#include "Vt/dictionary.h"
#include "Vt/value.h"

#include <Arch/swiftInterop.h>

#include <iosfwd>
#include <list>
#include <map>
#include <stdint.h>
#include <string>
#include <typeinfo>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class SdfPath;

/// An enum that specifies the type of an object. Objects
/// are entities that have fields and are addressable by path.
enum SdfSpecType {
  // The unknown type has a value of 0 so that SdfSpecType() is unknown.
  SdfSpecTypeUnknown = 0,

  // Real concrete types
  SdfSpecTypeAttribute,
  SdfSpecTypeConnection,
  SdfSpecTypeExpression,
  SdfSpecTypeMapper,
  SdfSpecTypeMapperArg,
  SdfSpecTypePrim,
  SdfSpecTypePseudoRoot,
  SdfSpecTypeRelationship,
  SdfSpecTypeRelationshipTarget,
  SdfSpecTypeVariant,
  SdfSpecTypeVariantSet,

  SdfNumSpecTypes
};

/// An enum that identifies the possible specifiers for an
/// SdfPrimSpec. The SdfSpecifier enum is registered as a TfEnum
/// for converting to and from <c>std::string</c>.
///
/// <b>SdfSpecifier:</b>
/// <ul>
/// <li><b>SdfSpecifierDef.</b> Defines a concrete prim.
/// <li><b>SdfSpecifierOver.</b> Overrides an existing prim.
/// <li><b>SdfSpecifierClass.</b> Defines an abstract prim.
/// <li><b>SdfNumSpecifiers.</b> The number of specifiers.
/// </ul>
///
enum SdfSpecifier { SdfSpecifierDef, SdfSpecifierOver, SdfSpecifierClass, SdfNumSpecifiers };

/// Returns true if the specifier defines a prim.
inline bool SdfIsDefiningSpecifier(SdfSpecifier spec)
{
  return (spec != SdfSpecifierOver);
}

/// An enum that defines permission levels.
///
/// Permissions control which layers may refer to or express
/// opinions about a prim.  Opinions expressed about a prim, or
/// relationships to that prim, by layers that are not allowed
/// permission to access the prim will be ignored.
///
/// <b>SdfPermission:</b>
/// <ul>
/// <li><b>SdfPermissionPublic.</b> Public prims can be referred to by
///     anything. (Available to any client.)
/// <li><b>SdfPermissionPrivate.</b> Private prims can be referred to
///     only within the local layer stack, and not across references
///     or inherits. (Not available to clients.)
/// <li><b>SdfNumPermission.</b> Internal sentinel value.
/// </ul>
///
enum SdfPermission {
  SdfPermissionPublic,
  SdfPermissionPrivate,

  SdfNumPermissions
};

/// An enum that identifies variability types for attributes.
/// Variability indicates whether the attribute may vary over time and
/// value coordinates, and if its value comes through authoring or
/// or from its owner.
///
/// <b>SdfVariability:</b>
/// <ul>
///     <li><b>SdfVariabilityVarying.</b> Varying attributes may be directly
///            authored, animated and affected on by Actions.  They are the
///            most flexible.
///     <li><b>SdfVariabilityUniform.</b> Uniform attributes may be authored
///            only with non-animated values (default values).  They cannot
///            be affected by Actions, but they can be connected to other
///            Uniform attributes.
///     <li><b>SdNumVariabilities.</b> Internal sentinel value.
/// </ul>
///
enum SdfVariability {
  SdfVariabilityVarying,
  SdfVariabilityUniform,

  SdfNumVariabilities
};

/// An enum for TfError codes related to authoring operations.
///
/// <b>SdfAuthoringError:</b>
/// <ul>
///     <li><b>SdfAuthoringErrorUnrecognizedFields.</b> This error is raised if
///            SdfLayer::TransferContent, or SdfLayer::SetField API is called
///            for layers of differing schema, and fields from the source layer
///            are not recognized by the target layer's schema.
///     <li><b>SdfAuthoringErrorUnrecognizedSpecType.</b> This error is raised
///            in attempts to create specs on layers with spec types that are
///            not recognized by the layer's schema.
/// </ul>
///
enum SdfAuthoringError {
  SdfAuthoringErrorUnrecognizedFields,
  SdfAuthoringErrorUnrecognizedSpecType
};

// Each category of compatible units of measurement is defined by a
// preprocessor sequence of tuples.  Each such sequence gives rise to an enum
// representing the corresponding unit category.  All the unit categories are
// listed in _SDF_UNITS where each entry is a two-tuple with the unit category
// name as the first element, and the second element is the units in that
// category.  Each tuple in a unit category sequence corresponds to a unit of
// measurement represented by an enumerant whose name is given by concatenating
// 'Sdf', the unit category name, the word 'Unit' and the first entry in the
// tuple.  (E.g. units of category 'Length' are represented by an enum named
// SdfLengthUnit with enumerants SdfLengthUnitInch, SdfLengthUnitMeter and so
// forth.)  The second element in the tuple is the display name for the unit,
// and the third element is the relative size of the unit compared to the menv
// default unit for the unit category (which has a relative size of 1.0).
// Dimensionless quantities use a special 'Dimensionless' unit category
// represented by the enum SdfDimensionlessUnit.
#define _SDF_LENGTH_UNITS \
  ((Millimeter, "mm", 0.001))((Centimeter, "cm", 0.01))((Decimeter, "dm", 0.1))( \
      (Meter, "m", 1.0))((Kilometer, "km", 1000.0))((Inch, "in", 0.0254))((Foot, "ft", 0.3048))( \
      (Yard, "yd", 0.9144))((Mile, "mi", 1609.344))

#define _SDF_ANGULAR_UNITS ((Degrees, "deg", 1.0))((Radians, "rad", 57.2957795130823208768))

#define _SDF_DIMENSIONLESS_UNITS ((Percent, "%", 0.01))((Default, "default", 1.0))

#define _SDF_UNITS \
  ((Length, _SDF_LENGTH_UNITS), \
   (Angular, _SDF_ANGULAR_UNITS), \
   (Dimensionless, _SDF_DIMENSIONLESS_UNITS))

#define _SDF_UNIT_TAG(tup) TF_PP_TUPLE_ELEM(0, tup)
#define _SDF_UNIT_NAME(tup) TF_PP_TUPLE_ELEM(1, tup)
#define _SDF_UNIT_SCALE(tup) TF_PP_TUPLE_ELEM(2, tup)

#define _SDF_UNITSLIST_CATEGORY(tup) TF_PP_TUPLE_ELEM(0, tup)
#define _SDF_UNITSLIST_TUPLES(tup) TF_PP_TUPLE_ELEM(1, tup)
#define _SDF_UNITSLIST_ENUM(elem) TF_PP_CAT(TF_PP_CAT(Sdf, _SDF_UNITSLIST_CATEGORY(elem)), Unit)

#define _SDF_DECLARE_UNIT_ENUMERANT(tag, elem) TF_PP_CAT(Sdf##tag##Unit, _SDF_UNIT_TAG(elem)),

#define _SDF_DECLARE_UNIT_ENUM(elem) \
  enum _SDF_UNITSLIST_ENUM(elem) { \
    TF_PP_SEQ_FOR_EACH( \
        _SDF_DECLARE_UNIT_ENUMERANT, _SDF_UNITSLIST_CATEGORY(elem), _SDF_UNITSLIST_TUPLES(elem)) \
  };

#define _SDF_FOR_EACH_UNITS_IMPL(macro, ...) TF_PP_FOR_EACH(macro, __VA_ARGS__)
#define _SDF_FOR_EACH_UNITS(macro, args) _SDF_FOR_EACH_UNITS_IMPL(macro, TF_PP_EAT_PARENS(args))

// On Windows this call to _SDF_FOR_EACH_UNITS generates a C4003 warning.
// This is harmless, but we disable the warning here so that external
// projects that include this header don't run into it as well.
ARCH_PRAGMA_PUSH
ARCH_PRAGMA_MACRO_TOO_FEW_ARGUMENTS
_SDF_FOR_EACH_UNITS(_SDF_DECLARE_UNIT_ENUM, _SDF_UNITS)
ARCH_PRAGMA_POP

/// A map of mapper parameter names to parameter values.
typedef std::map<std::string, VtValue> SdfMapperParametersMap;

/// A map of reference variant set names to variants in those sets.
typedef std::map<std::string, std::string> SdfVariantSelectionMap;

/// A map of variant set names to list of variants in those sets.
typedef std::map<std::string, std::vector<std::string>> SdfVariantsMap;

/// A map of source SdfPaths to target SdfPaths for relocation.
//  Note: This map needs to be lexicographically sorted for some downstream
//        clients, so SdfPath::FastLessThan is explicitly omitted as
//        the Compare template parameter.
typedef std::map<SdfPath, SdfPath> SdfRelocatesMap;

/// A single relocate specifying a source SdfPath and a target SdfPath for a
/// relocation.
typedef std::pair<SdfPath, SdfPath> SdfRelocate;

/// A vector of relocation source path to target path pairs.
typedef std::vector<SdfRelocate> SdfRelocates;

/// A map from sample times to sample values.
typedef std::map<double, VtValue> SdfTimeSampleMap;

/// Gets the show default unit for the given /a typeName.
SDF_API TfEnum SdfDefaultUnit(TfToken const &typeName);

/// Gets the show default unit for the given /a unit.
SDF_API const TfEnum &SdfDefaultUnit(const TfEnum &unit);

/// Gets the unit category for a given /a unit.
SDF_API const std::string &SdfUnitCategory(const TfEnum &unit);

/// Converts from one unit of measure to another. The \a fromUnit and \a toUnit
/// units must be of the same type (for example, both of type SdfLengthUnit).
SDF_API double SdfConvertUnit(const TfEnum &fromUnit, const TfEnum &toUnit);

/// Gets the name for a given /a unit.
SDF_API const std::string &SdfGetNameForUnit(const TfEnum &unit);

/// Gets a unit for the given /a name
SDF_API const TfEnum &SdfGetUnitFromName(const std::string &name);

/// Given a value, returns if there is a valid corresponding valueType.
SDF_API bool SdfValueHasValidType(VtValue const &value);

/// Given an sdf valueType name, produce TfType if the type name specifies a
/// valid sdf value type.
SDF_API TfType SdfGetTypeForValueTypeName(TfToken const &name);

/// Given a value, produce the sdf valueType name.  If you provide a value that
/// does not return true for SdfValueHasValidType, the return value is
/// unspecified.
SDF_API SdfValueTypeName SdfGetValueTypeNameForValue(VtValue const &value);

/// Return role name for \p typeName.  Return empty token if \p typeName has no
/// associated role name.
SDF_API TfToken SdfGetRoleNameForValueTypeName(TfToken const &typeName);

// Sdf allows a specific set of types for attribute and metadata values.
// These types and some additional metadata are listed in the preprocessor
// sequence of tuples below. First element is a tag name that is appended to
// 'SdfValueType' to produce the C++ traits type for the value type.
// Second element is the value type name, third element is the corresponding
// C++ type, and the fourth element is the tuple of tuple dimensions.
//
// Libraries may extend this list and define additional value types.
// When doing so, the type must be declared using the SDF_DECLARE_VALUE_TYPE
// macro below. The type must also be registered in the associated schema using
// SdfSchema::_RegisterValueType(s).
#define _SDF_SCALAR_VALUE_TYPES \
  ((Bool, bool, bool, ()))((UChar, uchar, unsigned char, ()))((Int, int, int, ()))( \
      (UInt, uint, unsigned int, ()))((Int64, int64, int64_t, ()))( \
      (UInt64, uint64, uint64_t, ()))((Half, half, GfHalf, ()))((Float, float, float, ()))( \
      (Double, double, double, ()))((TimeCode, timecode, SdfTimeCode, ()))( \
      (String, string, std::string, ()))((Token, token, TfToken, ()))( \
      (Asset, asset, SdfAssetPath, ()))((Opaque, opaque, SdfOpaqueValue, ()))( \
      (PathExpression, pathExpression, SdfPathExpression, ()))

#define _SDF_DIMENSIONED_VALUE_TYPES \
  ((Matrix2d, matrix2d, GfMatrix2d, (2, 2)))((Matrix3d, matrix3d, GfMatrix3d, (3, 3)))( \
      (Matrix4d, matrix4d, GfMatrix4d, (4, 4)))((Quath, quath, GfQuath, (4)))( \
      (Quatf, quatf, GfQuatf, (4)))((Quatd, quatd, GfQuatd, (4)))((Int2, int2, GfVec2i, (2)))( \
      (Half2, half2, GfVec2h, (2)))((Float2, float2, GfVec2f, (2)))(( \
      Double2, double2, GfVec2d, (2)))((Int3, int3, GfVec3i, (3)))((Half3, half3, GfVec3h, (3)))( \
      (Float3, float3, GfVec3f, (3)))((Double3, double3, GfVec3d, (3)))( \
      (Int4, int4, GfVec4i, (4)))((Half4, half4, GfVec4h, (4)))((Float4, float4, GfVec4f, (4)))( \
      (Double4, double4, GfVec4d, (4)))

#define SDF_VALUE_TYPES _SDF_SCALAR_VALUE_TYPES _SDF_DIMENSIONED_VALUE_TYPES

// Accessors for individual elements in the value types tuples.
#define SDF_VALUE_CPP_TYPE(tup) TF_PP_TUPLE_ELEM(2, tup)
#define SDF_VALUE_CPP_ARRAY_TYPE(tup) VtArray<TF_PP_TUPLE_ELEM(2, tup)>

template<class T> struct SdfValueTypeTraits {
  static const bool IsValueType = false;
};

// Allow character arrays to be treated as Sdf value types.
// Sdf converts character arrays to strings for scene description.
template<int N> struct SdfValueTypeTraits<char[N]> {
  static const bool IsValueType = true;
};

#define SDF_DECLARE_VALUE_TYPE_TRAITS(unused, elem) \
  template<> struct SdfValueTypeTraits<SDF_VALUE_CPP_TYPE(elem)> { \
    static const bool IsValueType = true; \
  }; \
  template<> struct SdfValueTypeTraits<SDF_VALUE_CPP_ARRAY_TYPE(elem)> { \
    static const bool IsValueType = true; \
  };

TF_PP_SEQ_FOR_EACH(SDF_DECLARE_VALUE_TYPE_TRAITS, ~, SDF_VALUE_TYPES);

/// Convert \p dict to a valid metadata dictionary for scene description.  Valid
/// metadata dictionaries have values that are any of SDF_VALUE_TYPES (or
/// VtArrays of those), plus VtDictionary with values of those types (or
/// similarly nested VtDictionaries).
///
/// Certain conversions are performed in an attempt to produce a valid metadata
/// dictionary.  For example:
///
/// Convert std::vector<VtValue> to VtArray<T> where T is the type of the first
/// element in the vector.  Fail conversion for empty vectors where a concrete
/// type cannot be inferred.
///
/// Convert python sequences to VtArray<T> where T is the type of the first
/// element in the python sequence, when converted to VtValue, if that T is an
/// SDF_VALUE_TYPE).  Fail conversion for empty sequences where a concrete type
/// cannot be inferred.
///
/// If any values cannot be converted to valid SDF_VALUE_TYPES, omit those
/// elements and add a message to \p errMsg indicating which values were
/// omitted.
///
SDF_API
bool SdfConvertToValidMetadataDictionary(VtDictionary *dict, std::string *errMsg);

#define SDF_VALUE_ROLE_NAME_TOKENS \
  (Point)(Normal)( \
      Vector)(Color)(Frame)(Transform)(PointIndex)(EdgeIndex)(FaceIndex)(Group)(TextureCoordinate)

TF_DECLARE_PUBLIC_TOKENS(SdfValueRoleNames, SDF_API, SDF_VALUE_ROLE_NAME_TOKENS);

SDF_DECLARE_HANDLES(SdfLayer);

SDF_DECLARE_HANDLES(SdfAttributeSpec);
SDF_DECLARE_HANDLES(SdfPrimSpec);
SDF_DECLARE_HANDLES(SdfPropertySpec);
SDF_DECLARE_HANDLES(SdfSpec);
SDF_DECLARE_HANDLES(SdfRelationshipSpec);
SDF_DECLARE_HANDLES(SdfVariantSetSpec);
SDF_DECLARE_HANDLES(SdfVariantSpec);

typedef std::map<std::string, SdfVariantSetSpecHandle> SdfVariantSetSpecHandleMap;

/// Writes the string representation of \c SdfSpecifier to \a out.
SDF_API
std::ostream &operator<<(std::ostream &out, const SdfSpecifier &spec);

/// Writes the string representation of \c SdfRelocatesMap to \a out.
SDF_API
std::ostream &operator<<(std::ostream &out, const SdfRelocatesMap &reloMap);

/// Writes the string representation of \c SdfRelocates to \a out.
SDF_API
std::ostream &operator<<(std::ostream &out, const SdfRelocates &relocates);

/// Writes the string representation of \c SdfTimeSampleMap to \a out.
SDF_API
std::ostream &operator<<(std::ostream &out, const SdfTimeSampleMap &sampleMap);

SDF_API
std::ostream &VtStreamOut(const SdfVariantSelectionMap &, std::ostream &);

/// \class SdfUnregisteredValue
/// Stores a representation of the value for an unregistered metadata
/// field encountered during text layer parsing.
///
/// This provides the ability to serialize this data to a layer, as
/// well as limited inspection and editing capabilities (e.g., moving
/// this data to a different spec or field) even when the data type
/// of the value isn't known.
class SdfUnregisteredValue {
 public:
  /// Wraps an empty VtValue
  SDF_API SdfUnregisteredValue();

  /// Wraps a std::string
  SDF_API explicit SdfUnregisteredValue(const std::string &value);

  /// Wraps a VtDictionary
  SDF_API explicit SdfUnregisteredValue(const VtDictionary &value);

  /// Wraps a SdfUnregisteredValueListOp
  SDF_API explicit SdfUnregisteredValue(const SdfUnregisteredValueListOp &value);

  /// Returns the wrapped VtValue specified in the constructor
  const VtValue &GetValue() const
  {
    return _value;
  }

  /// Hash.
  friend size_t hash_value(const SdfUnregisteredValue &uv)
  {
    return uv._value.GetHash();
  }

  /// Returns true if the wrapped VtValues are equal
  SDF_API bool operator==(const SdfUnregisteredValue &other) const;

  /// Returns true if the wrapped VtValues are not equal
  SDF_API bool operator!=(const SdfUnregisteredValue &other) const;

 private:
  VtValue _value;
};

/// Writes the string representation of \c SdfUnregisteredValue to \a out.
SDF_API std::ostream &operator<<(std::ostream &out, const SdfUnregisteredValue &value);

class Sdf_ValueTypeNamesType {
  Sdf_ValueTypeNamesType(const Sdf_ValueTypeNamesType &) = delete;
  Sdf_ValueTypeNamesType &operator=(const Sdf_ValueTypeNamesType &) = delete;

 public:
  SdfValueTypeName Bool;
  SdfValueTypeName UChar, Int, UInt, Int64, UInt64;
  SdfValueTypeName Half, Float, Double, TimeCode;
  SdfValueTypeName String, Token, Asset;
  SdfValueTypeName Int2, Int3, Int4;
  SdfValueTypeName Half2, Half3, Half4;
  SdfValueTypeName Float2, Float3, Float4;
  SdfValueTypeName Double2, Double3, Double4;
  SdfValueTypeName Point3h, Point3f, Point3d;
  SdfValueTypeName Vector3h, Vector3f, Vector3d;
  SdfValueTypeName Normal3h, Normal3f, Normal3d;
  SdfValueTypeName Color3h, Color3f, Color3d;
  SdfValueTypeName Color4h, Color4f, Color4d;
  SdfValueTypeName Quath, Quatf, Quatd;
  SdfValueTypeName Matrix2d, Matrix3d, Matrix4d;
  SdfValueTypeName Frame4d;
  SdfValueTypeName TexCoord2h, TexCoord2f, TexCoord2d;
  SdfValueTypeName TexCoord3h, TexCoord3f, TexCoord3d;
  SdfValueTypeName Opaque;
  SdfValueTypeName Group;
  SdfValueTypeName PathExpression;

  SdfValueTypeName BoolArray;
  SdfValueTypeName UCharArray, IntArray, UIntArray, Int64Array, UInt64Array;
  SdfValueTypeName HalfArray, FloatArray, DoubleArray, TimeCodeArray;
  SdfValueTypeName StringArray, TokenArray, AssetArray;
  SdfValueTypeName Int2Array, Int3Array, Int4Array;
  SdfValueTypeName Half2Array, Half3Array, Half4Array;
  SdfValueTypeName Float2Array, Float3Array, Float4Array;
  SdfValueTypeName Double2Array, Double3Array, Double4Array;
  SdfValueTypeName Point3hArray, Point3fArray, Point3dArray;
  SdfValueTypeName Vector3hArray, Vector3fArray, Vector3dArray;
  SdfValueTypeName Normal3hArray, Normal3fArray, Normal3dArray;
  SdfValueTypeName Color3hArray, Color3fArray, Color3dArray;
  SdfValueTypeName Color4hArray, Color4fArray, Color4dArray;
  SdfValueTypeName QuathArray, QuatfArray, QuatdArray;
  SdfValueTypeName Matrix2dArray, Matrix3dArray, Matrix4dArray;
  SdfValueTypeName Frame4dArray;
  SdfValueTypeName TexCoord2hArray, TexCoord2fArray, TexCoord2dArray;
  SdfValueTypeName TexCoord3hArray, TexCoord3fArray, TexCoord3dArray;
  SdfValueTypeName PathExpressionArray;

  SDF_API ~Sdf_ValueTypeNamesType();
  struct _Init {
    SDF_API static const Sdf_ValueTypeNamesType *New();
  };

  // For Pixar internal backwards compatibility.
  TfToken GetSerializationName(const SdfValueTypeName &) const;
  TfToken GetSerializationName(const VtValue &) const;
  TfToken GetSerializationName(const TfToken &) const;

 private:
  friend const Sdf_ValueTypeNamesType *Sdf_InitializeValueTypeNames();
  Sdf_ValueTypeNamesType();
} SWIFT_IMMORTAL_REFERENCE;

extern SDF_API TfStaticData<const Sdf_ValueTypeNamesType, Sdf_ValueTypeNamesType::_Init>
    SdfValueTypeNames;

/**
 * Ugly monstrosity to allow us to look
 * up a SdfValueTypeName from a Swift enum.
 *
 * Swift magically turns enum values such as
 * "SdfValueTypeNameTypeFloat" to simply "float".
 */
enum class SdfValueTypeNameType {
  SdfValueTypeNameTypeBool,
  SdfValueTypeNameTypeUChar,
  SdfValueTypeNameTypeInt,
  SdfValueTypeNameTypeUInt,
  SdfValueTypeNameTypeInt64,
  SdfValueTypeNameTypeUInt64,
  SdfValueTypeNameTypeHalf,
  SdfValueTypeNameTypeFloat,
  SdfValueTypeNameTypeDouble,
  SdfValueTypeNameTypeTimeCode,
  SdfValueTypeNameTypeString,
  SdfValueTypeNameTypeToken,
  SdfValueTypeNameTypeAsset,
  SdfValueTypeNameTypeInt2,
  SdfValueTypeNameTypeInt3,
  SdfValueTypeNameTypeInt4,
  SdfValueTypeNameTypeHalf2,
  SdfValueTypeNameTypeHalf3,
  SdfValueTypeNameTypeHalf4,
  SdfValueTypeNameTypeFloat2,
  SdfValueTypeNameTypeFloat3,
  SdfValueTypeNameTypeFloat4,
  SdfValueTypeNameTypeDouble2,
  SdfValueTypeNameTypeDouble3,
  SdfValueTypeNameTypeDouble4,
  SdfValueTypeNameTypePoint3h,
  SdfValueTypeNameTypePoint3f,
  SdfValueTypeNameTypePoint3d,
  SdfValueTypeNameTypeVector3h,
  SdfValueTypeNameTypeVector3f,
  SdfValueTypeNameTypeVector3d,
  SdfValueTypeNameTypeNormal3h,
  SdfValueTypeNameTypeNormal3f,
  SdfValueTypeNameTypeNormal3d,
  SdfValueTypeNameTypeColor3h,
  SdfValueTypeNameTypeColor3f,
  SdfValueTypeNameTypeColor3d,
  SdfValueTypeNameTypeColor4h,
  SdfValueTypeNameTypeColor4f,
  SdfValueTypeNameTypeColor4d,
  SdfValueTypeNameTypeQuath,
  SdfValueTypeNameTypeQuatf,
  SdfValueTypeNameTypeQuatd,
  SdfValueTypeNameTypeMatrix2d,
  SdfValueTypeNameTypeMatrix3d,
  SdfValueTypeNameTypeMatrix4d,
  SdfValueTypeNameTypeFrame4d,
  SdfValueTypeNameTypeTexCoord2h,
  SdfValueTypeNameTypeTexCoord2f,
  SdfValueTypeNameTypeTexCoord2d,
  SdfValueTypeNameTypeTexCoord3h,
  SdfValueTypeNameTypeTexCoord3f,
  SdfValueTypeNameTypeTexCoord3d,
  SdfValueTypeNameTypeOpaque,
  SdfValueTypeNameTypeGroup,
  SdfValueTypeNameTypePathExpression,
  SdfValueTypeNameTypeBoolArray,
  SdfValueTypeNameTypeUCharArray,
  SdfValueTypeNameTypeIntArray,
  SdfValueTypeNameTypeUIntArray,
  SdfValueTypeNameTypeInt64Array,
  SdfValueTypeNameTypeUInt64Array,
  SdfValueTypeNameTypeHalfArray,
  SdfValueTypeNameTypeFloatArray,
  SdfValueTypeNameTypeDoubleArray,
  SdfValueTypeNameTypeTimeCodeArray,
  SdfValueTypeNameTypeStringArray,
  SdfValueTypeNameTypeTokenArray,
  SdfValueTypeNameTypeAssetArray,
  SdfValueTypeNameTypeInt2Array,
  SdfValueTypeNameTypeInt3Array,
  SdfValueTypeNameTypeInt4Array,
  SdfValueTypeNameTypeHalf2Array,
  SdfValueTypeNameTypeHalf3Array,
  SdfValueTypeNameTypeHalf4Array,
  SdfValueTypeNameTypeFloat2Array,
  SdfValueTypeNameTypeFloat3Array,
  SdfValueTypeNameTypeFloat4Array,
  SdfValueTypeNameTypeDouble2Array,
  SdfValueTypeNameTypeDouble3Array,
  SdfValueTypeNameTypeDouble4Array,
  SdfValueTypeNameTypePoint3hArray,
  SdfValueTypeNameTypePoint3fArray,
  SdfValueTypeNameTypePoint3dArray,
  SdfValueTypeNameTypeVector3hArray,
  SdfValueTypeNameTypeVector3fArray,
  SdfValueTypeNameTypeVector3dArray,
  SdfValueTypeNameTypeNormal3hArray,
  SdfValueTypeNameTypeNormal3fArray,
  SdfValueTypeNameTypeNormal3dArray,
  SdfValueTypeNameTypeColor3hArray,
  SdfValueTypeNameTypeColor3fArray,
  SdfValueTypeNameTypeColor3dArray,
  SdfValueTypeNameTypeColor4hArray,
  SdfValueTypeNameTypeColor4fArray,
  SdfValueTypeNameTypeColor4dArray,
  SdfValueTypeNameTypeQuathArray,
  SdfValueTypeNameTypeQuatfArray,
  SdfValueTypeNameTypeQuatdArray,
  SdfValueTypeNameTypeMatrix2dArray,
  SdfValueTypeNameTypeMatrix3dArray,
  SdfValueTypeNameTypeMatrix4dArray,
  SdfValueTypeNameTypeFrame4dArray,
  SdfValueTypeNameTypeTexCoord2hArray,
  SdfValueTypeNameTypeTexCoord2fArray,
  SdfValueTypeNameTypeTexCoord2dArray,
  SdfValueTypeNameTypeTexCoord3hArray,
  SdfValueTypeNameTypeTexCoord3fArray,
  SdfValueTypeNameTypeTexCoord3dArray,
  SdfValueTypeNameTypePathExpressionArray,
};

/**
 * Ugly monstrosity to allow us to look up a SdfValueTypeName from Swift using a
 * SdfValueTypeNameType enum, all of this because Swift hates the -> operator pointer
 * lookup on SdfValueTypeNames.
 */
inline SdfValueTypeName SdfGetValueType(const SdfValueTypeNameType &type)
{
  switch (type) {
    case SdfValueTypeNameType::SdfValueTypeNameTypeBool:
      return SdfValueTypeNames->Bool;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUChar:
      return SdfValueTypeNames->UChar;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt:
      return SdfValueTypeNames->Int;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUInt:
      return SdfValueTypeNames->UInt;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt64:
      return SdfValueTypeNames->Int64;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUInt64:
      return SdfValueTypeNames->UInt64;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf:
      return SdfValueTypeNames->Half;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat:
      return SdfValueTypeNames->Float;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble:
      return SdfValueTypeNames->Double;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTimeCode:
      return SdfValueTypeNames->TimeCode;
    case SdfValueTypeNameType::SdfValueTypeNameTypeString:
      return SdfValueTypeNames->String;
    case SdfValueTypeNameType::SdfValueTypeNameTypeToken:
      return SdfValueTypeNames->Token;
    case SdfValueTypeNameType::SdfValueTypeNameTypeAsset:
      return SdfValueTypeNames->Asset;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt2:
      return SdfValueTypeNames->Int2;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt3:
      return SdfValueTypeNames->Int3;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt4:
      return SdfValueTypeNames->Int4;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf2:
      return SdfValueTypeNames->Half2;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf3:
      return SdfValueTypeNames->Half3;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf4:
      return SdfValueTypeNames->Half4;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat2:
      return SdfValueTypeNames->Float2;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat3:
      return SdfValueTypeNames->Float3;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat4:
      return SdfValueTypeNames->Float4;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble2:
      return SdfValueTypeNames->Double2;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble3:
      return SdfValueTypeNames->Double3;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble4:
      return SdfValueTypeNames->Double4;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3h:
      return SdfValueTypeNames->Point3h;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3f:
      return SdfValueTypeNames->Point3f;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3d:
      return SdfValueTypeNames->Point3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3h:
      return SdfValueTypeNames->Vector3h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3f:
      return SdfValueTypeNames->Vector3f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3d:
      return SdfValueTypeNames->Vector3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3h:
      return SdfValueTypeNames->Normal3h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3f:
      return SdfValueTypeNames->Normal3f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3d:
      return SdfValueTypeNames->Normal3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3h:
      return SdfValueTypeNames->Color3h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3f:
      return SdfValueTypeNames->Color3f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3d:
      return SdfValueTypeNames->Color3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4h:
      return SdfValueTypeNames->Color4h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4f:
      return SdfValueTypeNames->Color4f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4d:
      return SdfValueTypeNames->Color4d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuath:
      return SdfValueTypeNames->Quath;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuatf:
      return SdfValueTypeNames->Quatf;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuatd:
      return SdfValueTypeNames->Quatd;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix2d:
      return SdfValueTypeNames->Matrix2d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix3d:
      return SdfValueTypeNames->Matrix3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix4d:
      return SdfValueTypeNames->Matrix4d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFrame4d:
      return SdfValueTypeNames->Frame4d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2h:
      return SdfValueTypeNames->TexCoord2h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2f:
      return SdfValueTypeNames->TexCoord2f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2d:
      return SdfValueTypeNames->TexCoord2d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3h:
      return SdfValueTypeNames->TexCoord3h;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3f:
      return SdfValueTypeNames->TexCoord3f;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3d:
      return SdfValueTypeNames->TexCoord3d;
    case SdfValueTypeNameType::SdfValueTypeNameTypeOpaque:
      return SdfValueTypeNames->Opaque;
    case SdfValueTypeNameType::SdfValueTypeNameTypeGroup:
      return SdfValueTypeNames->Group;
    case SdfValueTypeNameType::SdfValueTypeNameTypePathExpression:
      return SdfValueTypeNames->PathExpression;
    case SdfValueTypeNameType::SdfValueTypeNameTypeBoolArray:
      return SdfValueTypeNames->BoolArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUCharArray:
      return SdfValueTypeNames->UCharArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeIntArray:
      return SdfValueTypeNames->IntArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUIntArray:
      return SdfValueTypeNames->UIntArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt64Array:
      return SdfValueTypeNames->Int64Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeUInt64Array:
      return SdfValueTypeNames->UInt64Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalfArray:
      return SdfValueTypeNames->HalfArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloatArray:
      return SdfValueTypeNames->FloatArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDoubleArray:
      return SdfValueTypeNames->DoubleArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTimeCodeArray:
      return SdfValueTypeNames->TimeCodeArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeStringArray:
      return SdfValueTypeNames->StringArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTokenArray:
      return SdfValueTypeNames->TokenArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeAssetArray:
      return SdfValueTypeNames->AssetArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt2Array:
      return SdfValueTypeNames->Int2Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt3Array:
      return SdfValueTypeNames->Int3Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeInt4Array:
      return SdfValueTypeNames->Int4Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf2Array:
      return SdfValueTypeNames->Half2Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf3Array:
      return SdfValueTypeNames->Half3Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeHalf4Array:
      return SdfValueTypeNames->Half4Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat2Array:
      return SdfValueTypeNames->Float2Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat3Array:
      return SdfValueTypeNames->Float3Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFloat4Array:
      return SdfValueTypeNames->Float4Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble2Array:
      return SdfValueTypeNames->Double2Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble3Array:
      return SdfValueTypeNames->Double3Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypeDouble4Array:
      return SdfValueTypeNames->Double4Array;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3hArray:
      return SdfValueTypeNames->Point3hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3fArray:
      return SdfValueTypeNames->Point3fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypePoint3dArray:
      return SdfValueTypeNames->Point3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3hArray:
      return SdfValueTypeNames->Vector3hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3fArray:
      return SdfValueTypeNames->Vector3fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeVector3dArray:
      return SdfValueTypeNames->Vector3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3hArray:
      return SdfValueTypeNames->Normal3hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3fArray:
      return SdfValueTypeNames->Normal3fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeNormal3dArray:
      return SdfValueTypeNames->Normal3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3hArray:
      return SdfValueTypeNames->Color3hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3fArray:
      return SdfValueTypeNames->Color3fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor3dArray:
      return SdfValueTypeNames->Color3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4hArray:
      return SdfValueTypeNames->Color4hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4fArray:
      return SdfValueTypeNames->Color4fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeColor4dArray:
      return SdfValueTypeNames->Color4dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuathArray:
      return SdfValueTypeNames->QuathArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuatfArray:
      return SdfValueTypeNames->QuatfArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeQuatdArray:
      return SdfValueTypeNames->QuatdArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix2dArray:
      return SdfValueTypeNames->Matrix2dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix3dArray:
      return SdfValueTypeNames->Matrix3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeMatrix4dArray:
      return SdfValueTypeNames->Matrix4dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeFrame4dArray:
      return SdfValueTypeNames->Frame4dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2hArray:
      return SdfValueTypeNames->TexCoord2hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2fArray:
      return SdfValueTypeNames->TexCoord2fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord2dArray:
      return SdfValueTypeNames->TexCoord2dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3hArray:
      return SdfValueTypeNames->TexCoord3hArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3fArray:
      return SdfValueTypeNames->TexCoord3fArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypeTexCoord3dArray:
      return SdfValueTypeNames->TexCoord3dArray;
    case SdfValueTypeNameType::SdfValueTypeNameTypePathExpressionArray:
      return SdfValueTypeNames->PathExpressionArray;
    default:
      return SdfValueTypeNames->String;
  }
}

/// \class SdfValueBlock
/// A special value type that can be used to explicitly author an
/// opinion for an attribute's default value or time sample value
/// that represents having no value. Note that this is different
/// from not having a value authored.
///
/// One could author such a value in two ways.
///
/// \code
/// attribute->SetDefaultValue(VtValue(SdfValueBlock());
/// ...
/// layer->SetTimeSample(attribute->GetPath(), 101, VtValue(SdfValueBlock()));
/// \endcode
///
struct SdfValueBlock {
  bool operator==(const SdfValueBlock &block) const
  {
    return true;
  }
  bool operator!=(const SdfValueBlock &block) const
  {
    return false;
  }

 private:
  friend inline size_t hash_value(const SdfValueBlock &block)
  {
    return 0;
  }
};

// Write out the string representation of a block.
SDF_API std::ostream &operator<<(std::ostream &, SdfValueBlock const &);

// A class that represents a human-readable value.  This is used for the special
// purpose of producing layers that serialize field values in alternate ways; to
// produce more human-readable output, for example.
struct SdfHumanReadableValue {
  SdfHumanReadableValue() = default;
  explicit SdfHumanReadableValue(std::string const &text) : _text(text) {}

  bool operator==(SdfHumanReadableValue const &other) const
  {
    return GetText() == other.GetText();
  }
  bool operator!=(SdfHumanReadableValue const &other) const
  {
    return !(*this == other);
  }

  std::string const &GetText() const
  {
    return _text;
  }

 private:
  std::string _text;
};

SDF_API
std::ostream &operator<<(std::ostream &out, const SdfHumanReadableValue &hrval);

SDF_API
size_t hash_value(const SdfHumanReadableValue &hrval);

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_SDF_TYPES_H
