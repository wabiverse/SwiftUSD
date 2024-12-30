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
 * # GfRotation
 *
 * Basic type for a 3-space rotation specification.
 */
public typealias GfRotation = Pixar.GfRotation

public extension Gf
{
  /**
   * # GfRotation
   *
   * Basic type for a 3-space rotation specification.
   */
  typealias Rotation = GfRotation
}

public extension Gf.Rotation
{
  static func * (lhs: Gf.Rotation, rhs: Gf.Rotation) -> Gf.Rotation
  {
    var result = lhs
    result *= rhs
    return result
  }

  static func * (rotation: Gf.Rotation, scale: Double) -> Gf.Rotation
  {
    var result = rotation
    result *= scale
    return result
  }
}
