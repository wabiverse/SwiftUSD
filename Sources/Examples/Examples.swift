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

@main
enum USDExamples
{
  static func main()
  {
    Msg.logger.info("launched test program 'USDExamples'.")

    /* Setup all usd resources (python, plugins, resources). */
    #if os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
      Pixar.Bundler.shared.setup(.resources, installPlugins: true)
    #else
      Pixar.Bundler.shared.setup(.resources, installPlugins: false)
    #endif

    Msg.logger.info("succesfully registered all usd plugins.")

    // custom ar resolver examples.
    ArResolverExamples.run()

    // galah interpreter embedding examples.
    #if WITH_GALAH
      GalahInterpreterExamples.run()
    #endif /* WITH_GALAH */

    // python interpreter embedding examples.
    PythonInterpreterExamples.run()

    // scene description examples.
    SceneDescriptionExamples.run()

    // scene cache examples.
    StageCacheExamples.run()

    Msg.logger.info("program completed succesfully, exiting...")
  }
}
