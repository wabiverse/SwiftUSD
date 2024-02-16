/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

public protocol Scalar: Sequence, Dimensional
{
  /// Scalar element type.
  associatedtype ScalarType: Numeric

  /// Default constructor does no initialization.
  init()

  /// Initialize all elements to a single value.
  init(_ value: ScalarType)

  /// Indexing.
  subscript(_: Int) -> ScalarType { get set }

  /// Create a unit vector along the specified axis.
  static func axis<T>(_ axis: T) -> Self where T == AxisCount

  // Set all elements with an array.
  mutating func set(_ a: [ScalarType]) -> Self

  /// Direct data access.
  func getArray() -> [ScalarType]

  /// Returns the projection of this onto other.
  /// That is, the component of this that is parallel to other.
  func getProjection(_ other: Self) -> Self

  /// Returns the component of this that is orthogonal to other.
  /// That is, the component of this that is perpendicular to other.
  func getComplement(_ normal: Self) -> Self

  /// Squared length.
  func getLengthSq() -> ScalarType

  /// Returns an iterator over the elements in this scalar.
  func makeIterator() -> ScalarIterator<Self>
}

/// Create an iterator for all scalar types,
/// so that they can act as their own iterator.
public struct ScalarIterator<T>: IteratorProtocol where T: Scalar
{
  let scalar: T
  var index = 0

  public init(_ scalar: T)
  {
    self.scalar = scalar
  }

  public mutating func next() -> T.ScalarType?
  {
    let nextIndex = index + 1
    guard nextIndex < (T.AxisCount.dimension + 1)
    else { return nil }

    let valueIndex = scalar.getArray().index(before: nextIndex)

    index += 1
    return scalar.getArray()[valueIndex]
  }
}
