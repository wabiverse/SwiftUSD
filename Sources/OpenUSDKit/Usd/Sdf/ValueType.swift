/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                                        Copyright (C) 2016 Pixar.
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

#if canImport(Sdf)
  import Sdf
#else
  import OpenUSD
#endif

public typealias SdfValueTypeNameType = Pixar.SdfValueTypeNameType
public typealias SdfValueTypeName = Pixar.SdfValueTypeName

public extension Sdf
{
  typealias ValueTypeNameType = SdfValueTypeNameType
  typealias ValueTypeName = SdfValueTypeName
}

public extension Sdf
{
  static func getValueType(for type: SdfValueTypeNameType) -> Sdf.ValueTypeName
  {
    Overlay.SdfGetValueTypeNameValue(type)
  }
}

#if !canImport(Sdf)
public extension Pixar
{
  enum SdfValueTypeNameType
  {
    case bool, uChar, int, uInt, int64, uInt64
    case half, float, double, timeCode
    case string, token, asset
    case int2, int3, int4
    case half2, half3, half4
    case float2, float3, float4
    case double2, double3, double4
    case point3h, point3f, point3d
    case vector3h, vector3f, vector3d
    case normal3h, normal3f, normal3d
    case color3h, color3f, color3d
    case color4h, color4f, color4d
    case quath, quatf, quatd
    case matrix2d, matrix3d, matrix4d
    case frame4d
    case texCoord2h, texCoord2f, texCoord2d
    case texCoord3h, texCoord3f, texCoord3d
    case opaque, group, pathExpression

    case boolArray, uCharArray, intArray, uIntArray, int64Array, uInt64Array
    case halfArray, floatArray, doubleArray, timeCodeArray
    case stringArray, tokenArray, assetArray
    case int2Array, int3Array, int4Array
    case half2Array, half3Array, half4Array
    case float2Array, float3Array, float4Array
    case double2Array, double3Array, double4Array
    case point3hArray, point3fArray, point3dArray
    case vector3hArray, vector3fArray, vector3dArray
    case normal3hArray, normal3fArray, normal3dArray
    case color3hArray, color3fArray, color3dArray
    case color4hArray, color4fArray, color4dArray
    case quathArray, quatfArray, quatdArray
    case matrix2dArray, matrix3dArray, matrix4dArray
    case frame4dArray
    case texCoord2hArray, texCoord2fArray, texCoord2dArray
    case texCoord3hArray, texCoord3fArray, texCoord3dArray
    case pathExpressionArray
  }
}

extension Overlay
{
  public static func SdfGetValueTypeNameValue(_ type: Pixar.SdfValueTypeNameType) -> Pixar.SdfValueTypeName
  {
    Overlay.SdfGetValueTypeName(type)
  }
  
