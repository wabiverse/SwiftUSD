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
import Sdf
import Usd

public protocol Stage
{
  associatedtype Scene: Collection where Scene.Element == any Prim

  @StageBuilder
  var scene: Self.Scene { get }
}

public struct UsdStage: Stage
{
  public typealias Scene = [any Prim]

  public var stage: StageRefPtr

  /**
   * Common file exts, for convenience.
   */
  public enum FileExt: String, CaseIterable
  {
    case usd
    case usda
    case usdc
    case usdz
  }

  public init(_ identifier: String, ext: FileExt, @StageBuilder scene: () -> Scene)
  {
    self.init("\(identifier).\(ext.rawValue)", scene: scene)
  }

  public init(_ identifier: String, @StageBuilder scene: () -> Scene)
  {
    stage = Pixar.Usd.Stage.createNew(identifier)

    scene().forEach
    { prim in

      if !prim.path.string.isEmpty
      {
        print("Defining prim:", prim.path.string)
        let parent = stage.definePrim(prim.path, type: prim.typeName)

        for children in prim.children
        {
          let child = define(prim: children, after: [parent])

          for grandchildren in children.children
          {
            let grandchild = define(prim: grandchildren, after: [parent, child])

            for n3children in grandchildren.children
            {
              let _ = define(prim: n3children, after: [parent, child, grandchild])
            }
          }
        }
      }
    }
  }

  private func define(prim: any Prim, after primStack: [Pixar.Usd.Prim]) -> Pixar.Usd.Prim
  {
    let primPath: Pixar.SdfPath = .init(prim.path.string.replacingOccurrences(of: "/", with: ""))

    let pathDepth = primStack.reduce(Pixar.SdfPath("/"))
    { p1, p2 in
      let sdfPath: Pixar.SdfPath = .init(p2.path.string.components(separatedBy: "/").last?.replacingOccurrences(of: "/", with: "") ?? "")

      return p1.append(path: sdfPath)
    }

    return stage.definePrim(pathDepth.append(path: primPath), type: prim.typeName)
  }

  @StageBuilder
  public var scene: Scene
  {
    getPrims()
  }

  private func getPrims() -> Scene
  {
    let it = Pixar.UsdPrimRange.Stage(stage.pointee.getPtr())

    return IteratorSequence(it).map { $0 }
  }

  @discardableResult
  public func set(doc: String) -> UsdStage
  {
    stage.getPseudoRoot().set(doc: doc)

    return self
  }

  @discardableResult
  public func save() -> UsdStage
  {
    stage.save()

    return self
  }
}
