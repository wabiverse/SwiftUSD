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
import SwiftBundlerBuilders

@main
public struct OpenUSDBuilder: Builder 
{
  public static func build(_ context: some BuilderContext) throws -> BuilderResult
  {
    try context.run(
      "/usr/bin/python3", [
        "build_scripts/build_usd.py",
        "--build-shared",
        "--no-python", 
        "--no-imaging", 
        "--no-usdview",
        "--build-variant", "release",
        context.buildDirectory.path
      ]
    )

    return .init()
  }
}
