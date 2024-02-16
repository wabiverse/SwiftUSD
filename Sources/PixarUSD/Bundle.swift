/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import CxxStdlib
import Foundation
import PixarBase
import Plug
import Rainbow

#if os(Linux)
  /**
   * On Linux there is no ``Foundation.Bundle``, so we create one.
   */
  public struct Bundle
  {
    public static let main = Bundle()
    private init()
    {
      resourcePath = "/" + Pixar.Arch.getExecutablePath().split(separator: "/").dropLast().joined(separator: "/")

      Msg.logger.log(level: .info, "Bundle path: \(resourcePath ?? "")")
    }

    private let fileManager = FileManager.default

    public var resourcePath: String?

    public init?(path: String)
    {
      if fileManager.fileExists(atPath: path, isDirectory: nil)
      {
        resourcePath = path
      }
      else
      {
        return nil
      }
    }
  }
#endif /* os(Linux) */

public extension Bundle
{
  static let pxrRoot = Bundle.main.resourcePath ?? ""

  #if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
    static let ext = ".bundle"
  #else
    static let ext = ".resources"
  #endif

  /**
   * Where ``__ObjC/Pixar/Ar`` application bundle resources are located. */
  static let ar = Bundle(path: "\(pxrRoot)/SwiftUSD_Ar\(ext)")

  /**
   * Where ``__ObjC/Pixar/Sdf`` application bundle resources are located. */
  static let sdf = Bundle(path: "\(pxrRoot)/SwiftUSD_Sdf\(ext)")

  /**
   * Where ``__ObjC/Pixar/Usd`` application bundle resources are located. */
  static let usd = Bundle(path: "\(pxrRoot)/SwiftUSD_Usd\(ext)")

  /**
   * Where ``__ObjC/Pixar/Ndr`` application bundle resources are located. */
  static let ndr = Bundle(path: "\(pxrRoot)/SwiftUSD_Ndr\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdGeom`` application bundle resources are located. */
  static let usdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdGeom\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdShade`` application bundle resources are located. */
  static let usdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShade\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdShaders`` application bundle resources are located. */
  static let usdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShaders\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdLux`` application bundle resources are located. */
  static let usdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdLux\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdHydra`` application bundle resources are located. */
  static let usdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdHydra\(ext)")

  /**
   * Where ``__ObjC/Pixar/Hd`` application bundle resources are located. */
  static let hd = Bundle(path: "\(pxrRoot)/SwiftUSD_Hd\(ext)")

  /**
   * Where ``__ObjC/Pixar/Tf`` python bundle resources are located. */
  static let pyTf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTf\(ext)")

  /**
   * Where ``__ObjC/Pixar/Plug`` python bundle resources are located. */
  static let pyPlug = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPlug\(ext)")

  /**
   * Where ``__ObjC/Pixar/Trace`` python bundle resources are located. */
  static let pyTrace = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTrace\(ext)")

  /**
   * Where ``__ObjC/Pixar/Work`` python bundle resources are located. */
  static let pyWork = Bundle(path: "\(pxrRoot)/SwiftUSD_PyWork\(ext)")

  /**
   * Where ``__ObjC/Pixar/Gf`` python bundle resources are located. */
  static let pyGf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGf\(ext)")

  /**
   * Where ``__ObjC/Pixar/Vt`` python bundle resources are located. */
  static let pyVt = Bundle(path: "\(pxrRoot)/SwiftUSD_PyVt\(ext)")

  /**
   * Where ``__ObjC/Pixar/Ar`` python bundle resources are located. */
  static let pyAr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyAr\(ext)")

  /**
   * Where ``__ObjC/Pixar/Kind`` python bundle resources are located. */
  static let pyKind = Bundle(path: "\(pxrRoot)/SwiftUSD_PyKind\(ext)")

  /**
   * Where ``__ObjC/Pixar/Sdf`` python bundle resources are located. */
  static let pySdf = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdf\(ext)")

  /**
   * Where ``__ObjC/Pixar/Pcp`` python bundle resources are located. */
  static let pyPcp = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPcp\(ext)")

  /**
   * Where ``__ObjC/Pixar/Usd`` python bundle resources are located. */
  static let pyUsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsd\(ext)")

  /**
   * Where ``__ObjC/Pixar/Ndr`` python bundle resources are located. */
  static let pyNdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyNdr\(ext)")

  /**
   * Where ``__ObjC/Pixar/Sdr`` python bundle resources are located. */
  static let pySdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdr\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdGeom`` python bundle resources are located. */
  static let pyUsdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdGeom\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdShade`` python bundle resources are located. */
  static let pyUsdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShade\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdShaders`` application bundle resources are located. */
  static let pyUsdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShaders\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdLux`` application bundle resources are located. */
  static let pyUsdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdLux\(ext)")

  /**
   * Where ``__ObjC/Pixar/UsdHydra`` application bundle resources are located. */
  static let pyUsdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdHydra\(ext)")

  /**
   * Where ``__ObjC/Pixar/CameraUtil`` application bundle resources are located. */
  static let pyCameraUtil = Bundle(path: "\(pxrRoot)/SwiftUSD_PyCameraUtil\(ext)")

  /**
   * Where ``__ObjC/Pixar/PxOsd`` application bundle resources are located. */
  static let pyPxOsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPxOsd\(ext)")
}

public enum BundleKind
{
  case resources
}

public extension Pixar
{
  struct Bundler
  {
    let fileManager: FileManager

