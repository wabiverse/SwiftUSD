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

import Gf

/* note: the typealiases are documented the same way twice,
 * keep it like this so that sourcekit shows documentation
 * regardless of which typealias a user might use in their
 * code. */

/**
 * # GfVec2d
 *
 * Basic type for a vector of 2 double components.
 *
 * Represents a vector of 2 components of type **double**.
 * It is intended to be fast and simple.
 */
public typealias GfVec2d = Pixar.GfVec2d

public extension Pixar.Gf
{
  /**
   * # GfVec2d
   *
   * Basic type for a vector of 2 double components.
   *
   * Represents a vector of 2 components of type **double**.
   * It is intended to be fast and simple.
   */
  typealias Vec2d = GfVec2d
}

extension GfVec2d: Scalar
{
  /// Axis count of the vector.
  public typealias AxisCount = Axis2

  /// Create a unit vector along the specified axis.
  public static func axis(_ axis: AxisCount) -> Self
  {
    switch axis
    {
      case .x:
        XAxis()

      case .y:
        YAxis()
    }
  }

  /// Set all elements with explicit arguments.
  public mutating func set(_ s0: Double, _ s1: Double) -> Self
  {
    Set(s0, s1).pointee
  }

  /// Set all elements with an array as the argument.
  public mutating func set(_ a: [ScalarType]) -> Self
  {
    Set(a).pointee
  }

  /// Get the elements of this vector as an array.
  public func getArray() -> [ScalarType]
  {
    let buffer = UnsafeBufferPointer(start: GetArray(), count: GfVec2d.scalarCount)

    return Array(buffer)
  }

  /// Returns the projection of this vector onto **other**,
  /// that is:
  /// ```
  /// other * (self * other)
  /// ```
  public func getProjection(_ other: Self) -> Self
  {
    GetProjection(other)
  }

  /// Returns the orthogonal complement of this vector onto **other**,
  /// that is:
  /// ```
  ///  self - self.getProjection(b)
  /// ```
  public func getComplement(_ normal: Self) -> Self
  {
    GetComplement(normal)
  }

  /// Returns the squared length of this vector,
  /// that is:
  /// ```
  ///  self * self
  /// ```
  public func getLengthSq() -> Double
  {
    GetLengthSq()
  }

  /// Returns the length of this vector,
  /// that is:
  /// ```
  ///  Gf.sqrt(self.getLengthSq())
  /// ```
  public func getLength() -> Double
  {
    GetLength()
  }

  /// Normalizes the vector in place to unit length, returning the
  /// length before normalization. If the length of the vector is
  /// smaller than argument **eps**, then the vector is set to the
  /// value of `self / eps`.
  ///
  /// The original length of the vector is returned.
  /// See also: `Gf.normalize()`.
  public mutating func normalize(_ eps: Double) -> Double
  {
    Normalize(eps)
  }

  /// Returns a normalized version of this vector, returning the
  /// vector after undergoing normalization. If the length of the
  /// vector is smaller than argument **eps**, then the vector is
  /// set to the value of `self / eps`.
  public func getNormalized(_ eps: Double) -> Self
  {
    GetNormalized(eps)
  }
}

extension GfVec2d: SIMD
{
  public typealias Scalar = Self.ScalarType
  public typealias SIMDStorage = SIMD2<Scalar>
  public typealias MaskStorage = SIMD2<Scalar>.MaskStorage

  public var scalarCount: Int { 2 }

  public var simd: SIMD2<Scalar>
  {
    get
    {
      SIMD2<Scalar>(
        Scalar(data()[0]),
        Scalar(data()[1])
      )
    }
    set
    {
      dataMutating()[0] = Scalar(newValue[0])
      dataMutating()[1] = Scalar(newValue[1])
    }
  }

  public init(_ simd: SIMD2<Scalar>)
  {
    self.init()

    self.simd = simd
  }
}
