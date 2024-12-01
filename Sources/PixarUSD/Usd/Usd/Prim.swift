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

import CxxStdlib
import Foundation
import Usd

public typealias UsdStageWeakPtr = Pixar.UsdStageWeakPtr
public typealias UsdPrim = Pixar.UsdPrim

public extension Usd
{
  /**
   * # Usd.Prim
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
   * - ``__ObjC/Pixar/TfRefPtr<UsdStage>/getPrim(at:)-1jtte``
   * - ``__ObjC/Pixar/TfRefPtr<UsdStage>/overridePrim(path:)-3liu9``
   * - ``__ObjC/Pixar/TfRefPtr<UsdStage>/definePrim(_:type:)-19ehc``
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
   * ``__ObjC/Pixar/TfRefPtr<UsdStage>/getPrim(at:)-1jtte``,
   * which will never cause a mutation to the Stage or its layers.
   *
   * Please refer to ``Notice`` for a listing of the events that could cause
   * ``Notice/objectsChanged`` to be emitted.
   */
  typealias Prim = UsdPrim
  typealias StageWeakPtr = UsdStageWeakPtr
}

extension Usd.Prim: Prim
{
  /**
   * Sets the documentation string for this layer. */
  public func set(doc: String)
  {
    SetDocumentation(std.string(doc))
  }

  public func set(active: Bool)
  {
    SetActive(active)
  }

  public func getStage() -> UsdStageWeakPtr
  {
    GetStage()
  }

  public func getPath() -> Sdf.Path
  {
    GetPath()
  }

  public func getReferences() -> Usd.References
  {
    GetReferences()
  }

  private borrowing func GetNameCopy() -> Tf.Token
  {
    __GetNameUnsafe().pointee
  }

  private borrowing func GetTypeNameCopy() -> Tf.Token
  {
    __GetTypeNameUnsafe().pointee
  }

  public var path: Sdf.Path
  {
    GetPath()
  }

  public var name: Tf.Token
  {
    GetNameCopy()
  }

  public var typeName: Tf.Token
  {
    get { GetTypeNameCopy() }
    set { SetTypeName(newValue) }
  }

  public var children: [any Prim]
  {
    IteratorSequence(GetChildren()).map { $0 }
  }
}
