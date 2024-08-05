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

import Gf

/* note: the typealiases are documented the same way twice,
 * keep it like this so that sourcekit shows documentation
 * regardless of which typealias a user might use in their
 * code. */

/**
 * # GfVec3d
 *
 * Basic type for a vector of 3 double components.
 *
 * Represents a vector of 3 components of type **double**.
 * It is intended to be fast and simple.
 */
public typealias GfVec3d = Pixar.GfVec3d

public extension Gf
{
  /**
   * # GfVec3d
   *
   * Basic type for a vector of 3 double components.
   *
   * Represents a vector of 3 components of type **double**.
   * It is intended to be fast and simple.
   */
  typealias Vec3d = GfVec3d
}

extension Gf.Vec3d: Scalar
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

  /// Set all elements with explicit arguments.
  public mutating func set(_ s0: Double, _ s1: Double, _ s2: Double) -> Self
  {
    Set(s0, s1, s2).pointee
  }

  /// Set all elements with an array as the argument.
  public mutating func set(_ a: [ScalarType]) -> Self
  {
    Set(a).pointee
  }

  /// Get the elements of this vector as an array.
  public func getArray() -> [ScalarType]
  {
    let buffer = UnsafeBufferPointer(start: GetArray(), count: GfVec3d.scalarCount)

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

  /// Returns the orthogonal complement of this vector onto
  /// **other**, that is:
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

  /// Returns an iterator over this scalar.
  ///
  /// Since this type can return its own iterator, it conforms
  /// this scalar to a sequence to enable many useful operations,
  /// like for-in looping and the contains method, without much
  /// effort.
  public func makeIterator() -> ScalarIterator<Self>
  {
    ScalarIterator(self)
  }
}

extension Gf.Vec3d: SIMD
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
