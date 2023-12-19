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

public typealias StageRefPtr = Pixar.UsdStageRefPtr

public extension Pixar.Usd
{
  /**
   * # Pixar.Usd.Stage
   *
   * The outermost container for scene description, which owns and presents
   * composed prims as a scenegraph, following the composition recipe recursively
   * described in its associated "root layer".
   *
   * USD derives its persistent-storage scalability by combining and reusing simple
   * compositions into richer aggregates using referencing and layering with sparse
   * overrides. Ultimately, every composition (i.e. "scene") is identifiable by its
   * root layer, i.e. the `.usd` file, and a scene is instantiated in an application
   * on a UsdStage that presents a composed view of the scene's root layer. Each simple
   * composition referenced into a larger composition could be presented on its own
   * ``UsdStage``, at the same (or not) time that it is participating in the larger
   * composition on its own UsdStage; all of the underlying layers will be shared by
   * the two stages, while each maintains its own scenegraph of composed prims.
   *
   * A UsdStage has sole ownership over the UsdPrim 's with which it is populated, and
   * retains *shared* ownership (with other stages and direct clients of SdfLayer's, via
   * the ``Sdf/LayerRegistry`` that underlies all ``SdfLayer`` creation methods) of layers.
   *
   * It provides roughly five categories of API that address different aspects of scene
   * management:
   *
   * - "Stage lifetime management" methods for constructing and initially populating a
   * UsdStage from an existing layer file, or one that will be created as a result, in
   * memory or on the filesystem.
   * - "Load/unload working set management" methods that allow you to specify which
   * ``Payloads`` should be included and excluded from the stage's composition.
   * - "Variant management" methods to manage policy for which variant to use when
   * composing prims that provide a named variant set, but do not specify a selection.
   * - "Prim access, creation, and mutation" methods that allow you to find, create, or
   * remove a prim identified by a path on
   * the stage. This group also provides methods for efficiently traversing the prims
   * on the stage.
   * - "Layers and EditTargets" methods provide access to the layers in the stage's
   * **root LayerStack** (i.e. the root layer and all of its recursive sublayers),
   * and the ability to set a ``UsdEditTarget`` into which all subsequent mutations
   * to objects associated with the stage (e.g. prims, properties, etc) will go.
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
   * Each ``Pixar.Usd.Stage`` can possess an optional "session layer". The purpose
   * of a session layer is to hold ephemeral edits that modify a UsdStage's contents
   * or behavior in a way that is useful to the client, but should not be considered
   * as permanent mutations to be recorded upon export. A very common use of session
   * layers is to make variant selections, to pick a specific LOD or shading variation,
   * for example. The session layer is also frequently used to override the visibility
   * of geometry and assets in the scene. A session layer, if present, contributes to a
   * ``Pixar.Usd.Stage``'s identity, for purposes of stage-caching, etc.
   *
   * To edit content in a session layer, get the layer's edit target using
   * `stage.getEditTarget(for: .localLayer, stage.getSessionLayer())` and
   * set that target in the stage by calling `setEditTarget()` or creating
   * a ``UsdEditContext``. */
  typealias Stage = Pixar.UsdStage
}

public extension Pixar.Usd.Stage
{
  static func createNew(_ identifier: String, load: InitialLoadingSet = .all) -> StageRefPtr
  {
    Pixar.UsdStage.CreateNew(std.string(identifier), load.rawValue)
  }
}
