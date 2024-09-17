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
import PixarUSD

public extension Hydra
{
  /**
   * ``NORenderer``
   *
   * ## Overview
   *
   * The Hydra Engine (``Hd``) no-op renderer for the ``UsdView``
   * application. Note: This renders nothing. */
  class NORenderer: HdRenderEngine
  {
    public var stage: UsdStageRefPtr

    public required init(stage: UsdStageRefPtr)
    {
      self.stage = stage
    }

    public func info()
    {
      Msg.logger.log(level: .info, "Created HGI -> None.")
    }

    public func draw()
    {}
  }
}
