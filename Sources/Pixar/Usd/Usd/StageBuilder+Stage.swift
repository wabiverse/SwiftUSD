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
      case .xform:
        return Pixar.UsdGeom.Xform.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .sphere:
        return Pixar.UsdGeom.Sphere.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .capsule:
        return Pixar.UsdGeom.Capsule.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .cylinder:
        return Pixar.UsdGeom.Cylinder.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .cube:
        return Pixar.UsdGeom.Cube.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .cone:
        return Pixar.UsdGeom.Cone.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .plane:
        return Pixar.UsdGeom.Plane.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .distantLight:
        return Pixar.UsdLux.DistantLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .diskLight:
        return Pixar.UsdLux.DiskLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .rectLight:
        return Pixar.UsdLux.RectLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .sphereLight:
        return Pixar.UsdLux.SphereLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .cylinderLight:
        return Pixar.UsdLux.CylinderLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .geometryLight:
        return Pixar.UsdLux.GeometryLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .domeLight:
        return Pixar.UsdLux.DomeLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case .portalLight:
        return Pixar.UsdLux.PortalLight.define(stage, path: pathDepth.append(path: primPath)).GetPrim()
      case let .token(type):
        return stage.definePrim(pathDepth.append(path: primPath), type: type)
      default:
        return stage.definePrim(pathDepth.append(path: primPath))
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
