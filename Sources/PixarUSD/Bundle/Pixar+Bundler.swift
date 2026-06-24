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

#if canImport(Arch)
  import Arch
  import Plug
#else
  import OpenUSD
#endif
import CxxStdlib
import Foundation

#if !os(Android)
  import Rainbow
#endif

public extension Pixar
{
  final class Bundler: Sendable
  {
    public static let shared = Bundler()

    /**
     * On Android the app files directory must be set before calling
     * ``setup(_:)``.  Read ``/proc/self/cmdline`` to get the package name
     * and derive the path, e.g. ``/data/data/foundation.wabi.usdview/files``.
     *
     * This property is written once from the main thread in ``UsdView.init()``
     * and read once shortly after on the same thread, so unsynchronised access
     * is safe in practice.
     */
    public nonisolated(unsafe) static var androidFilesDir: String = ""

    private init()
    {}

    public func setup(_ kind: BundleKind)
    {
      switch kind
      {
        case .resources:
          #if os(Android)
            resourcesInitAndroid()
          #else
            resourcesInit()
          #endif
      }
    }

    private func resourcesInit()
    {
      /* 1. find all resource paths (ex. Usd/Contents/Resources) */
      let resources = BundleFramework.allCases.compactMap(\.resourcePath)

      /* 2. fill a std.vector of std.string plugin paths. */
      var plugPaths = Overlay.MakeStringVector()
      _ = resources.map
      { path in

        #if DEBUG_PIXAR_BUNDLE
          Msg.logger.log(level: .info, "Adding usd resource -> \(path)")
        #endif /* DEBUG_PIXAR_BUNDLE */

        plugPaths = path.withCString { Overlay.PushBackPath(plugPaths, $0) }
      }

      /* 3. registers all plugins discovered in any plugPaths. */
      Pixar.PlugRegistry.GetInstance().RegisterPlugins(plugPaths)
    }
  }
}
