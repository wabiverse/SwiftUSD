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
 * # GfMatrix4d
 *
 * Basic type for a 4x4 matrix of double components.
 */
public typealias GfMatrix4d = Pixar.GfMatrix4d

public extension Gf
{
  /**
   * # GfMatrix4d
   *
   * Basic type for a 4x4 matrix of double components.
   */
  typealias Matrix4d = GfMatrix4d
}

extension Gf.Matrix4d: Scalar
{
  /// Axis count of the vector.
  public typealias AxisCount = Axis16

  public func getRow(_ index: Int) -> Gf.Vec4d
  {
    GetRow(Int32(index))
  }

  public func getColumn(_ index: Int) -> Gf.Vec4d
  {
    GetColumn(Int32(index))
  }

  /// Sets the matrix from 16 independent \c double values,
  /// specified in row-major order. For example, parameter \e m10 specifies
  /// the value in row 1 and column 0.
  public mutating func set(_ m00: Double, _ m01: Double, _ m02: Double, _ m03: Double, _ m10: Double,
                           _ m11: Double, _ m12: Double, _ m13: Double, _ m20: Double, _ m21: Double,
                           _ m22: Double, _ m23: Double, _ m30: Double, _ m31: Double, _ m32: Double,
                           _ m33: Double) -> Self
  {
    Set(m00, m01, m02, m03, m10,
        m11, m12, m13, m20, m21,
        m22, m23, m30, m31, m32,
        m33).pointee
  }

  /// Get the elements of this Matrix as an array.
  public func getArray() -> [ScalarType]
  {
    let buffer = UnsafeBufferPointer(start: GetArray(), count: GfMatrix4d.scalarCount)

    return Array(buffer)
  }

  /// Normalizes the Matrix in place to unit length, returning the
  /// length before normalization. If the length of the Matrix is
  /// smaller than argument **eps**, then the Matrix is set to the
  /// value of `self / eps`.
  ///
  /// The original length of the Matrix is returned.
  /// See also: `Gf.normalize()`.
  public mutating func orthonormalize(warn: Bool = true) -> Bool
  {
    Orthonormalize(warn)
  }

  /// Returns a normalized version of this Matrix, returning the
  /// Matrix after undergoing normalization. If the length of the
  /// Matrix is smaller than argument **eps**, then the Matrix is
  /// set to the value of `self / eps`.
  public func getOrthonormalized(warn: Bool = true) -> Self
  {
    GetOrthonormalized(warn)
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

extension Gf.Matrix4d: SIMD
{
  public typealias Scalar = Self.ScalarType
  public typealias SIMDStorage = SIMD16<Scalar>
  public typealias MaskStorage = SIMD16<Scalar>.MaskStorage

  public var scalarCount: Int { 16 }

  public subscript(index: Int) -> Self.Scalar
  {
    get
    {
      getArray()[index]
    }

    set
    {
      dataMutating()[index] = Scalar(newValue)
    }
  }

  public var simd: SIMD16<Scalar>
  {
    get
    {
      SIMD16<Scalar>(
        Scalar(data()[0]),
        Scalar(data()[1]),
        Scalar(data()[2]),
        Scalar(data()[3]),
        Scalar(data()[4]),
        Scalar(data()[5]),
        Scalar(data()[6]),
        Scalar(data()[7]),
        Scalar(data()[8]),
        Scalar(data()[9]),
        Scalar(data()[10]),
        Scalar(data()[11]),
        Scalar(data()[12]),
        Scalar(data()[13]),
        Scalar(data()[14]),
        Scalar(data()[15])
      )
    }
    set
    {
      dataMutating()[0] = Scalar(newValue[0])
      dataMutating()[1] = Scalar(newValue[1])
      dataMutating()[2] = Scalar(newValue[2])
      dataMutating()[3] = Scalar(newValue[3])
      dataMutating()[4] = Scalar(newValue[4])
      dataMutating()[5] = Scalar(newValue[5])
      dataMutating()[6] = Scalar(newValue[6])
      dataMutating()[7] = Scalar(newValue[7])
      dataMutating()[8] = Scalar(newValue[8])
      dataMutating()[9] = Scalar(newValue[9])
      dataMutating()[10] = Scalar(newValue[10])
      dataMutating()[11] = Scalar(newValue[11])
      dataMutating()[12] = Scalar(newValue[12])
      dataMutating()[13] = Scalar(newValue[13])
      dataMutating()[14] = Scalar(newValue[14])
      dataMutating()[15] = Scalar(newValue[15])
    }
  }

  public init(_ simd: SIMD16<Scalar>)
  {
    self.init()

    self.simd = simd
  }
}
