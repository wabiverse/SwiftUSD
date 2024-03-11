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

/// A protocol for the versioned USD API.
public protocol VersionedUsd
{
  /// The Pixar USD v0.23 C++ API.
  associatedtype v23

  /// The current version of ``PixarUSD``.
  static var version: String { get }
}

/// Represents all USD modules which
/// make up the foundational base of
/// the Pixar USD API.
public protocol PxrBase
{
  associatedtype Arch
  associatedtype Gf
  associatedtype Js
  associatedtype Plug
  associatedtype Tf
  associatedtype Trace
  associatedtype Vt
  associatedtype Work
}

/// Represents all USD modules which
/// make up the main scene description
/// and composition API of Pixar USD.
public protocol PxrUsd
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
   * of ``Sdf/Layer``'s, via the ``Sdf/LayerRegistry``
   * that underlies all ``Sdf/Layer`` creation methods) of layers.
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
  associatedtype Stage

  associatedtype StageWeakPtr
  associatedtype StageRefPtr

  /**
   * # ``Prim``
   *
   * ``Prim`` is the sole persistent scenegraph object on a UsdStage, and
   * is the embodiment of a "Prim" as described in the *Universal Scene
   * Description Composition Compendium*.
   *
   * A ``Prim`` is the principal container of other types of scene description.
   * It provides API for accessing and creating all of the contained kinds of scene
   * description, which include:
   * - ``VariantSets`` - all VariantSets on the prim (`getVariantSets()`, `getVariantSet()`).
   * - ``References`` - all references on the prim (`getReferences()`).
   * - ``Inherits`` - all inherits on the prim (`getInherits()`).
   * - ``Specializes`` - all specializes on the prim (`getSpecializes()`).
   *
   * As well as access to the API objects for properties contained within the prim - ``Prim``
   * as well as all of the following classes are subclasses of ``Object``:
   * - ``Property`` - generic access to all attributes and relationships.
   * A ``Property`` can be queried and cast to a ``Usd.Attribute`` or
   * - ``Relationship`` using ``Object/is<T>(a: T.self)`` and ``Object/as<T>(T.self)``.
   * (getPropertyNames(), getProperties(), getPropertiesInNamespace(), getPropertyOrder(), setPropertyOrder()).
   * - ``Attribute`` - access to default and timesampled attribute values, as well as value resolution information,
   * and attribute-specific metadata (createAttribute(), getAttribute(), getAttributes(), hasAttribute()).
   * - ``Relationship`` - access to authoring and resolving relationships to other prims and properties
   * (createRelationship(), getRelationship(), getRelationships(), hasRelationship()).
   *
   * ``Prim`` also provides access to iteration through its prim children,
   * optionally making use of the **Prim Predicates Facility** (getChildren(),
   * getAllChildren(), getFilteredChildren()).
   *
   * ### Lifetime Management
   *
   * Clients acquire UsdPrim objects, which act like weak/guarded pointers
   * to persistent objects owned and managed by their originating UsdStage.
   *
   * We provide the following guarantees for a UsdPrim acquired via any of
   * the following:
   *
   * - ``__ObjC/pxr/TfRefPtr<UsdStage>/getPrim(at:)-1jtte``
   * - ``__ObjC/pxr/TfRefPtr<UsdStage>/overridePrim(path:)-3liu9``
   * - ``__ObjC/pxr/TfRefPtr<UsdStage>/definePrim(_:type:)-19ehc``
   *
   *   - As long as no further mutations to the structure of the UsdStage
   *   are made, the UsdPrim will still be valid. Loading and unloading are
   *   considered structural mutations.
   *
   *   - When the ``Stage``'s structure is **mutated**, the thread performing
   *   the mutation will receive a ``Notice/objectsChanged`` notice after the
   *   stage has been reconfigured, which provides details as to what prims may
   *   have been created or destroyed, and what prims may simply have changed in
   *   some structural way.
   *
   * Prim access in "reader" threads should be limited to
   * ``__ObjC/pxr/TfRefPtr<UsdStage>/getPrim(at:)-1jtte``,
   * which will never cause a mutation to the Stage or its layers.
   *
   * Please refer to ``Notice`` for a listing of the events that could cause
   * ``Notice/objectsChanged`` to be emitted.
   */
  associatedtype Prim

  associatedtype Ar
  associatedtype Kind
  associatedtype Ndr
  associatedtype Pcp
  associatedtype Sdf
  associatedtype Sdr
  associatedtype SdrOsl
  associatedtype UsdAbc
  associatedtype UsdDraco
  associatedtype UsdHydra
  associatedtype UsdLux
  associatedtype UsdMedia
  associatedtype UsdMtlx
  associatedtype UsdPhysics
  associatedtype UsdProc
  associatedtype UsdRender
  associatedtype UsdRi
  associatedtype UsdShade
  associatedtype UsdSkel
  associatedtype UsdUI
  associatedtype UsdUtils
  associatedtype UsdVol
}

public protocol PxrUsdGeom
{
  associatedtype BasisCurves
  associatedtype Camera
  associatedtype Capsule
  associatedtype Cone
  associatedtype Cube
  associatedtype Cylinder
  associatedtype Tokens
  associatedtype Mesh
  associatedtype NurbsCurves
  associatedtype NurbsPatch
  associatedtype Plane
  associatedtype Points
  associatedtype Sphere
  associatedtype Subset
  associatedtype Xform
  associatedtype Xformable
  associatedtype XformOp
}

/// Represents all USD modules which
/// make up the graphics and rendering
/// foundation of Pixar USD.
public protocol PxrImaging
{
  associatedtype CameraUtil
  associatedtype Garch
  associatedtype Hd
  associatedtype Hf
  associatedtype Hgi
  associatedtype HgiGL
  associatedtype HgiInterop
  associatedtype PxOsd

  #if WITH_METAL
    associatedtype HgiMetal
  #endif
}

/// Represents all USD modules which make up the
/// main API for graphics DCC apps and tools that
/// view and/or record images (including streaming
/// playback) of ``Usd/Stage``s.
public protocol PxrUsdImaging
{
  associatedtype UsdShaders
}
