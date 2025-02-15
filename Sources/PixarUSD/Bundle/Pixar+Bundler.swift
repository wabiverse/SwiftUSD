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

import Arch
import CxxStdlib
import Foundation
import Plug
import Rainbow

public extension Pixar
{
  final class Bundler: Sendable
  {
    public static let shared = Bundler()

    private init()
    {}

    public func setup(_ kind: BundleKind)
    {
      switch kind
      {
        case .resources:
          resourcesInit()
      }
    }

    private func resourcesInit()
    {
      /* 1. find all resource paths (ex. Usd/Contents/Resources) */
      let resources = BundleFramework.allCases.compactMap(\.resourcePath)

      /* 2. fill a std.vector of std.string plugin paths. */
      var plugPaths = Pixar.PlugRegistry.PlugPathsVector()
      _ = resources.map
      { path in

        #if DEBUG_PIXAR_BUNDLE
          Msg.logger.log(level: .info, "Adding usd resource -> \(path)")
        #endif /* DEBUG_PIXAR_BUNDLE */

        plugPaths.push_back(std.string(path))
      }

      /* 3. registers all plugins discovered in any plugPaths. */
      Pixar.PlugRegistry.GetInstance().RegisterPlugins(plugPaths)
    }
  }
}
