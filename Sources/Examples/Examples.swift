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
    Pixar.Bundler.shared.setup(.resources)

    Msg.logger.info("succesfully registered all usd plugins.")

    // custom ar resolver examples.
    ArResolverExamples.run()

    // scene description examples.
    SceneDescriptionExamples.run()

    // scene cache examples.
    StageCacheExamples.run()

    Msg.logger.info("program completed succesfully, exiting...")
  }
}