  public static func SdfGetValueTypeName(_ type: Pixar.SdfValueTypeNameType) -> Pixar.SdfValueTypeName
  {
    switch type {
      case .bool:                return Overlay.SdfValueTypeNames.Bool
      case .uChar:               return Overlay.SdfValueTypeNames.UChar
      case .int:                 return Overlay.SdfValueTypeNames.Int
      case .uInt:                return Overlay.SdfValueTypeNames.UInt
      case .int64:               return Overlay.SdfValueTypeNames.Int64
      case .uInt64:              return Overlay.SdfValueTypeNames.UInt64
      case .half:                return Overlay.SdfValueTypeNames.Half
      case .float:               return Overlay.SdfValueTypeNames.Float
      case .double:              return Overlay.SdfValueTypeNames.Double
      case .timeCode:            return Overlay.SdfValueTypeNames.TimeCode
      case .string:              return Overlay.SdfValueTypeNames.String
      case .token:               return Overlay.SdfValueTypeNames.Token
      case .asset:               return Overlay.SdfValueTypeNames.Asset
      case .int2:                return Overlay.SdfValueTypeNames.Int2
      case .int3:                return Overlay.SdfValueTypeNames.Int3
      case .int4:                return Overlay.SdfValueTypeNames.Int4
      case .half2:               return Overlay.SdfValueTypeNames.Half2
      case .half3:               return Overlay.SdfValueTypeNames.Half3
      case .half4:               return Overlay.SdfValueTypeNames.Half4
      case .float2:              return Overlay.SdfValueTypeNames.Float2
      case .float3:              return Overlay.SdfValueTypeNames.Float3
      case .float4:              return Overlay.SdfValueTypeNames.Float4
      case .double2:             return Overlay.SdfValueTypeNames.Double2
      case .double3:             return Overlay.SdfValueTypeNames.Double3
      case .double4:             return Overlay.SdfValueTypeNames.Double4
      case .point3h:             return Overlay.SdfValueTypeNames.Point3h
      case .point3f:             return Overlay.SdfValueTypeNames.Point3f
      case .point3d:             return Overlay.SdfValueTypeNames.Point3d
      case .vector3h:            return Overlay.SdfValueTypeNames.Vector3h
      case .vector3f:            return Overlay.SdfValueTypeNames.Vector3f
      case .vector3d:            return Overlay.SdfValueTypeNames.Vector3d
      case .normal3h:            return Overlay.SdfValueTypeNames.Normal3h
      case .normal3f:            return Overlay.SdfValueTypeNames.Normal3f
      case .normal3d:            return Overlay.SdfValueTypeNames.Normal3d
      case .color3h:             return Overlay.SdfValueTypeNames.Color3h
      case .color3f:             return Overlay.SdfValueTypeNames.Color3f
      case .color3d:             return Overlay.SdfValueTypeNames.Color3d
      case .color4h:             return Overlay.SdfValueTypeNames.Color4h
      case .color4f:             return Overlay.SdfValueTypeNames.Color4f
      case .color4d:             return Overlay.SdfValueTypeNames.Color4d
      case .quath:               return Overlay.SdfValueTypeNames.Quath
      case .quatf:               return Overlay.SdfValueTypeNames.Quatf
      case .quatd:               return Overlay.SdfValueTypeNames.Quatd
      case .matrix2d:            return Overlay.SdfValueTypeNames.Matrix2d
      case .matrix3d:            return Overlay.SdfValueTypeNames.Matrix3d
      case .matrix4d:            return Overlay.SdfValueTypeNames.Matrix4d
      case .frame4d:             return Overlay.SdfValueTypeNames.Frame4d
      case .texCoord2h:          return Overlay.SdfValueTypeNames.TexCoord2h
      case .texCoord2f:          return Overlay.SdfValueTypeNames.TexCoord2f
      case .texCoord2d:          return Overlay.SdfValueTypeNames.TexCoord2d
      case .texCoord3h:          return Overlay.SdfValueTypeNames.TexCoord3h
      case .texCoord3f:          return Overlay.SdfValueTypeNames.TexCoord3f
      case .texCoord3d:          return Overlay.SdfValueTypeNames.TexCoord3d
      case .opaque:              return Overlay.SdfValueTypeNames.Opaque
      case .group:               return Overlay.SdfValueTypeNames.Group
      case .pathExpression:      return Overlay.SdfValueTypeNames.PathExpression
      case .boolArray:           return Overlay.SdfValueTypeNames.BoolArray
      case .uCharArray:          return Overlay.SdfValueTypeNames.UCharArray
      case .intArray:            return Overlay.SdfValueTypeNames.IntArray
      case .uIntArray:           return Overlay.SdfValueTypeNames.UIntArray
      case .int64Array:          return Overlay.SdfValueTypeNames.Int64Array
      case .uInt64Array:         return Overlay.SdfValueTypeNames.UInt64Array
      case .halfArray:           return Overlay.SdfValueTypeNames.HalfArray
      case .floatArray:          return Overlay.SdfValueTypeNames.FloatArray
      case .doubleArray:         return Overlay.SdfValueTypeNames.DoubleArray
      case .timeCodeArray:       return Overlay.SdfValueTypeNames.TimeCodeArray
      case .stringArray:         return Overlay.SdfValueTypeNames.StringArray
      case .tokenArray:          return Overlay.SdfValueTypeNames.TokenArray
      case .assetArray:          return Overlay.SdfValueTypeNames.AssetArray
      case .int2Array:           return Overlay.SdfValueTypeNames.Int2Array
      case .int3Array:           return Overlay.SdfValueTypeNames.Int3Array
      case .int4Array:           return Overlay.SdfValueTypeNames.Int4Array
      case .half2Array:          return Overlay.SdfValueTypeNames.Half2Array
      case .half3Array:          return Overlay.SdfValueTypeNames.Half3Array
      case .half4Array:          return Overlay.SdfValueTypeNames.Half4Array
      case .float2Array:         return Overlay.SdfValueTypeNames.Float2Array
      case .float3Array:         return Overlay.SdfValueTypeNames.Float3Array
      case .float4Array:         return Overlay.SdfValueTypeNames.Float4Array
      case .double2Array:        return Overlay.SdfValueTypeNames.Double2Array
      case .double3Array:        return Overlay.SdfValueTypeNames.Double3Array
      case .double4Array:        return Overlay.SdfValueTypeNames.Double4Array
      case .point3hArray:        return Overlay.SdfValueTypeNames.Point3hArray
      case .point3fArray:        return Overlay.SdfValueTypeNames.Point3fArray
      case .point3dArray:        return Overlay.SdfValueTypeNames.Point3dArray
      case .vector3hArray:       return Overlay.SdfValueTypeNames.Vector3hArray
      case .vector3fArray:       return Overlay.SdfValueTypeNames.Vector3fArray
      case .vector3dArray:       return Overlay.SdfValueTypeNames.Vector3dArray
      case .normal3hArray:       return Overlay.SdfValueTypeNames.Normal3hArray
      case .normal3fArray:       return Overlay.SdfValueTypeNames.Normal3fArray
      case .normal3dArray:       return Overlay.SdfValueTypeNames.Normal3dArray
      case .color3hArray:        return Overlay.SdfValueTypeNames.Color3hArray
      case .color3fArray:        return Overlay.SdfValueTypeNames.Color3fArray
      case .color3dArray:        return Overlay.SdfValueTypeNames.Color3dArray
      case .color4hArray:        return Overlay.SdfValueTypeNames.Color4hArray
      case .color4fArray:        return Overlay.SdfValueTypeNames.Color4fArray
      case .color4dArray:        return Overlay.SdfValueTypeNames.Color4dArray
      case .quathArray:          return Overlay.SdfValueTypeNames.QuathArray
      case .quatfArray:          return Overlay.SdfValueTypeNames.QuatfArray
      case .quatdArray:          return Overlay.SdfValueTypeNames.QuatdArray
      case .matrix2dArray:       return Overlay.SdfValueTypeNames.Matrix2dArray
      case .matrix3dArray:       return Overlay.SdfValueTypeNames.Matrix3dArray
      case .matrix4dArray:       return Overlay.SdfValueTypeNames.Matrix4dArray
      case .frame4dArray:        return Overlay.SdfValueTypeNames.Frame4dArray
      case .texCoord2hArray:     return Overlay.SdfValueTypeNames.TexCoord2hArray
      case .texCoord2fArray:     return Overlay.SdfValueTypeNames.TexCoord2fArray
      case .texCoord2dArray:     return Overlay.SdfValueTypeNames.TexCoord2dArray
      case .texCoord3hArray:     return Overlay.SdfValueTypeNames.TexCoord3hArray
      case .texCoord3fArray:     return Overlay.SdfValueTypeNames.TexCoord3fArray
      case .texCoord3dArray:     return Overlay.SdfValueTypeNames.TexCoord3dArray
      case .pathExpressionArray: return Overlay.SdfValueTypeNames.PathExpressionArray
      default:                   return Overlay.SdfValueTypeNames.Bool
    }
  }
}
#endif
