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

import Foundation
import Sdf
import Usd

/**
 * A ``Usd/Stage`` for declaratively authoring scene description.
 *
 * This api is currently experimental and will evolve overtime, its
 * purpose is to declaratively author scene description in a design
 * pattern that is similiar to that of SwiftUI, while ensuring that
 * the full range and extensibility of Pixar's USD API is preserved
 * within a innovative, exceptionally simple and highly expressible
 * way to author scene description using UsdPrim building blocks to
 * compose a scenegraph that are owned & presented by the outermost
 * UsdStage that contains them.
 *
 * Usage example:
 * ```swift
 * UsdStage("HelloWorldExample", ext: .usda)
 * {
 *   UsdPrim("Hello", type: .xform)
 *   {
 *     UsdPrim("World", type: .sphere)
 *   }
 * }
 * ``` */
public struct UsdStage
{
  public var stage: UsdStageRefPtr
  public var prims: [UsdPrim]

  public init(_ identifier: String,
              ext: UsdStage.FileExt = .custom(""),
              load set: Usd.Stage.InitialLoadingSet = .all,
              @StageBuilder prims: () -> [UsdPrim])
  {
    switch ext
    {
      case let .custom(customExt):
        if customExt.isEmpty
        {
          stage = Usd.Stage.createNew(identifier, load: set)
        }
        else if customExt.first == "."
        {
          stage = Usd.Stage.createNew("\(identifier)\(customExt)", load: set)
        }
        else
        {
          stage = Usd.Stage.createNew("\(identifier).\(customExt)", load: set)
        }
      default:
        stage = Usd.Stage.createNew("\(identifier).\(ext.rawValue)", load: set)
    }

    self.prims = []
    populate(prims: prims())
  }

  private mutating func populate(prims: [UsdPrim])
  {
    for prim in prims
    {
      define(prim: prim, after: self.prims)

      /* Step into this prims scope. */
      if prim == prims.first
      {
        self.prims.append(prim)
      }

      /* Recursively populate children. */
      populate(prims: prim.children)

      /* Step out of this prims scope. */
      if self.prims.contains(prim)
      {
        self.prims.removeAll(where: { $0 == prim })
      }
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

  private func getPrims() -> [Usd.Prim]
  {
    let it = Usd.PrimRange.Stage(stage.pointee.getPtr())

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
  public enum FileExt: CaseIterable
  {
    /// The (.usd) file extension.
    case usd

    /// The (.usda) file extension.
    case usda

    /// The (.usdc) file extension.
    case usdc

    /// The (.usdz) file extension.
    case usdz

    /// Custom file extension, accepts dot prefixed or not.
    case custom(String)

    /// The raw string value of this file extension.
    public var rawValue: String
    {
      switch self
      {
        case .usd:
          "usd"
        case .usda:
          "usda"
        case .usdc:
          "usdc"
        case .usdz:
          "usdz"
        case let .custom(ext):
          ext
      }
    }

    /// All cases of the FileExt enum.
    public static var allCases: [UsdStage.FileExt]
    {
      [.usd, .usda, .usdc, .usdz]
    }
  }
}

/*
 * ------------------------------------------------------------------------------
 * Private UsdStage extensions to allow users to declaratively define prim types.
 * --- */

public extension UsdStage
{
  /**
   * Private internal function to allow declaratively defining prim schema types. */
  @discardableResult
  private func define(prim: UsdPrim, after primStack: [UsdPrim]) -> Usd.Prim
  {
    let primPath: SdfPath = .init(prim.path.string.replacingOccurrences(of: "/", with: ""))

    let pathDepth = primStack.reduce(SdfPath("/"))
    { p1, p2 in
      let sdfPath: SdfPath = .init(p2.path.string.components(separatedBy: "/").last?.replacingOccurrences(of: "/", with: "") ?? "")

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
   * Private internal function to allow declaratively defining UsdGeom schema types. */
  private func defGeom(_ prim: UsdPrim, path: Sdf.Path, after pathDepth: Sdf.Path) -> Usd.Prim
  {
    switch prim.type
    {
      case .xform:
        UsdGeom.Xform.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .sphere:
        UsdGeom.Sphere.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .capsule:
        UsdGeom.Capsule.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cylinder:
        UsdGeom.Cylinder.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cube:
        UsdGeom.Cube.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cone:
        UsdGeom.Cone.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .plane:
        UsdGeom.Plane.define(stage, path: pathDepth.append(path: path)).GetPrim()
      default:
        stage.definePrim(pathDepth.append(path: path))
    }
  }

  /**
   * Private internal function to allow declaratively defining UsdLux schema types. */
  private func defLux(_ prim: UsdPrim, path: Sdf.Path, after pathDepth: Sdf.Path) -> Usd.Prim
  {
    switch prim.type
    {
      case .distantLight:
        UsdLux.DistantLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .diskLight:
        UsdLux.DiskLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .rectLight:
        UsdLux.RectLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .sphereLight:
        UsdLux.SphereLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .cylinderLight:
        UsdLux.CylinderLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .geometryLight:
        UsdLux.GeometryLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .domeLight:
        UsdLux.DomeLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      case .portalLight:
        UsdLux.PortalLight.define(stage, path: pathDepth.append(path: path)).GetPrim()
      default:
        stage.definePrim(pathDepth.append(path: path))
    }
  }
}
