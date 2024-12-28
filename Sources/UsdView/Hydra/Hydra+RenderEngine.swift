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

public enum Hydra
{
  public class RenderEngine
  {
    public var stage: UsdStageRefPtr
    public var engine: UsdImagingGL.EngineSharedPtr

    public required init(stage: UsdStageRefPtr)
    {
      self.stage = stage
      engine = UsdImagingGL.Engine.createEngine()
    }

    public func render()
    {
      var params = UsdImagingGL.RenderParams()
      params.frame = Usd.TimeCode.Default()
      params.clearColor = .init(0.1, 0.1, 0.1, 1.0)
      params.enableIdRender = false
      params.showGuides = false
      params.showRender = true
      params.showProxy = false

      engine.render(root: stage.getPseudoRoot(), params: params)
    }
  }
}
