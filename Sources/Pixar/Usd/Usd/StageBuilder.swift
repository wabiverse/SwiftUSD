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
 *       Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import Foundation
import Usd

@resultBuilder
public struct StageBuilder
{
  public static func buildBlock(_ components: [Prim]...) -> [Prim]
  {
    components.flatMap { $0 }
  }

  /// Add support for both single and collections of prims.
  public static func buildExpression(_ expression: Prim) -> [Prim]
  {
    [expression]
  }

  public static func buildExpression(_ expression: [Prim]) -> [Prim]
  {
    expression
  }

  /// Add support for optionals.
  public static func buildOptional(_ components: [Prim]?) -> [Prim]
  {
    components ?? []
  }

  /// Add support for if statements.
  public static func buildEither(first components: [Prim]) -> [Prim]
  {
    components
  }

  public static func buildEither(second components: [Prim]) -> [Prim]
  {
    components
  }

  /// Add support for loops.
  public static func buildArray(_ components: [[Prim]]) -> [Prim]
  {
    components.flatMap { $0 }
  }

  /// Add support for #availability checks.
  public static func buildLimitedAvailability(_ components: [Prim]) -> [Prim]
  {
    components
  }
}
