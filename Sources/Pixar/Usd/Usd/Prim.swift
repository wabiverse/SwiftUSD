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

public extension Pixar.Usd
{
  /**
   * # Pixar.Usd.Prim
   *
   * ``Usd.Prim`` is the sole persistent scenegraph object on a UsdStage, and
   * is the embodiment of a "Prim" as described in the *Universal Scene
   * Description Composition Compendium*.
   *
   * A ``Usd.Prim`` is the principal container of other types of scene description.
   * It provides API for accessing and creating all of the contained kinds of scene
   * description, which include:
   * - ``Usd.VariantSets`` - all VariantSets on the prim (`getVariantSets()`, `getVariantSet()`).
   * - ``Usd.References`` - all references on the prim (`getReferences()`).
   * - ``Usd.Inherits`` - all inherits on the prim (`getInherits()`).
   * - ``Usd.Specializes`` - all specializes on the prim (`getSpecializes()`).
   *
   * As well as access to the API objects for properties contained within the
   * prim - ``Usd.Prim`` as well as all of the following classes are subclasses
   * of ``Usd.Object``:
   * - ``Usd.Property`` - generic access to all attributes and relationships.
   * A ``Usd.Property`` can be queried and cast to a ``Usd.Attribute`` or
   * - ``Usd.Relationship`` using ``Usd.Object.is<T>(T.self)`` and ``Usd.Object.as<T>(T.self)``.
   * (getPropertyNames(), getProperties(), getPropertiesInNamespace(), getPropertyOrder(), setPropertyOrder()).
   * - ``Usd.Attribute`` - access to default and timesampled attribute values, as well as value resolution information,
   * and attribute-specific metadata (createAttribute(), getAttribute(), getAttributes(), hasAttribute()).
   * - ``Usd.Relationship`` - access to authoring and resolving relationships to other prims and properties
   * (createRelationship(), getRelationship(), getRelationships(), hasRelationship()).
   *
   * ``Usd.Prim`` also provides access to iteration through its prim children,
   * optionally making use of the **Prim Predicates Facility** (getChildren(),
   * getAllChildren(), getFilteredChildren()).
   *
   * ### Lifetime Management
   *
   * Clients acquire UsdPrim objects, which act like weak/guarded pointers
   * to persistent objects owned and managed by their originating UsdStage.
   * We provide the following guarantees for a UsdPrim acquired via
   * ``Pixar.Usd.Stage.getPrimAtPath()`` or ``Pixar.Usd.Stage.overridePrim()``
   * or ``Pixar.Usd.Stage.definePrim()``:
   * - As long as no further mutations to the structure of the UsdStage
   * are made, the UsdPrim will still be valid. Loading and unloading are
   * considered structural mutations.
   * - When the ``Usd.Stage``'s structure is **mutated**, the thread performing
   * the mutation will receive a ``UsdNotice.objectsChanged`` notice after the
   * stage has been reconfigured, which provides details as to what prims may
   * have been created or destroyed, and what prims may simply have changed in
   * some structural way.
   *
   * Prim access in "reader" threads should be limited to ``getPrimAtPath()``, which
   * will never cause a mutation to the Stage or its layers.
   *
   * Please refer to ``Pixar.Usd.Notice`` for a listing of
   * the events that could cause ``Usd.Notice.objectsChanged``
   * to be emitted.
   */
  typealias Prim = Pixar.UsdPrim
}
