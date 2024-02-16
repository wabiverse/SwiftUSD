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

import CxxStdlib
import Foundation
import Sdf
import Usd

public typealias UsdStageRefPtr = Pixar.UsdStageRefPtr

public extension Usd
{
  /**
   * # ``Stage``
   *
   * The outermost container for scene description, which owns and presents
   * composed prims as a scenegraph, following the composition recipe recursively
   * described in its associated "root layer".
   *
   * USD derives its persistent-storage scalability by combining and reusing simple
   * compositions into richer aggregates using referencing and layering with sparse
   * overrides. Ultimately, every composition (i.e. "scene") is identifiable by its
   * root layer, i.e. the `.usd` file, and a scene is instantiated in an application
   * on a Stage that presents a composed view of the scene's root layer. Each simple
   * composition referenced into a larger composition could be presented on its own
   * ``Stage``, at the same (or not) time that it is participating in the
   * larger composition on its own Stage; all of the underlying layers will be shared
   * by the two stages, while each maintains its own scenegraph of composed prims.
   *
   * A UsdStage has sole ownership over the ``Prim``'s with which it is
   * populated, and retains *shared* ownership (with other stages and direct clients
   * of ``PixarUSD/__ObjC/Pixar/Sdf/Layer``'s, via the ``PixarUSD/__ObjC/Pixar/Sdf/LayerRegistry``
   * that underlies all ``PixarUSD/__ObjC/Pixar/Sdf/Layer`` creation methods) of layers.
   *
   * It provides roughly five categories of API that address different aspects of scene
   * management:
   *
   * - "Stage lifetime management" methods for constructing and initially populating a
   * UsdStage from an existing layer file, or one that will be created as a result, in
   * memory or on the filesystem.
   * - "Load/unload working set management" methods that allow you to specify which
   * ``Payload``s should be included and excluded from the stage's composition.
   * - "Variant management" methods to manage policy for which variant to use when
   * composing prims that provide a named variant set, but do not specify a selection.
   * - "Prim access, creation, and mutation" methods that allow you to find, create, or
   * remove a prim identified by a path on
   * the stage. This group also provides methods for efficiently traversing the prims
   * on the stage.
   * - "Layers and EditTargets" methods provide access to the layers in the stage's
   * **root LayerStack** (i.e. the root layer and all of its recursive sublayers),
   * and the ability to set a ``EditTarget`` into which all subsequent
   * mutations to objects associated with the stage (e.g. prims, properties, etc)
   * will go.
   * - "Serialization" methods for "flattening" a composition (to varying degrees),
   * and exporting a completely flattened view of the stage to a string or file.
   * These methods can be very useful for targeted asset optimization and debugging,
   * though care should be exercized with large scenes, as flattening defeats some
   * of the benefits of referenced scene description, and may produce some very large
   * results, especially in file formats that do not support data de-duplication, like
   * the usda text format!
   *
   * ### Stage Session Layers
   *
   * Each ``Stage`` can possess an optional "session layer". The purpose
   * of a session layer is to hold ephemeral edits that modify a UsdStage's contents
   * or behavior in a way that is useful to the client, but should not be considered
   * as permanent mutations to be recorded upon export. A very common use of session
   * layers is to make variant selections, to pick a specific LOD or shading variation,
   * for example. The session layer is also frequently used to override the visibility
   * of geometry and assets in the scene. A session layer, if present, contributes to a
   * ``Stage``'s identity, for purposes of stage-caching, etc.
   *
   * To edit content in a session layer, get the layer's edit target using
   * `stage.getEditTarget(for: .localLayer, stage.getSessionLayer())` and
   * set that target in the stage by calling `setEditTarget()` or creating
   * a ``UsdEditContext``. */
  typealias Stage = Pixar.UsdStage
  typealias StageRefPtr = Pixar.UsdStageRefPtr
}

public extension Usd.Stage
{
  var scene: [Usd.Prim]
  {
    getPrims()
  }

  func getPrims() -> [Usd.Prim]
  {
    let it = Usd.PrimRange.Stage(getPtr())

    return IteratorSequence(it).map { $0 }
  }

  enum InitialLoadingSet
  {
    case all
    case none

    public var rawValue: InitialLoadSet
    {
      switch self
      {
        case .all: InitialLoadSet.LoadAll
        case .none: InitialLoadSet.LoadNone
      }
    }
  }

  @discardableResult
  static func createNew(_ identifier: String, ext: UsdStage.FileExt, load: InitialLoadingSet = .all) -> UsdStageRefPtr
  {
    Usd.Stage.CreateNew(std.string("\(identifier).\(ext.rawValue)"), load.rawValue)
  }