    public static let shared: Bundler = .init()

    private init()
    {
      fileManager = FileManager.default
    }

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
      /* ?. Toggle app bundling help in console. */
      var showHelp = false

      /* 1. find all resource paths (ex. Usd/Contents/Resources) */
      let resources = BundleFramework.allCases.compactMap(\.resourcePath)

      /* 2. fill a std.vector of std.string plugin paths. */
      var plugPaths = Pixar.PlugRegistry.PlugPathsVector()
      _ = resources.map
      { path in

        #if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
          let doInstallPlugs = !path.contains(".app") && !fileManager.fileExists(atPath: path.replacingOccurrences(of: "/Contents/Resources", with: "") + "/Contents/Resources", isDirectory: nil)
        #else /* os(Linux) */
          let doInstallPlugs = true
        #endif /* os(Linux) */

        /* Check for the existence of usd plugins, if they do not exist, we install them automatically. */
        if doInstallPlugs
        {
          /* Tell user what we are doing. */
          showHelp = true

          /* Automatically install the plugin. */
          let installedPlug = installPlug(at: path)

          #if DEBUG_PIXAR_BUNDLE
            Msg.logger.log(level: .info, "Adding usd resource -> \(shortenedPath(from: installedPlug).trailing)")
          #endif /* DEBUG_PIXAR_BUNDLE */

          plugPaths.push_back(std.string(installedPlug))
        }
        else
        {
          #if DEBUG_PIXAR_BUNDLE
            Msg.logger.log(level: .info, "Adding usd resource -> \(shortenedPath(from: path).trailing)")
          #endif /* DEBUG_PIXAR_BUNDLE */

          plugPaths.push_back(std.string(path))
        }
      }

      if showHelp
      {
        showBundleHelp(
          with: resources.map { shortenedPath(from: $0).trailing },
          searched: shortenedPath(from: resources.first ?? "").leading
        )
        showHelp = false
      }

      /* 3. registers all plugins discovered in any plugPaths. */
      Pixar.PlugRegistry.GetInstance().RegisterPlugins(plugPaths)
    }
  }
}

public enum BundleFramework: CaseIterable
{
  case ar
  case sdf
  case usd
  case ndr
  case usdGeom
  case usdShade
  case usdShaders
  case usdLux
  case usdHydra
  case hd

  public var resourcePath: String?
  {
    switch self
    {
      case .ar: Bundle.ar?.resourcePath
      case .sdf: Bundle.sdf?.resourcePath
      case .usd: Bundle.usd?.resourcePath
      case .ndr: Bundle.ndr?.resourcePath
      case .usdGeom: Bundle.usdGeom?.resourcePath
      case .usdShade: Bundle.usdShade?.resourcePath
      case .usdShaders: Bundle.usdShaders?.resourcePath
      case .usdLux: Bundle.usdLux?.resourcePath
      case .usdHydra: Bundle.usdHydra?.resourcePath
      case .hd: Bundle.hd?.resourcePath
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
  case pyNdr
  case pySdr
  case pyUsdGeom
  case pyUsdShade
  case pyUsdShaders
  case pyUsdLux
  case pyUsdHydra
  case pyCameraUtil
  case pyPxOsd

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
      case .pyNdr: Bundle.pyNdr?.resourcePath
      case .pySdr: Bundle.pySdr?.resourcePath
      case .pyUsdGeom: Bundle.pyUsdGeom?.resourcePath
      case .pyUsdShade: Bundle.pyUsdShade?.resourcePath
      case .pyUsdShaders: Bundle.pyUsdShaders?.resourcePath
      case .pyUsdLux: Bundle.pyUsdLux?.resourcePath
      case .pyUsdHydra: Bundle.pyUsdHydra?.resourcePath
      case .pyCameraUtil: Bundle.pyCameraUtil?.resourcePath
      case .pyPxOsd: Bundle.pyPxOsd?.resourcePath
    }
  }
}

