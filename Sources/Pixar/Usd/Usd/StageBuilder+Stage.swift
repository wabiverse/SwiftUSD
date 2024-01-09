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

/**
 * A Pixar.Usd.Stage for declaratively authoring scene description.
 *
 * This api is currently experimental and will evolve overtime, its
 * purpose is to declaratively author scene description in a design
 * pattern that is similiar to that of SwiftUI, while ensuring that
 * the full range and extensibility of Pixar's USD API is preserved
 * within a innovative, exceptionally simple and highly expressible
 * way to author scene description using UsdPrim building blocks to
 * compose a scenegraph that are owned & presented by the outermost
 * UsdStage that contains them. */
public struct UsdStage
{
  public var stage: StageRefPtr
  public var prims: [UsdPrim]

  public init(_ identifier: String,
              ext: FileExt,
              load set: Pixar.Usd.Stage.InitialLoadingSet = .all,
              @StageBuilder prims: () -> [UsdPrim])
  {
    stage = Pixar.Usd.Stage.createNew("\(identifier).\(ext.rawValue)", load: set)

    self.prims = []
    populate(prims: prims())
  }

  public init(_ identifier: String,
              load set: Pixar.Usd.Stage.InitialLoadingSet = .all,
              @StageBuilder prims: () -> [UsdPrim])
  {
    stage = Pixar.Usd.Stage.createNew(identifier, load: set)

    self.prims = []
    populate(prims: prims())
  }

  private mutating func populate(prims: [UsdPrim])
  {
    for prim in prims
    {
      define(prim: prim, after: self.prims)
      self.prims.append(prim)
    }
  }

  @StageBuilder
  public var scene: [UsdPrim]
  {
    getPrims().compactMap
    {
      UsdPrim($0.path.string, type: .token($0.typeName))
    }
  }

  private func getPrims() -> [Pixar.Usd.Prim]
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
}

/* 
 * ------------------------------------------------------------------------------
 * Private UsdStage extensions to allow users to declaratively define prim types.
 * --- */

public extension UsdStage
{
  /**
   * Private internal function to allow declaratively defining prim schema types.
   *
   * Usage example:
   * ```
   * UsdStage("HelloWorldExample", ext: .usda)
   * {
   *   UsdPrim("Hello", type: .xform)
   *   {
   *     UsdPrim("World", type: .sphere)
   *   }
   * }
   * ``` */
  @discardableResult
  private func define(prim: UsdPrim, after primStack: [UsdPrim]) -> Pixar.Usd.Prim
  {
    let primPath: Pixar.SdfPath = .init(prim.path.string.replacingOccurrences(of: "/", with: ""))

    let pathDepth = primStack.reduce(Pixar.SdfPath("/"))
    { p1, p2 in
      let sdfPath: Pixar.SdfPath = .init(p2.path.string.components(separatedBy: "/").last?.replacingOccurrences(of: "/", with: "") ?? "")

      return p1.append(path: sdfPath)
    }

    switch prim.type
    {
      case .xform, .sphere, .capsule, .cylinder, .cube, .cone, .plane:
        return defGeom(prim, path: primPath, after: pathDepth)
      case .distantLight, .diskLight, .rectLight, .sphereLight, .cylinderLight, .geometryLight, .domeLight, .portalLight:
        return defLux(prim, path: primPath, after: pathDepth)
      case let .token(type):
        return stage.definePrim(pathDepth.append(path: primPath), type: type)
      default:
        return stage.definePrim(pathDepth.append(path: primPath))
    }
  }

  /**
   * Private internal function to allow declaratively defining Pixar.UsdGeom schema types. */
  private func defGeom(_ prim: UsdPrim, path: Pixar.Sdf.Path, after pathDepth: Pixar.Sdf.Path) -> Pixar.Usd.Prim
  {
    switch prim.type
    {
      case .xform:
        Pixar.UsdGeom.Xform.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .sphere:
        Pixar.UsdGeom.Sphere.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .capsule:
        Pixar.UsdGeom.Capsule.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cylinder:
        Pixar.UsdGeom.Cylinder.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cube:
        Pixar.UsdGeom.Cube.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cone:
        Pixar.UsdGeom.Cone.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .plane:
        Pixar.UsdGeom.Plane.define(stage, path: pathDepth.append(path: path)).GetPrim()
      default:
        stage.definePrim(pathDepth.append(path: path))
    }
  }

  /**
   * Private internal function to allow declaratively defining Pixar.UsdLux schema types. */
  private func defLux(_ prim: UsdPrim, path: Pixar.Sdf.Path, after pathDepth: Pixar.Sdf.Path) -> Pixar.Usd.Prim
  {
    switch prim.type
    {
      case .distantLight:
        Pixar.UsdLux.DistantLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .diskLight:
        Pixar.UsdLux.DiskLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .rectLight:
        Pixar.UsdLux.RectLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .sphereLight:
        Pixar.UsdLux.SphereLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cylinderLight:
        Pixar.UsdLux.CylinderLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .geometryLight:
        Pixar.UsdLux.GeometryLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .domeLight:
        Pixar.UsdLux.DomeLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .portalLight:
        Pixar.UsdLux.PortalLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      default:
        stage.definePrim(pathDepth.append(path: path))
    }
  }
}
