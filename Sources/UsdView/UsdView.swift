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
import SwiftCrossUI

/**
 * ``UsdView``
 *
 * ## Overview
 *
 * A ``UsdView`` application written in Swift for
 * the purposes of demonstrating the usage of USD,
 * from the Swift programming language. */
@main
struct UsdView: App
{
  typealias Backend = PlatformBackend

  /// the active usd stage.
  let stage: UsdStageRefPtr
  /// the hydra rendering engine.
  let engine: Hydra.RenderEngine

  public init()
  {
    // register all usd plugins & resources.
    Pixar.Bundler.shared.setup(.resources)

    // create a new usd stage.
    stage = UsdView.createScene()

    // setup hydra to render the usd stage.
    engine = Hydra.RenderEngine(stage: stage)

    Msg.logger.log(level: .info, "UsdView launched | USD v\(Pixar.version).")
  }

  var body: some Scene
  {
    WindowGroup("UsdView")
    {
      Hydra.Viewport(engine: engine)
    }
  }
}
