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

import Usd

public typealias UsdPrimRange = Pixar.UsdPrimRange

public extension Pixar.Usd
{
  /**
   * # Pixar.Usd.PrimRange
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

extension Pixar.Usd.PrimRange: IteratorProtocol
{
  public typealias Element = Pixar.Usd.Prim

  public mutating func next() -> Element?
  {
    guard empty() == false
    else { return nil }

    let prim = front()

    increment_begin()

    return prim
  }
}