  @discardableResult
  static func createNew(_ identifier: String, load: InitialLoadingSet = .all) -> UsdStageRefPtr
  {
    Usd.Stage.CreateNew(std.string(identifier), load.rawValue)
  }

  @discardableResult
  static func open(_ filePath: String, load: InitialLoadingSet = .all) -> UsdStageRefPtr
  {
    Usd.Stage.Open(std.string(filePath), load.rawValue)
  }
}

public extension Usd.StageRefPtr
{
  var scene: [Usd.Prim]
  {
    pointee.scene
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
  func traverse() -> Usd.PrimRange
  {
    pointee.Traverse()
  }

  /**
   * Attempt to ensure a UsdPrim at path is defined (according to Usd.Prim.isDefined()) on this stage.
   *
   * If a prim at path is already defined on this stage and typeName is empty or equal to the existing prim's typeName,
   * return that prim. Otherwise, author an SdfPrimSpec with **specifier** == `Sdf.SpecifierDef` and typeName for
   * the prim at **path** at the current EditTarget. Lastly, author `Sdf.PrimSpec`s with the **specifier** set equal
   * to `Sdf.SpecifierDef` and an empty typeName at the current **edit target** for any nonexistent, or existing but
   * not Defined ancestors.
   *
   * The given path must be an absolute prim path that does not contain any variant selections. If it is impossible to author
   * any of the necessary `Sdf.PrimSpec`s (for example, in case path cannot map to the current UsdEditTarget's namespace
   * or one of the ancestors of path is inactive on the UsdStage), issue an error and return an invalid ``Usd.Prim``.
   *
   * > Note: This method may return a defined prim whose **type name** does not match the supplied **type name**,
   *   in case a stronger **type name** opinion overrides the opinion at the current **edit target**. */
  @discardableResult
  func definePrim(_ path: Sdf.Path, type name: Tf.Token = Tf.Token()) -> Usd.Prim
  {
    pointee.DefinePrim(path, name)
  }

  /**
   * Attempt to ensure a UsdPrim at path is defined (according to UsdPrim::IsDefined()) on this stage.
   *
   * If a prim at path is already defined on this stage and typeName is empty or equal to the existing prim's typeName,
   * return that prim. Otherwise, author an SdfPrimSpec with **specifier** == `Sdf.SpecifierDef` and typeName for
   * the prim at **path** at the current EditTarget. Lastly, author `Sdf.PrimSpec`s with the **specifier** set equal
   * to `Sdf.SpecifierDef` and an empty typeName at the current **edit target** for any nonexistent, or existing but
   * not Defined ancestors.
   *
   * The given path must be an absolute prim path that does not contain any variant selections. If it is impossible to author
   * any of the necessary `Sdf.PrimSpec`s (for example, in case path cannot map to the current UsdEditTarget's namespace
   * or one of the ancestors of path is inactive on the UsdStage), issue an error and return an invalid ``Usd.Prim``.
   *
   * > [!NOTE]
   * > This method may return a defined prim whose **type name** does not match the supplied **type name**,
   * > in case a stronger **type name** opinion overrides the opinion at the current **edit target**. */
  @discardableResult
  func definePrim(_ path: String, type name: Tf.Token = Tf.Token()) -> Usd.Prim
  {
    pointee.DefinePrim(.init(path), name)
  }

  func getPrim(at path: Sdf.Path) -> Usd.Prim
  {
    pointee.GetPrimAtPath(path)
  }

  func getPrim(at path: String) -> Usd.Prim
  {
    pointee.GetPrimAtPath(Sdf.Path(path))
  }

  func overridePrim(path: Sdf.Path) -> Usd.Prim
  {
    pointee.OverridePrim(path)
  }

  func overridePrim(path: String) -> Usd.Prim
  {
    pointee.OverridePrim(Sdf.Path(path))
  }

  /**
   * Return this stage's root layer. */
  func getRootLayer() -> SdfLayerHandle
  {
    pointee.GetRootLayer()
  }

  /**
   * Return this stage's root layer. */
  func getPseudoRoot() -> Usd.Prim
  {
    pointee.GetPseudoRoot()
  }

  /**
   * Save all dirty layers contributing to this stage.
   *
   * Calls ``Sdf.Layer.save()`` on all dirty layers contributing to this stage
   * except session layers and sublayers of session layers. This function will emit a
   * warning and skip each dirty anonymous layer it encounters, since anonymous layers
   * cannot be saved with ``Sdf.Layer.save()``. These layers must be manually
   * exported by calling ``Sdf.Layer.export()``. */
  func save()
  {
    pointee.Save()
  }
}
