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

import ArPrototypes
import Foundation
import PixarUSD

/* ----------- xxx ----------
 *    AR RESOLVER EXAMPLES
 * ----------- xxx ---------- */

final class CustomResolver: ArDefaultResolver
{
  func _resolve(_ path: std.string) -> Pixar.ArResolvedPath
  {
    Msg.logger.info("resolving path: \(path)")

    let asset = _Resolve(path)
    if !asset.empty()
    {
      return asset
    }

    return .init()
  }
}

public enum ArResolverExamples
{
  public static func run()
  {
    Msg.logger.info("running ar resolver examples...")

    Msg.logger.info("creating new ar custom resolver.")
    let resolver = CustomResolver()
    let resolvedPath = resolver._resolve(std.string("HelloPixarUSD.usda"))
    Msg.logger.info("resolved path: \(resolvedPath.empty() ? "empty" : resolvedPath.path)")

    Msg.logger.info("ar resolver examples succesfully completed.")
  }
}
