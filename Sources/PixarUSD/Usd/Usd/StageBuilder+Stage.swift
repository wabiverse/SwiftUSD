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
 * USDStage("HelloWorldExample", ext: .usda)
 * {
 *   USDPrim("Hello", type: .xform)
 *   {
 *     USDPrim("World", type: .sphere)
 *   }
 * }
 * ``` */
public struct USDStage
{
  public var stage: UsdStageRefPtr
  public var prims: [USDPrim]

  public init(_ identifier: String,
              ext: USDStage.FileExt = .custom(""),
              load set: Usd.Stage.InitialLoadingSet = .all,
              @StageBuilder prims: () -> [USDPrim])
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

  private mutating func populate(prims: [USDPrim])
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

  /**
   * Traverse the active, loaded, defined, non-abstract prims on this stage depth-first.
   *
   * Returns a ``Usd.PrimRange`` , which allows low-latency traversal, with the
   * ability to prune subtrees from traversal. It is python iterable, so in its simplest form,
   * one can do:
   * ```swift
   * for prim in stage.traverse()
   * {
   *   print(prim.GetPath())
   * }
   * ```
   *
   * If either a pre-and-post-order traversal or, a traversal rooted at
   * a particular prim is desired, construct a ``Usd.PrimRange``
   * directly.
   *
   * This is equivalent to ``Usd.PrimRange.stage()``. */
  // public func traverse() -> [Usd.Prim]
  // {
  //   let it = Usd.PrimRange.Stage(stage.pointee.getPtr())

  //   return IteratorSequence(it).map { $0 }
  // }

  /**
   * Sets the documentation string for this layer. */
  @discardableResult
  public func set(doc: String) -> USDStage
  {
    stage.getPseudoRoot().set(doc: doc)

    return self
  }

  /**
   * Save all dirty layers contributing to this stage.
   *
   * Calls ``Sdf.Layer.save()`` on all dirty layers contributing to this stage
   * except session layers and sublayers of session layers. This function will emit a
   * warning and skip each dirty anonymous layer it encounters, since anonymous layers
   * cannot be saved with ``Sdf.Layer.save()``. These layers must be manually
   * exported by calling ``Sdf.Layer.export()``. */
  @discardableResult
  public func save() -> USDStage
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
    public static var allCases: [USDStage.FileExt]
    {
      [.usd, .usda, .usdc, .usdz]
    }
  }
}

/*
 * ------------------------------------------------------------------------------
 * Private USDStage extensions to allow users to declaratively define prim types.
 * --- */

public extension USDStage
{
  /**
   * Private internal function to allow declaratively defining prim schema types. */
  @discardableResult
  private func define(prim: USDPrim, after primStack: [USDPrim]) -> Usd.Prim
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
  private func defGeom(_ prim: USDPrim, path: Sdf.Path, after pathDepth: Sdf.Path) -> Usd.Prim
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
  private func defLux(_ prim: USDPrim, path: Sdf.Path, after pathDepth: Sdf.Path) -> Usd.Prim
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
