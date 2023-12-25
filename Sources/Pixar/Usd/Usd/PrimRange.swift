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

import Usd

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
   * in a stack-like fashion.  See ``Usd.PrimRange.iterator.isPostVisit()`` to
   * detect when an iterator is visiting a prim for the second time.
   *
   * There are several constructors providing different levels of configurability;
   * ultimately, one can provide a prim predicate for a custom iteration, just as
   * one would use ``Usd.Prim.getFilteredChildren()`` in a custom recursion.
   *
   * Why would one want to use a ``Usd.PrimRange`` rather than just iterating
   * over the results of ``UsdPrim.getFilteredDescendants()``?  Primarily, if
   * one of the following applies:
   * - You need to perform pre-and-post-order processing
   * - You may want to prune sub-trees from processing (see Usd.PrimRange.iterator.pruneChildren())
   * - You want to treat the root prim itself uniformly with its descendents (getFilteredDescendants() will not
   * return the root prim itself, while ``Usd.PrimRange`` will, see  ``Usd.PrimRange.stage`` for an exception). */
  typealias PrimRange = Pixar.UsdPrimRange
}
