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

public protocol Prim
{
  func set(doc: String) -> Void

  func getStage() -> Pixar.UsdStageWeakPtr

  func getPath() -> Pixar.Sdf.Path

  var path: Pixar.Sdf.Path { get }

  var name: Pixar.TfToken { get }

  var typeName: Pixar.TfToken { get }

  var children: [any Prim] { get }
}

public struct UsdPrim: Prim
{
  public init(_ path: String, type: Pixar.TfToken = Pixar.TfToken(), @StageBuilder children: () -> [any Prim] = { [] })
  {
    self.path = Pixar.Sdf.Path(
      (!path.contains("/") ? "/\(path)" : path)
        .replacingOccurrences(of: "/\(path)/\(path)", with: "/\(path)")
    )
    self.children = children()

    name = Pixar.TfToken()
    typeName = type
  }

  public func set(doc _: String)
  {}

  public func getStage() -> Pixar.UsdStageWeakPtr
  {
    .init()
  }

  public func getPath() -> Pixar.Sdf.Path
  {
    path
  }

  public var path: Pixar.Sdf.Path

  public var name: Pixar.TfToken

  public var typeName: Pixar.TfToken

  public var children: [any Prim]
}
