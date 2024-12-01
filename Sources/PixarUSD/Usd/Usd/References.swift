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

public typealias UsdReferences = Pixar.UsdReferences

public extension Usd
{
  typealias References = UsdReferences
}

public extension Usd.References
{
  @discardableResult
  mutating func addReference(_ ref: Sdf.Reference, position: Pixar.UsdListPosition = .backOfPrependList) -> Bool
  {
    AddReference(ref, position)
  }

  @discardableResult
  mutating func addReference(assetPath: String,
                             primPath: Sdf.Path,
                             layerOffset: Sdf.LayerOffset = Sdf.LayerOffset(),
                             position: Pixar.UsdListPosition = .backOfPrependList) -> Bool
  {
    AddReference(std.string(assetPath), primPath, layerOffset, position)
  }

  @discardableResult
  mutating func addReference(assetPath: String,
                             layerOffset: Sdf.LayerOffset = Sdf.LayerOffset(),
                             position: Pixar.UsdListPosition = .backOfPrependList) -> Bool
  {
    AddReference(std.string(assetPath), layerOffset, position)
  }
}
