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
#if canImport(Sdf)
  import Sdf
#else
  import OpenUSD
#endif

public typealias SdfReference = Pixar.SdfReference

public extension Sdf
{
  typealias Reference = SdfReference
}

public extension Sdf.Reference
{
  init(assetPath: String = "",
       primPath: Sdf.Path = Sdf.Path(),
       layerOffset: Sdf.LayerOffset = Sdf.LayerOffset(),
       customData: Vt.Dictionary = Vt.Dictionary())
  {
    self = assetPath.withCString { Overlay.MakeReference($0, primPath, layerOffset, customData) }
  }
}
