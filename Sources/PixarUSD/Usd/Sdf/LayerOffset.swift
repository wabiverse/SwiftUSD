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
import Sdf

public typealias SdfLayerOffset = Pixar.SdfLayerOffset

public extension Sdf
{
  typealias LayerOffset = SdfLayerOffset
}

public extension Sdf.LayerOffset
{
  init(offset: Double = 0.0, scale: Double = 1.0)
  {
    self = Sdf.LayerOffset(offset, scale)
  }
}
