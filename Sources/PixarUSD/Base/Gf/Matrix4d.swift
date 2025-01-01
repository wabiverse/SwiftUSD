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

  /// Sets a row of the matrix from a ```Gf.Vec4d```.
  public mutating func setRow(at rowIndex: Int, to value: Gf.Vec4d)
  {
    SetRow(Int32(rowIndex), value)
  }

  /// Sets a column of the matrix from a ```Gf.Vec4d```.
  public mutating func setColumn(at columnIndex: Int, to value: Gf.Vec4d)
  {
    SetColumn(Int32(columnIndex), value)
  }

  /// Gets a row of the matrix as a ```Gf.Vec4```.
  public func getRow(at rowIndex: Int) -> Gf.Vec4d
  {
    GetRow(Int32(rowIndex))
  }

  /// Gets a column of the matrix as a ```Gf.Vec4```.
  public func getColumn(at columnIndex: Int) -> Gf.Vec4d
  {
    GetColumn(Int32(columnIndex))
  }

  /// Sets the matrix from 16 independent `Double` values,
  /// specified in row-major order. For example, parameter
  /// `m10` specifies the value in row 1 and column 0.
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

  /// Get the elements of this matrix as an array.
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

  /// Returns an iterator over this matrix's elements as scalars.
  ///
  /// This allows you to perform scalar operations like iterating
  /// through each element with a for-in loop or performing functional
  /// transformations.
  ///
  /// Example:
  /// ```swift
  /// let matrix: Gf.Matrix4d = ...
  /// for scalar in matrix {
  ///   print(scalar) // Accesses each scalar element of the matrix
  /// }
  /// ```
  ///
  /// The iterator yields the elements in row-major order:
  /// Row 0, Column 0 -> Row 0, Column 1 -> ... -> Row 3, Column 3
  ///
  /// - Returns: A `ScalarIterator` instance that conforms to `IteratorProtocol`.
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

  /// Accesses or modifies the element at the specified index in the matrix.
  ///
  /// This subscript provides direct access to the elements of the matrix as a
  /// flat sequence of values. It operates on the underlying storage of the matrix,
  /// which is organized as a contiguous array of scalars. The index must be within
  /// the range `0..<scalarCount`, where `scalarCount` is always 16 for a `Gf.Matrix4d`.
  ///
  /// - Parameter index: The index of the element to access. Must be in the range `0..<scalarCount`.
  ///
  /// - Returns: The scalar value at the specified index.
  /// - Note: This subscript is used for direct access to individual elements, typically in lower-level or SIMD operations.
  public subscript(index: Int) -> Self.Scalar
  {
    get
    {
      data()[index]
    }

    set
    {
      dataMutating()[index] = Scalar(newValue)
    }
  }

  /// Accesses the specified row as a `Gf.Vec4d`.
  ///
  /// **Data Access**: Row-major order.
  ///
  /// - Parameter row: The zero-based index of the row to access.
  ///
  /// - Returns: A 4D vector representing the specified row.
  /// - Complexity: O(1) for both `get` and `set`.
  ///
  /// Example:
  /// ```swift
  /// let row0 = matrix[0] // Access the first row as a Gf.Vec4d
  /// ```
  public subscript(row: Int) -> Gf.Vec4d
  {
    get
    {
      getRow(at: row)
    }
    set
    {
      setRow(at: row, to: newValue)
    }
  }

  /// Accesses an individual element of the matrix by its row and column indices.
  ///
  /// This subscript provides intuitive two-dimensional access to the matrix
  /// elements using row and column indices.
  ///
  /// **Index Mapping**:
  /// - Row 0, Column 0 corresponds to the first element
  /// - Row 1, Column 2 corresponds to the 6th element
  ///
  /// - Parameter row: The zero-based index of the row (0...3).
  /// - Parameter column: The zero-based index of the column (0...3).
  ///
  /// - Returns: The scalar value at the specified row and column.
  ///
  /// Example:
  /// ```swift
  /// var matrix: Gf.Matrix4d = ...
  /// let value = matrix[1, 2] // Access the element at Row 1, Column 2
  /// matrix[2, 0] = 3.0 // Sets the element at Row 2, Column 0
  /// ```
  public subscript(row: Int, column: Int) -> Scalar
  {
    get
    {
      // Get the row, then access the column of that row.
      getRow(at: row)[column]
    }
    set
    {
      // Get the row, modify the column, and then set the updated row.
      var rowValues = getRow(at: row)
      rowValues[column] = newValue
      setRow(at: row, to: rowValues)
    }
  }

  /// Returns the matrix data as a `SIMD16` vector for optimized computation.
  ///
  /// The `simd` property combines the 16 scalar components of the 4x4 matrix
  /// into a `SIMD16` structure, enabling high-performance operations when using
  /// SIMD instructions.
  ///
  /// **Data Ordering**: Row-major order.
  /// ```
  /// // Access the SIMD representation of a Gf.Matrix4d
  /// let simdMatrix = matrix.simd
  /// ```
  ///
  /// Setting this property updates the underlying matrix elements.
  /// ```swift
  /// var matrix: Gf.Matrix4d = ...
  /// matrix.simd = SIMD16(...) // Updates matrix elements in row-major order
  /// ```
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
      for i in 0 ..< 16
      {
        dataMutating()[i] = Scalar(newValue[i])
      }
    }
  }

  /// Initializes a `Gf.Matrix4d` from a SIMD16 vector.
  ///
  /// The `init` method allows creating a matrix directly from a
  /// `SIMD16` vector. The vector's elements are used to populate
  /// the matrix in row-major order:
  /// - Elements 0-3 -> Row 0
  /// - Elements 4-7 -> Row 1
  /// - Elements 8-11 -> Row 2
  /// - Elements 12-15 -> Row 3
  ///
  /// - Parameter simd: A `SIMD16` vector containing the 16 scalar elements.
  ///
  /// Example:
  /// ```swift
  /// let simd = SIMD16<Double>(0, 1, 2, ..., 15)
  /// let matrix = Gf.Matrix4d(simd)
  /// ```
  public init(_ simd: SIMD16<Scalar>)
  {
    self.init()

    self.simd = simd
  }
}
