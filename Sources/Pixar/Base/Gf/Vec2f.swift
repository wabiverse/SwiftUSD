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

public typealias GfVec2f = CXX.GfVec2f

public extension Pixar.Gf
{
  /**
   * # GfVec2f
   *
   * Basic type for a vector of 2 float components.
   *
   * Represents a vector of 2 components of type **float**.
   * It is intended to be fast and simple.
   */
  struct Vec2f: Scalar
  {
    /// Scalar element type and dimension.
    public typealias ScalarType = Float
    public static let dimension: Int = 2
    public let scalarCount: Int = dimension

    /// Axis count of the vector.
    public typealias AxisCount = Axis2

    /// Default constructor does no initialization.
    public init()
    {}

    /// Create a unit vector along the specified axis.
    public static func axis(_ axis: AxisCount) -> Self
    {
      switch axis
      {
        case .x:
          var result = Vec2f(0)
          result[0] = 1
          return result

        case .y:
          var result = Vec2f(0)
          result[1] = 1
          return result
      }
    }

    public mutating func set(_ s0: Float, _ s1: Float) -> Vec2f
    {
      _data[0] = s0
      _data[1] = s1
      return self
    }

    public mutating func set(_ a: [ScalarType]) -> Vec2f
    {
      set(a[0], a[1])
    }

    public func data() -> [ScalarType]
    {
      _data
    }

    public func getArray() -> [ScalarType]
    {
      data()
    }

    public func getProjection(_ other: Vec2f) -> Vec2f
    {
      other * (self * other)
    }

    public func getComplement(_ normal: Vec2f) -> Vec2f
    {
      self - getProjection(normal)
    }

    public mutating func getLengthSq() -> Float
    {
      self * self
    }

    public mutating func getLength() -> Float
    {
      CXX.GfSqrt(getLengthSq())
    }

    public mutating func normalize(_ eps: Float) -> Float
    {
      // TODO: this seems suspect... the result of the division
      // operation is discarded.
      let length = getLength()
      self /= (length > eps) ? length : 1
      return length
    }

    public func getNormalized(_ eps: Float) -> Vec2f
    {
      var normalized = self
      return Vec2f(normalized.normalize(eps))
    }

    public init(_ other: GfVec2f)
    {
      self.init()

      _data[0] = other[0]
      _data[1] = other[1]
    }

    public static func * (lhs: Vec2f, rhs: Vec2f) -> Float
    {
      lhs[0] * rhs[0] + lhs[1] * rhs[1]
    }

    public static func == (lhs: Vec2f, rhs: GfVec2f) -> Bool
    {
      lhs.data()[0] == rhs.data()[0] && lhs.data()[1] == rhs.data()[1]
    }

    public var _data: [ScalarType] = [0, 0]
  }
}

extension Pixar.Gf.Vec2f: SIMD
{
  public typealias Scalar = Self.ScalarType
  public typealias SIMDStorage = SIMD2<ScalarType>
  public typealias MaskStorage = SIMD2<ScalarType>.MaskStorage

  public var simd: SIMD2<Scalar>
  {
    get
    {
      SIMD2<Scalar>(Scalar(_data[0]), Scalar(_data[1]))
    }
    set
    {
      _data[0] = Float(newValue[0])
      _data[1] = Float(newValue[1])
    }
  }

  public init(_ simd: SIMD2<Scalar>)
  {
    self.init()

    self.simd = simd
  }
}
