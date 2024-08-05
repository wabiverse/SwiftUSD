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

public typealias UsdPrimRange = Pixar.UsdPrimRange

public extension Usd
{
  /**
   * # Usd.PrimRange
   *
   * An forward-iterable range that traverses a subtree of prims rooted at a
   * given prim in depth-first order.
   *
   * In addition to depth-first order, UsdPrimRange provides the optional ability
   * to traverse in depth-first pre- and post-order wher prims appear twice in
   * the range; first before all descendants and then again immediately after all
   * descendants. This is useful for maintaining state associated with subtrees,
   * in a stack-like fashion.  See ``PrimRange/iterator/isPostVisit()`` to
   * detect when an iterator is visiting a prim for the second time.
   *
   * There are several constructors providing different levels of configurability;
   * ultimately, one can provide a prim predicate for a custom iteration, just as
   * one would use ``Usd.Prim.getFilteredChildren()`` in a custom recursion.
   *
   * Why would one want to use a ``PrimRange`` rather than just iterating
   * over the results of ``Prim/getFilteredDescendants()``?  Primarily, if
   * one of the following applies:
   * - You need to perform pre-and-post-order processing
   * - You may want to prune sub-trees from processing (see Usd.PrimRange.iterator.pruneChildren())
   * - You want to treat the root prim itself uniformly with its descendents (getFilteredDescendants() will not
   * return the root prim itself, while ``PrimRange`` will, see  ``PrimRange/stage`` for an exception). */
  typealias PrimRange = UsdPrimRange
}

extension Usd.PrimRange: IteratorProtocol
{
  public typealias Element = Usd.Prim

  public mutating func next() -> Element?
  {
    guard empty() == false
    else { return nil }

    let prim = front()

    increment_begin()

    return prim
  }
}
