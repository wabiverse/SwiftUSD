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

#if canImport(SwiftUI)
  import SwiftUI
  public protocol PixarApp: App
  {}
#else
  public protocol PixarApp
  {}
#endif

/**
 * ``UsdView``
 *
 * ## Overview
 *
 * A ``UsdView`` application written in Swift for
 * the purposes of demonstrating the usage of USD,
 * from the Swift programming language. */
@main
struct UsdView: PixarApp
{
  /// the active usd stage.
  let stage: UsdStageRefPtr
  /// the hydra rendering engine.
  let hydra: Hydra.RenderEngine

  public init()
  {
    // register all usd plugins & resources.
    registerPlugins()

    // create a new usd stage.
    stage = Usd.Stage.createNew("\(documentsDirPath())/HelloPixarUSD", ext: .usda)

    // setup hydra to render the usd stage.
    hydra = Hydra.RenderEngine(stage: stage)

    runDemo()
  }

  #if canImport(SwiftUI)
    var body: some Scene
    {
      WindowGroup("UsdView", id: "usdview")
      {
        VStack
        {
          Text("UsdView Under Construction...")
            .font(.system(size: 24, weight: .black))
            .padding()
        }
      }
    }
  #else
    static func main()
    {
      let app = UsdView()
    }
  #endif

  func runDemo()
  {
    // show hydra gpu info.
    hydra.info()

    // create usd scene.
    createScene()

    // declarative usd scene
    // (using swiftui-like api).
    declareScene()

    Msg.logger.log(level: .info, "UsdView launched | USD v\(Pixar.version).")

    // complete.
  }
}
