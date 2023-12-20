/* --------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                          ::
 * --------------------------------------------------------------
 * This program is free software; you can redistribute it, and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Check out
 * the GNU General Public License for more details.
 *
 * You should have received a copy for this software license, the
 * GNU General Public License along with this program; or, if not
 * write to the Free Software Foundation, Inc., to the address of
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import Foundation
import Plug

public extension Pixar.Bundle
{
  /**
   * Where ``Pixar.Plug`` application bundle resources are located. */
  static let plug = Bundle(path: "SwiftUSD_Plug.bundle")

  /**
   * Where ``Pixar.Ar`` application bundle resources are located. */
  static let ar = Bundle(path: "SwiftUSD_Ar.bundle")

  /**
   * Where ``Pixar.Sdf`` application bundle resources are located. */
  static let sdf = Bundle(path: "SwiftUSD_Sdf.bundle")

  /**
   * Where ``Pixar.Usd`` application bundle resources are located. */
  static let usd = Bundle(path: "SwiftUSD_Usd.bundle")

  /**
   * Where ``Pixar.Tf`` python bundle resources are located. */
  static let pyTf = Bundle(path: "SwiftUSD_PyTf.bundle")

  /**
   * Where ``Pixar.Plug`` python bundle resources are located. */
  static let pyPlug = Bundle(path: "SwiftUSD_PyPlug.bundle")

  /**
   * Where ``Pixar.Trace`` python bundle resources are located. */
  static let pyTrace = Bundle(path: "SwiftUSD_PyTrace.bundle")

  /**
   * Where ``Pixar.Work`` python bundle resources are located. */
  static let pyWork = Bundle(path: "SwiftUSD_PyWork.bundle")

  /**
   * Where ``Pixar.Gf`` python bundle resources are located. */
  static let pyGf = Bundle(path: "SwiftUSD_PyGf.bundle")

  /**
   * Where ``Pixar.Vt`` python bundle resources are located. */
  static let pyVt = Bundle(path: "SwiftUSD_PyVt.bundle")

  /**
   * Where ``Pixar.Ar`` python bundle resources are located. */
  static let pyAr = Bundle(path: "SwiftUSD_PyAr.bundle")

  /**
   * Where ``Pixar.Kind`` python bundle resources are located. */
  static let pyKind = Bundle(path: "SwiftUSD_PyKind.bundle")

  /**
   * Where ``Pixar.Sdf`` python bundle resources are located. */
  static let pySdf = Bundle(path: "SwiftUSD_PySdf.bundle")

  /**
   * Where ``Pixar.Pcp`` python bundle resources are located. */
  static let pyPcp = Bundle(path: "SwiftUSD_PyPcp.bundle")

  /**
   * Where ``Pixar.Usd`` python bundle resources are located. */
  static let pyUsd = Bundle(path: "SwiftUSD_PyUsd.bundle")
}

public extension Pixar
{
  struct Bundle
  {
    public static let shared = Pixar.Bundle()

    private init()
    {}

    public enum BundleKind
    {
      case resources
    }

    public func setup(_ kind: BundleKind)
    {
      switch kind
      {
        case .resources:
          resourcesInit()
      }
    }

    public enum BundleFramework: CaseIterable
    {
      case ar
      case plug
      case sdf
      case usd

      public var resourcePath: String?
      {
        switch self
        {
          case .ar: Bundle.ar?.resourcePath
          case .plug: Bundle.plug?.resourcePath
          case .sdf: Bundle.sdf?.resourcePath
          case .usd: Bundle.usd?.resourcePath
        }
      }
    }

    public enum BundlePython: CaseIterable
    {
      case pyTf
      case pyPlug
      case pyTrace
      case pyWork
      case pyGf
      case pyVt
      case pyAr
      case pyKind
      case pySdf
      case pyPcp
      case pyUsd

      public var resourcePath: String?
      {
        switch self
        {
          case .pyTf: Bundle.pyTf?.resourcePath
          case .pyPlug: Bundle.pyPlug?.resourcePath
          case .pyTrace: Bundle.pyTrace?.resourcePath
          case .pyWork: Bundle.pyWork?.resourcePath
          case .pyGf: Bundle.pyGf?.resourcePath
          case .pyVt: Bundle.pyVt?.resourcePath
          case .pyAr: Bundle.pyAr?.resourcePath
          case .pyKind: Bundle.pyKind?.resourcePath
          case .pySdf: Bundle.pySdf?.resourcePath
          case .pyPcp: Bundle.pyPcp?.resourcePath
          case .pyUsd: Bundle.pyUsd?.resourcePath
        }
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
        #if DEBUG
          Msg.Log.point("Adding usd resource", to: path)
        #endif /* DEBUG */

        plugPaths.push_back(std.string(path))
      }

      /* 3. registers all plugins discovered in any plugPaths. */
      Pixar.PlugRegistry.GetInstance().RegisterPlugins(plugPaths)
    }
  }
}
