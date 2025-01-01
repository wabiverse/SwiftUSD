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
  public mutating func normalize(eps: Double = GF_MIN_VECTOR_LENGTH) -> Double
  {
    Normalize(eps)
  }

  /// Returns a normalized version of this vector, returning the
  /// vector after undergoing normalization. If the length of the
  /// vector is smaller than argument **eps**, then the vector is
  /// set to the value of `self / eps`.
  public func getNormalized(eps: Double = GF_MIN_VECTOR_LENGTH) -> Self
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

public extension Gf
{
  /// Returns component-wise multiplication of two vectors.
  /// - Parameter v1: A vector to multiply.
  /// - Parameter v2: A second vector to multiply with.
  ///
  /// - Returns: The component-wise multiplication of the two vectors.
  @inlinable
  static func compMult(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Gf.Vec3d
  {
    Pixar.GfCompMult(v1, v2)
  }

  /// Returns component-wise division of two vectors.
  /// - Parameter v1: A vector to divide.
  /// - Parameter v2: A second vector to divide by.
  ///
  /// - Returns: The component-wise division of the two vectors.
  @inlinable
  static func compDiv(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Gf.Vec3d
  {
    Pixar.GfCompDiv(v1, v2)
  }

  /// Returns the dot (inner) product of two vectors.
  /// - Parameter v1: A vector to multiply.
  /// - Parameter v2: A second vector to multiply with.
  ///
  /// - Returns: The dot product of the two vectors.
  @inlinable
  static func dot(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Double
  {
    Pixar.GfDot(v1, v2)
  }

  /// Returns the geometric length of a vector.
  /// - Parameter v: The vector to measure.
  ///
  /// - Returns: The geometric length of the vector.
  @inlinable
  static func getLength(_ v: Gf.Vec3d) -> Double
  {
    Pixar.GfGetLength(v)
  }

  /// Normalizes the vector in place to unit length, returning the length before
  /// normalization. If the length of the vector is smaller than `eps` then the
  /// vector is set to vector/eps, the original length of the vector is returned.
  /// - Parameter v: The vector to normalize.
  /// - Parameter eps: The length of the vector.
  ///
  /// - Returns: The length of the vector.
  @inlinable
  static func normalize(_ v: inout Gf.Vec3d, eps: Double = GF_MIN_VECTOR_LENGTH) -> Double
  {
    Pixar.GfNormalize(&v, eps)
  }

  /// Returns a normalized (unit-length) vector with the same direction as the given
  /// vector. If the length of this vector is smaller than `eps`, the vector divided
  /// by `eps` is returned.
  /// - Parameter v: The vector to normalize.
  /// - Parameter eps: The length of the vector.
  ///
  /// - Returns: The normalized vector.
  @inlinable
  static func getNormalized(_ v: Gf.Vec3d, eps: Double = GF_MIN_VECTOR_LENGTH) -> Gf.Vec3d
  {
    Pixar.GfGetNormalized(v, eps)
  }

  /// Returns the projection of vector `v1` onto vector `v2`.
  /// That is `v2 * (v1 * v2)`.
  /// - Parameter v1: The vector to project.
  /// - Parameter v2: The vector to project onto.
  ///
  /// - Returns: The projection of `v1` onto `v2`.
  @inlinable
  static func getProjection(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Gf.Vec3d
  {
    Pixar.GfGetProjection(v1, v2)
  }

  /// Returns the orthogonal complement of vector `v1` onto vector `v2`.
  /// That is `v1 - v1.getProjection(v2)`.
  /// - Parameter v1: The vector to project.
  /// - Parameter v2: The vector to project onto.
  ///
  /// - Returns: The orthogonal complement of `v1` onto `v2`.
  @inlinable
  static func getComplement(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Gf.Vec3d
  {
    Pixar.GfGetComplement(v1, v2)
  }

  /// Tests for equality within a given `tolerance`, returning `true` if the
  /// length of the difference vector is **less than** or **equal to** `tolerance`.
  /// - Parameter v1: The first vector to compare.
  /// - Parameter v2: The second vector to compare.
  /// - Parameter tolerance: The tolerance to use.
  ///
  /// - Returns: `true` if the vectors are equal within the tolerance.
  @inlinable
  static func isClose(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d, within tolerance: Double) -> Bool
  {
    Pixar.GfIsClose(v1, v2, tolerance)
  }

  /// Returns the cross product of two vectors.
  /// - Parameter v1: The first vector.
  /// - Parameter v2: The second vector.
  ///
  /// - Returns: The cross product of the two vectors.
  @inlinable
  static func cross(_ v1: Gf.Vec3d, _ v2: Gf.Vec3d) -> Gf.Vec3d
  {
    Pixar.GfCross(v1, v2)
  }
}
