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
import Sdf

public typealias SdfLayer = Pixar.SdfLayer
public typealias SdfLayerHandle = Pixar.SdfLayerHandle

public extension Sdf
{
  typealias Layer = SdfLayer
  typealias LayerHandle = SdfLayerHandle
}

public extension SdfLayerHandle
{
  /**
   * Sets the documentation string for this layer. */
  func set(doc: String)
  {
    pointee.SetDocumentation(std.string(doc))
  }

  /**
   * Returns `true` if successful, `false` if an error occurred.
   * Returns `false` if the layer has no remembered file name or the
   * layer type cannot be saved. The layer will not be overwritten if the
   * file exists and the layer is not dirty unless `force` is true. */
  func save(force: Bool = false)
  {
    pointee.Save(force)
  }

  /**
   * Reloads the layer from its persistent representation.
   *
   * This restores the layer to a state as if it had just been created
   * with ``SdfLayer/findOrOpen()``. This operation is undoable.
   *
   * The fileName and whether journaling is enabled are not affected
   * by this method.
   *
   * When called with force = false (the default), Reload attempts to
   * avoid reloading layers that have not changed on disk. It does so
   * by comparing the file's modification time (mtime) to when the
   * file was loaded. If the layer has unsaved modifications, this
   * mechanism is not used, and the layer is reloaded from disk. If the
   * layer has any ``SdfLayer/getExternalAssetDependencies()`` "external
   * asset dependencies", their modification state will also be consulted
   * when determining if the layer needs to be reloaded.
   *
   * Passing true to the `force` parameter overrides this behavior, forcing
   * the layer to be reloaded from disk regardless of whether it has changed. */
  func reload(force: Bool = false)
  {
    pointee.Reload(force)
  }
}
