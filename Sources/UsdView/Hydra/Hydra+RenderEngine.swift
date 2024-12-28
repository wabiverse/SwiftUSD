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

    private let hgi: Pixar.HgiMetalPtr
    private let engine: UsdImagingGL.EngineSharedPtr

    public required init(stage: UsdStageRefPtr)
    {
      self.stage = stage

      hgi = HgiMetal.createHgi()
      let driver = HdDriver(name: .renderDriver, driver: hgi.value)

      engine = UsdImagingGL.Engine.createEngine(
        rootPath: stage.getPseudoRoot().getPath(),
        excludedPaths: Sdf.PathVector(),
        invisedPaths: Sdf.PathVector(),
        sceneDelegateId: Sdf.Path.absoluteRootPath(),
        driver: driver
      )
    }

    public func render(rgba: (Double, Double, Double, Double))
    {
      var params = UsdImagingGL.RenderParams()

      params.frame = Usd.TimeCode.Default()
      params.clearColor = .init(Float(rgba.0), Float(rgba.1), Float(rgba.2), Float(rgba.3))
      params.enableIdRender = false
      params.showGuides = false
      params.showRender = true
      params.showProxy = false

      engine.render(root: stage.getPseudoRoot(), params: params)
    }
  }
}