public extension Pixar.Bundler
{
  private func installPlug(at path: String) -> String
  {
    func strip(_ path: String) -> String
    {
      path.replacingOccurrences(of: "/Contents/Resources", with: "")
    }

    let dest = strip(path) + "/Contents/Resources"
    let srcEnum = fileManager.enumerator(atPath: path)

    do
    {
      if fileManager.fileExists(atPath: strip(path) + "/Contents", isDirectory: nil)
      {
        try fileManager.removeItem(atPath: strip(path) + "/Contents")
      }

      try fileManager.createDirectory(atPath: dest, withIntermediateDirectories: true)

      while let file = srcEnum?.nextObject() as? String
      {
        let sourceFile = path.appending("/\(file)")
        let destFile = dest.appending("/\(file)")

        if sourceFile.contains("Contents")
        {
          continue
        }

        #if DEBUG_PIXAR_BUNDLE
          Msg.logger.log(level: .info, "Moving resource: \(sourceFile) -> \(destFile)")
        #endif /* DEBUG_PIXAR_BUNDLE */

        try fileManager.moveItem(atPath: sourceFile,
                                 toPath: destFile)
      }
    }
    catch
    {
      Msg.logger.log(level: .error, "Could not move usd resource from \(path) to \(dest): \(error.localizedDescription)")
    }

    return dest
  }
}

public extension Pixar.Bundler
{
  private struct ShortPath
  {
    var leading: String
    var trailing: String
  }

  /**
   * Shorten a plug's long path up to its bundle dir by
   * returning the shortened path part of the string as
   * a struct with leading and trailing parts. Only for
   * console logs to keep them short and readable.
   */
  private func shortenedPath(from string: String) -> ShortPath
  {
    #if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
      /**  xcode build directories are capitalized, swiftpm builds are not. */
      let isXcodeBuild = string.contains("Build")

      #if DEBUG
        let shortenTo = isXcodeBuild ? "Debug/" : "debug/"
      #else
        let shortenTo = isXcodeBuild ? "Release/" : "release/"
      #endif
    #else
      #if DEBUG
        let shortenTo = "debug/"
      #else
        let shortenTo = "release/"
      #endif
    #endif

    if let theRange = string.range(of: shortenTo, options: .backwards)
    {
      return ShortPath(leading: String(string[..<theRange.lowerBound]) + shortenTo,
                       trailing: String(string[theRange.upperBound...]))
    }
    else
    {
      return ShortPath(leading: string, trailing: string)
    }
  }
}

public extension Pixar.Bundler
{
  private func showBundleHelp(with missing: [String], searched: String)
  {
    Msg.logger.log(level: .warning, """

      \("MISSING USD RESOURCES".magenta) ------------------------------------------------------------------

      \("We searched for resources in the following location:".lightBlue)
      \("*".yellow)  \(searched.magenta)

      \("And the following resources were not found:".lightBlue)
      \(missing.map { "\("*".yellow)  \($0.magenta)" }.joined(separator: "\n"))

      ----------------------------------------------------------------------------------------

      Plugins are not installed and will be installed for you, however, you should bundle the
      application bundle appropriately with \("https://swiftbundler.dev".cyan) instead of the \("swift run".yellow)
      command, this is because \("swift run".yellow) is not meant to run bundled applications, it is best
      suited for command line utilities that do not require application resources or graphical
      user interfaces.

      ----------------------------------------------------------------------------------------

      The recommended method of running your app is to add swift bundler to the swift package
      by adding the following code to your package \("dependencies".yellow) array:

      \("dependencies: [".green)
      \("  .package(url: \"https://github.com/furby-tm/swift-bundler\", from: \"2.0.9\")".green)
      \("]".green)

      ----------------------------------------------------------------------------------------

      Then, instead of running \("swift run".yellow), use swift bundler's package plugin command:

      \("$".red) \("swift".yellow) package \("--disable-sandbox".lightWhite) plugin bundler run \("-p".lightWhite) \("macOS".magenta) \("MyApp".yellow)

      \("NOTE:".magenta) Ensure that you replace \("MyApp".yellow) to the name of your executable target,
      and change the platform (\("-p".lightWhite) \("macOS".magenta)) depending on the intended platform.

      The following platforms are currently supported:
      \("*".yellow) \("linux".magenta)
      \("*".yellow) \("macOS".magenta)
      \("*".yellow) \("visionOS".magenta) or \("visionOSSimulator".magenta)
      \("*".yellow) \("iOS".magenta) or \("iOSSimulator".magenta)

      When running on \("visionOSSimulator".magenta) or \("iOSSimulator".magenta), the simulator will automatically
      launch with an instance of your bundled app running within it.

      ----------------------------------------------------------------------------------------
      """)
  }
}
