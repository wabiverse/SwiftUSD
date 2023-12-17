/* --------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                          ::
 * --------------------------------------------------------------
 * This program is free software; you can redistribute it, and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Check out
 * the GNU General Public License for more details.
 *
 * You should have received a copy for this software license, the
 * GNU General Public License along with this program; or, if not
 * write to the Free Software Foundation, Inc., to the address of
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

public typealias GfVec3f = Pixar.GfVec3f

public extension Pixar.Gf
{
  typealias Vec3f = GfVec3f
}

/**
 * # GfVec3f
 *
 * Basic type for a vector of 3 float components.
 *
 * Represents a vector of 3 components of type **float**.
 * It is intended to be fast and simple.
 */
extension GfVec3f: Scalar
{
  /// Axis count of the vector.
  public typealias AxisCount = Axis3

  /// Create a unit vector along the specified axis.
  public static func axis(_ axis: AxisCount) -> Self
  {
    switch axis
    {
      case .x:
        XAxis()

      case .y:
        YAxis()

      case .z:
        ZAxis()
    }
  }

  public mutating func set(_ s0: Float, _ s1: Float, _ s2: Float) -> Self
  {
    Set(s0, s1, s2).pointee
  }

  public mutating func set(_ a: [ScalarType]) -> Self
  {
    Set(a).pointee
  }

  public func getArray() -> [ScalarType]
  {
    let buffer = UnsafeBufferPointer(start: GetArray(), count: GfVec3f.scalarCount)

    return Array(buffer)
  }

  public func getProjection(_ other: Self) -> Self
  {
    GetProjection(other)
  }

  public func getComplement(_ normal: Self) -> Self
  {
    GetComplement(normal)
  }

  public func getLengthSq() -> Float
  {
    GetLengthSq()
  }

  public func getLength() -> Float
  {
    GetLength()
  }

  public mutating func normalize(_ eps: Float) -> Float
  {
    Normalize(eps)
  }

  public func getNormalized(_ eps: Float) -> Self
  {
    GetNormalized(eps)
  }
}

extension GfVec3f: SIMD
{
  public typealias Scalar = Self.ScalarType
  public typealias SIMDStorage = SIMD3<Scalar>
  public typealias MaskStorage = SIMD3<Scalar>.MaskStorage

  public var scalarCount: Int { 3 }

  public var simd: SIMD3<Scalar>
  {
    get
    {
      SIMD3<Scalar>(
        Scalar(data()[0]), 
        Scalar(data()[1]),
        Scalar(data()[2])
      )
    }
    set
    {
      dataMutating()[0] = Scalar(newValue[0])
      dataMutating()[1] = Scalar(newValue[1])
      dataMutating()[2] = Scalar(newValue[2])
    }
  }

  public init(_ simd: SIMD3<Scalar>)
  {
    self.init()

    self.simd = simd
  }
}
