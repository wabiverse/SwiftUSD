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

import Usd

public typealias UsdPrimSiblingRange = Pixar.UsdPrimSiblingRange

public extension Usd
{
  typealias PrimSiblingRange = UsdPrimSiblingRange
}

extension Usd.PrimSiblingRange: IteratorProtocol
{
  public typealias Element = Usd.Prim

  @discardableResult
  private mutating func advance_beginCopy() -> Usd.PrimSiblingRange
  {
    __advance_beginUnsafe(1).pointee
  }

  public mutating func next() -> Element?
  {
    guard empty() == false
    else { return nil }

    let prim = front()

    advance_beginCopy()

    return prim
  }
}
