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

#if os(Linux)
  /**
   * On Linux there is no ``Foundation.Bundle``, so we create one.
   */
  public struct Bundle
  {
    public static let main = Bundle()
    private init()
    {
      resourcePath = "/" + Arch.getExecutablePath().split(separator: "/").dropLast().joined(separator: "/")

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
   * Where ``Ar`` application bundle resources are located. */
  static let ar = Bundle(path: "\(pxrRoot)/SwiftUSD_Ar\(ext)")

  /**
   * Where ``Sdf`` application bundle resources are located. */
  static let sdf = Bundle(path: "\(pxrRoot)/SwiftUSD_Sdf\(ext)")

  /**
   * Where ``Usd`` application bundle resources are located. */
  static let usd = Bundle(path: "\(pxrRoot)/SwiftUSD_Usd\(ext)")

  /**
   * Where ``Ndr`` application bundle resources are located. */
  static let ndr = Bundle(path: "\(pxrRoot)/SwiftUSD_Ndr\(ext)")

  /**
   * Where ``UsdGeom`` application bundle resources are located. */
  static let usdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdGeom\(ext)")

  /**
   * Where ``UsdShade`` application bundle resources are located. */
  static let usdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShade\(ext)")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let usdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShaders\(ext)")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let usdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdLux\(ext)")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let usdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdHydra\(ext)")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let sdrOsl = Bundle(path: "\(pxrRoot)/SwiftUSD_SdrOsl\(ext)")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let usdAbc = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdAbc\(ext)")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let usdDraco = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdDraco\(ext)")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let usdMedia = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdMedia\(ext)")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let usdMtlx = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdMtlx\(ext)")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let usdPhysics = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdPhysics\(ext)")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let usdProc = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdProc\(ext)")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let usdRender = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdRender\(ext)")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let usdRi = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdRi\(ext)")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let usdSkel = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdSkel\(ext)")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let usdUI = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdUI\(ext)")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let usdVol = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdVol\(ext)")

  /**
   * Where ``Hd`` application bundle resources are located. */
  static let hd = Bundle(path: "\(pxrRoot)/SwiftUSD_Hd\(ext)")

  /**
   * Where ``HgiMetal`` application bundle resources are located. */
  static let hgiMetal = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiMetal\(ext)")

  /**
   * Where ``HgiVulkan`` application bundle resources are located. */
  static let hgiVulkan = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiVulkan\(ext)")

  /**
   * Where ``HgiGL`` application bundle resources are located. */
  static let hgiGL = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiGL\(ext)")

  /**
   * Where ``Hio`` application bundle resources are located. */
  static let hio = Bundle(path: "\(pxrRoot)/SwiftUSD_Hio\(ext)")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let glf = Bundle(path: "\(pxrRoot)/SwiftUSD_Glf\(ext)")

  /**
   * Where ``Tf`` python bundle resources are located. */
  static let pyTf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTf\(ext)")

  /**
   * Where ``Plug`` python bundle resources are located. */
  static let pyPlug = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPlug\(ext)")

  /**
   * Where ``Trace`` python bundle resources are located. */
  static let pyTrace = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTrace\(ext)")

  /**
   * Where ``Work`` python bundle resources are located. */
  static let pyWork = Bundle(path: "\(pxrRoot)/SwiftUSD_PyWork\(ext)")

  /**
   * Where ``Gf`` python bundle resources are located. */
  static let pyGf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGf\(ext)")

  /**
   * Where ``Vt`` python bundle resources are located. */
  static let pyVt = Bundle(path: "\(pxrRoot)/SwiftUSD_PyVt\(ext)")

  /**
   * Where ``Ar`` python bundle resources are located. */
  static let pyAr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyAr\(ext)")

  /**
   * Where ``Kind`` python bundle resources are located. */
  static let pyKind = Bundle(path: "\(pxrRoot)/SwiftUSD_PyKind\(ext)")

  /**
   * Where ``Sdf`` python bundle resources are located. */
  static let pySdf = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdf\(ext)")

  /**
   * Where ``Pcp`` python bundle resources are located. */
  static let pyPcp = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPcp\(ext)")

  /**
   * Where ``Usd`` python bundle resources are located. */
  static let pyUsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsd\(ext)")

  /**
   * Where ``Ndr`` python bundle resources are located. */
  static let pyNdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyNdr\(ext)")

  /**
   * Where ``Sdr`` python bundle resources are located. */
  static let pySdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdr\(ext)")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let pySdrOsl = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdrOsl\(ext)")

  /**
   * Where ``UsdGeom`` python bundle resources are located. */
  static let pyUsdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdGeom\(ext)")

  /**
   * Where ``UsdShade`` python bundle resources are located. */
  static let pyUsdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShade\(ext)")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let pyUsdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShaders\(ext)")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let pyUsdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdLux\(ext)")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let pyUsdAbc = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdAbc\(ext)")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let pyUsdDraco = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdDraco\(ext)")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let pyUsdMedia = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdMedia\(ext)")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let pyUsdMtlx = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdMtlx\(ext)")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let pyUsdPhysics = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdPhysics\(ext)")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let pyUsdProc = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdProc\(ext)")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let pyUsdRender = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdRender\(ext)")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let pyUsdRi = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdRi\(ext)")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let pyUsdSkel = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdSkel\(ext)")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let pyUsdUI = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdUI\(ext)")

  /**
   * Where ``UsdUtils`` application bundle resources are located. */
  static let pyUsdUtils = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdUtils\(ext)")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let pyUsdVol = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdVol\(ext)")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let pyUsdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdHydra\(ext)")

  /**
   * Where ``CameraUtil`` application bundle resources are located. */
  static let pyCameraUtil = Bundle(path: "\(pxrRoot)/SwiftUSD_PyCameraUtil\(ext)")

  /**
   * Where ``PxOsd`` application bundle resources are located. */
  static let pyPxOsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPxOsd\(ext)")

  /**
   * Where ``Garch`` application bundle resources are located. */
  static let pyGarch = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGarch\(ext)")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let pyGlf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGlf\(ext)")

  /**
   * Where ``GeomUtil`` application bundle resources are located. */
  static let pyGeomUtil = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGeomUtil\(ext)")
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

    public func setup(_ kind: BundleKind, installPlugins: Bool = false)
    {
      switch kind
      {
        case .resources:
          resourcesInit(installPlugins: installPlugins)
      }
    }

    private func resourcesInit(installPlugins: Bool)
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
          let doInstallPlugs = installPlugins || (!path.contains(".app") && !fileManager.fileExists(atPath: path.replacingOccurrences(of: "/Contents/Resources", with: "") + "/Contents/Resources", isDirectory: nil))
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
  case sdrOsl
  case usdAbc
  case usdDraco
  case usdMedia
  case usdMtlx
  case usdPhysics
  case usdProc
  case usdRender
  case usdRi
  case usdSkel
  case usdUI
  case usdVol
  case hd
  case hgiMetal
  case hgiVulkan
  case hgiGL
  case hio
  case glf

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
      case .sdrOsl: Bundle.sdrOsl?.resourcePath
      case .usdAbc: Bundle.usdAbc?.resourcePath
      case .usdDraco: Bundle.usdDraco?.resourcePath
      case .usdMedia: Bundle.usdMedia?.resourcePath
      case .usdMtlx: Bundle.usdMtlx?.resourcePath
      case .usdPhysics: Bundle.usdPhysics?.resourcePath
      case .usdProc: Bundle.usdProc?.resourcePath
      case .usdRender: Bundle.usdRender?.resourcePath
      case .usdRi: Bundle.usdRi?.resourcePath
      case .usdSkel: Bundle.usdSkel?.resourcePath
      case .usdUI: Bundle.usdUI?.resourcePath
      case .usdVol: Bundle.usdVol?.resourcePath
      case .hd: Bundle.hd?.resourcePath
      case .hgiMetal: Bundle.hgiMetal?.resourcePath
      case .hgiVulkan: Bundle.hgiVulkan?.resourcePath
      case .hgiGL: Bundle.hgiGL?.resourcePath
      case .hio: Bundle.hio?.resourcePath
      case .glf: Bundle.glf?.resourcePath
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
  case pySdrOsl
  case pyUsdGeom
  case pyUsdShade
  case pyUsdShaders
  case pyUsdLux
  case pyUsdHydra
  case pyUsdAbc
  case pyUsdDraco
  case pyUsdMedia
  case pyUsdMtlx
  case pyUsdPhysics
  case pyUsdProc
  case pyUsdRender
  case pyUsdRi
  case pyUsdSkel
  case pyUsdUI
  case pyUsdUtils
  case pyUsdVol
  case pyCameraUtil
  case pyPxOsd
  case pyGarch
  case pyGlf
  case pyGeomUtil

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
      case .pySdrOsl: Bundle.pySdrOsl?.resourcePath
      case .pyUsdGeom: Bundle.pyUsdGeom?.resourcePath
      case .pyUsdShade: Bundle.pyUsdShade?.resourcePath
      case .pyUsdShaders: Bundle.pyUsdShaders?.resourcePath
      case .pyUsdLux: Bundle.pyUsdLux?.resourcePath
      case .pyUsdHydra: Bundle.pyUsdHydra?.resourcePath
      case .pyUsdAbc: Bundle.pyUsdAbc?.resourcePath
      case .pyUsdDraco: Bundle.pyUsdDraco?.resourcePath
      case .pyUsdMedia: Bundle.pyUsdMedia?.resourcePath
      case .pyUsdMtlx: Bundle.pyUsdMtlx?.resourcePath
      case .pyUsdPhysics: Bundle.pyUsdPhysics?.resourcePath
      case .pyUsdProc: Bundle.pyUsdProc?.resourcePath
      case .pyUsdRender: Bundle.pyUsdRender?.resourcePath
      case .pyUsdRi: Bundle.pyUsdRi?.resourcePath
      case .pyUsdSkel: Bundle.pyUsdSkel?.resourcePath
      case .pyUsdUI: Bundle.pyUsdUI?.resourcePath
      case .pyUsdUtils: Bundle.pyUsdUtils?.resourcePath
      case .pyUsdVol: Bundle.pyUsdVol?.resourcePath
      case .pyCameraUtil: Bundle.pyCameraUtil?.resourcePath
      case .pyPxOsd: Bundle.pyPxOsd?.resourcePath
      case .pyGarch: Bundle.pyGarch?.resourcePath
      case .pyGlf: Bundle.pyGlf?.resourcePath
      case .pyGeomUtil: Bundle.pyGeomUtil?.resourcePath
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
