/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                                  ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                   Copyright (C) 2016 Pixar. All Rights Reserved.
 *                              Copyright (C) 2024 Wabi Foundation.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import ArgumentParser
import Foundation

/**
 * The subcommand for changing the pixar
 * usd version for a specified package.
 */
struct UpdateCommand: AsyncCommand
{
  static let configuration = CommandConfiguration(
    commandName: "update",
    abstract: "Update the OpenUSD version in the current package."
  )

  /// Arguments in common with the run command.
  @OptionGroup
  var arguments: UpdateArguments

  init()
  {
    _arguments = OptionGroup()
  }

  init(arguments: OptionGroup<UpdateArguments>)
  {
    _arguments = arguments
  }

  static func validateArguments(_: UpdateArguments) -> Bool
  {
    // validate parameters
    true
  }

  func wrappedRun() async throws
  {
    // get the package directory.
    var packageDirectory = URL(fileURLWithPath: ".")
    if let selectedPackage = arguments.packageDirectory
    {
      packageDirectory = selectedPackage
    }

    // get the package directory path.
    let pkgDir = packageDirectory.path

    // remove possibly existing openusd directory.
    if FileManager.default.fileExists(atPath: "\(pkgDir)/.build/OpenUSD", isDirectory: nil)
    {
      try FileManager.default.removeItem(atPath: "\(pkgDir)/.build/OpenUSD")
    }

    // start timing
    let elapsed = try await Stopwatch.time
    {
      // 1. clone pixar official openusd repository.
      if let usdVersion = arguments.usdVersion {
        try Command.git.run(with: ["clone", "--branch", usdVersion, "https://github.com/PixarAnimationStudios/OpenUSD.git", "\(pkgDir)/.build/OpenUSD"])
      } else {
        log.info("no openusd version provided, updating openusd to the latest revision from the 'dev' branch.")
        try Command.git.run(with: ["clone", "https://github.com/PixarAnimationStudios/OpenUSD.git", "\(pkgDir)/.build/OpenUSD"])
      }

      // 2. collect basenames of files enumerate() treats specially (python-only, test-only).
      let exclusions = SourceExclusions(checkoutRoot: "\(pkgDir)/.build/OpenUSD")

      // 3. update all usd source in this package, in parallel.
      async let bse = try Pxr.base.enumerate(packagePath: pkgDir, exclusions: exclusions)
      async let img = try Pxr.imaging.enumerate(packagePath: pkgDir, exclusions: exclusions)
      async let usd = try Pxr.usd.enumerate(packagePath: pkgDir, exclusions: exclusions)
      async let uim = try Pxr.usdImaging.enumerate(packagePath: pkgDir, exclusions: exclusions)
      async let exc = try Pxr.exec.enumerate(packagePath: pkgDir, exclusions: exclusions)

      // 4. wait for all usd source to be updated.
      let _ = try await [bse, img, usd, uim, exc]
    }

    // output elapsed time
    log.info("done in \(elapsed.secondsString). openusd source updated at '\(pkgDir)'.")
  }
}

/**
 * Basenames of source files that `enumerate()`/`updateSource()` treat
 * specially, collected once per checkout and threaded through to every
 * `Pxr.enumerate()` call. */
public struct SourceExclusions: Sendable
{
  /** Files only built when `PXR_ENABLE_PYTHON_SUPPORT` is on. */
  let pythonOnly: Set<String>
  /** Files only built when `PXR_BUILD_TESTS` is on. */
  let testOnly: Set<String>

  public init(checkoutRoot: String)
  {
    pythonOnly = collectPythonOnlyBasenames(checkoutRoot: checkoutRoot)
    testOnly = collectTestingFiles(checkoutRoot: checkoutRoot)
  }
}

/**
 * Find all `<lib>Test_<Name>` files (ex. "tsTest_Museum.cpp") -- only
 * built when PXR_BUILD_TESTS is on, so enumerate() skips them. */
private func collectTestingFiles(checkoutRoot: String) -> Set<String>
{
  var basenames: Set<String> = ["examples_usd", "examples_usdGeom"]

  guard let regex = try? NSRegularExpression(pattern: "^[a-z]+Test_[A-Z]"),
        let enumerator = FileManager.default.enumerator(atPath: "\(checkoutRoot)/pxr")
  else { return basenames }

  for entry in enumerator
  {
    guard let relPath = entry as? String else { continue }

    var name = (relPath as NSString).lastPathComponent
    guard let dotIndex = name.lastIndex(of: ".") else { continue }
    name = String(name[name.startIndex..<dotIndex])

    let range = NSRange(name.startIndex..<name.endIndex, in: name)
    if regex.firstMatch(in: name, range: range) != nil
    {
      basenames.insert(name)
    }
  }

  return basenames
}

/**
 * Scans every `CMakeLists.txt` for sources only built when
 * `PXR_ENABLE_PYTHON_SUPPORT` is on (`PYTHON_*_CLASSES`/`HEADERS`, plus
 * `PYMODULE_CPPFILES` entries without "wrap"/"module", ex.
 * `pyWeakObject.cpp`). `Patch.pythonGuards` wraps these files in
 * `#if PXR_PYTHON_SUPPORT_ENABLED`. */
private func collectPythonOnlyBasenames(checkoutRoot: String) -> Set<String>
{
  var basenames: Set<String> = []

  let pythonListNames: Set<String> = [
    "PYTHON_PUBLIC_CLASSES", "PYTHON_PRIVATE_CLASSES",
    "PYTHON_PUBLIC_HEADERS", "PYTHON_PRIVATE_HEADERS",
  ]

  func isListName(_ s: String) -> Bool
  {
    guard let first = s.first, first.isUppercase else { return false }
    return s.allSatisfy { $0.isUppercase || $0.isNumber || $0 == "_" }
  }

  guard let enumerator = FileManager.default.enumerator(atPath: "\(checkoutRoot)/pxr")
  else { return basenames }

  for entry in enumerator
  {
    guard let relPath = entry as? String, relPath.hasSuffix("CMakeLists.txt"),
          let contents = try? String(contentsOfFile: "\(checkoutRoot)/pxr/\(relPath)", encoding: .utf8)
    else { continue }

    var currentList: String? = nil
    for rawLine in contents.components(separatedBy: "\n")
    {
      let trimmed = rawLine.trimmingCharacters(in: .whitespaces)
      if trimmed.isEmpty { currentList = nil; continue }
      if isListName(trimmed) { currentList = trimmed; continue }

      guard let list = currentList else { continue }

      if list == "PYMODULE_CPPFILES"
      {
        if trimmed.contains("wrap") || trimmed.contains("module") { continue }
      }
      else if !pythonListNames.contains(list)
      {
        continue
      }

      var name = (trimmed as NSString).lastPathComponent
      if let dotIndex = name.lastIndex(of: ".")
      {
        name = String(name[name.startIndex..<dotIndex])
      }
      basenames.insert(name)
    }
  }

  return basenames
}

/**
 * The Pixar packages to update.
 */
public enum Pxr: String, CaseIterable
{
  /** The pxr.base package. */
  case base
  /** The pxr.imaging package. */
  case imaging
  /** The pxr.usd package. */
  case usd
  /** The pxr.usdImaging imaging package. */
  case usdImaging
  /** The pxr.exec package. */
  case exec

  /**
   * List the given package path, updating the source files for this
   * package from upstream pixar, and return a list of updated files.
   */
  public func enumerate(packagePath: String, exclusions: SourceExclusions) async throws -> [URL]
  {
    // ------------- list all files in the directory -------------

    guard let list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/\(rawValue)")
    else { log.critical("Failed to list \(rawValue) directory."); return [] }

    // ----- clear out stale generated files before repopulating -----

    // remember which targets already declare resource dirs before nuking
    // them, so we don't create new ones Package.swift doesn't declare.
    let existingResourceDirs = resourceDirectories(packagePath: packagePath)

    try nukeStaleTargetFiles(packagePath: packagePath, resourceDirectories: existingResourceDirs)

    // ---------------- process each file in list ----------------

    let updatedFiles: [URL] = try list.compactMap
    { pxrPath in

      // ----------- determine target and source paths -----------

      let suffix = path(from: pxrPath).split(separator: "pxr/\(rawValue)/").last ?? ""
      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")
      let suffixParts = suffix.split(separator: "/")

      // plugin/ libs (ex. usdAbc, hdStorm) are named by their second path
      // component, "plugin" is just a grouping dir, not a target.
      let isPluginLibrary = suffixParts.first == "plugin"
      var target = String((isPluginLibrary ? suffixParts.dropFirst().first : suffixParts.first) ?? "").capitalized

      ensureCasing(for: &target)

      // plugins we don't build yet (hioAvif, hioOpenEXR, hioOiio, hioImageIO,
      // hdEmbree -- vendored codec libs) have no Sources/<Target>, skip them.
      let isUnbuiltPlugin = isPluginLibrary && !FileManager.default.fileExists(atPath: "\(packagePath)/Sources/\(target)")

      // --------------------- skipped source --------------------

      #if os(Windows)
        let platformExcludes = false
      #else /* !os(Windows) */
        let platformExcludes = source.path.lowercased().contains("msinttypes")
      #endif
      if source.path.contains("testenv") ||
        source.path.lowercased().contains("cmakelists") ||
        source.path.lowercased().contains("pch.h") ||
        source.path.lowercased().contains(".template.") ||
        source.path.lowercased().contains("codegentemplates") ||
        source.path.lowercased().contains("unittest") ||
        exclusions.testOnly.contains(source.deletingPathExtension().lastPathComponent) ||
        platformExcludes ||
        isUnbuiltPlugin
      { return nil }

      // --------------- create target directories ---------------

      try createTargetDirectories(packagePath: packagePath, target: target)
      try createPythonDirectories(packagePath: packagePath, target: target)

      var sourceFile = source.lastPathComponent

      // SwiftPM has no per-file compile-flag override, so give this file
      // a ".mm" extension to get objective-c++ mode from the compiler driver
      // on every platform (this should be fine to do on Android, Linux, and
      // Windows).
      if target == "HgiInterop", sourceFile == "hgiInterop.cpp"
      {
        sourceFile = "hgiInterop.mm"
      }

      // ------ copy source files to dest (Sources/Target/*) -----

      if ["m", "mm", "cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if sourceFile.contains("wrap") || sourceFile.contains("module")
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(sourceFile)")

          // move wrap and module files to Python/PyTarget/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating python module: \(dest.path)")
          updateSource(fileURL: dest, target: target, exclusions: exclusions)

          return dest
        }
        else
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(sourceFile)")

          // move source files to Sources/Target/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating source: \(dest.path)")
          updateSource(fileURL: dest, target: target, exclusions: exclusions)

          return dest
        }
      }

      // ----- copy headers (Sources/Target/include/Target/*) -----

      // CMake `configure_file()` templates (ex. "impl.h.in" -> "impl.h").
      // "pxr/pxr.h.in" is handled by hand as "pxr/pxrns.h" and lives outside
      // these enumerated package directories, so it never reaches here.
      let isConfigTemplate = source.pathExtension == "in" && source.deletingPathExtension().pathExtension == "h"

      if ["h", "hpp", "hxx"].contains(source.pathExtension) || isConfigTemplate
      {
        if isConfigTemplate
        {
          // configure_file() writes its output without the trailing ".in".
          sourceFile = source.deletingPathExtension().lastPathComponent
        }

        // pegtl's internal/ and contrib/ headers share basenames with
        // top-level pegtl/*.hpp (ex. utf8.hpp) -- flattening them together
        // lets one clobber the other. preserve internal/ and contrib/ as
        // real subdirectories, matching upstream's layout.
        var preservesSubdirectory = false
        if target == "Pegtl"
        {
          let pegtlPath = suffix.split(separator: "/").dropFirst(2).joined(separator: "/")
          if pegtlPath.hasPrefix("internal/") || pegtlPath.hasPrefix("contrib/")
          {
            sourceFile = pegtlPath
            preservesSubdirectory = true
          }
        }

        // Tf vendors third-party libs under "pxr<Vendor>/" (ex.
        // pxrTslRobinMap/robin_map.h), included elsewhere via
        // "Tf/pxr<Vendor>/...". preserve as a real subdirectory -- flattening
        // leaves those includes resolving to stale copies.
        else if target == "Tf"
        {
          let tfPath = suffix.split(separator: "/").dropFirst(1).joined(separator: "/")
          if let vendorDir = tfPath.split(separator: "/").first,
            vendorDir.hasPrefix("pxr"), vendorDir.dropFirst(3).first?.isUppercase == true
          {
            sourceFile = tfPath
            preservesSubdirectory = true
          }
        }
        
        else if target == "Gf"
        {
          let gfPath = suffix.split(separator: "/").dropFirst(1).joined(separator: "/")
          if gfPath.hasPrefix("nc/")
          {
            sourceFile = gfPath
            preservesSubdirectory = true
          }
        }

        // rapidjson's own headers #include each other with paths relative
        // to "rapidjson/" (ex. "internal/meta.h", "../rapidjson.h",
        // "error/error.h"), and Js/json.cpp includes them as
        // "rapidjson/...". preserve rapidjson/ as a real subdirectory,
        // matching upstream's layout.
        else if target == "Js"
        {
          let jsPath = suffix.split(separator: "/").dropFirst(1).joined(separator: "/")
          if jsPath.hasPrefix("rapidjson/")
          {
            sourceFile = jsPath
            preservesSubdirectory = true
          }
        }

        // stbImage.cpp includes the vendored stb headers as "Hio/stb/...".
        // preserve stb/ as a real subdirectory, matching upstream's layout.
        else if target == "Hio"
        {
          let hioPath = suffix.split(separator: "/").dropFirst(1).joined(separator: "/")
          if hioPath.hasPrefix("stb/")
          {
            sourceFile = hioPath
            preservesSubdirectory = true
          }
        }

        // pxr headers must not have the name of the umbrella header, since
        // that collides on case-insensitive filesystems (ex. "tf.h" vs
        // the generated "Tf.h").
        if sourceFile.lowercased() == "\(target.lowercased()).h"
        {
          // so we suffix them with (ex. ar.h -> arImpl.h).
          sourceFile = "\(target.lowercased())Impl.h"
        }

        // workTBB/impl.h would collide with impl.h.in's configured
        // Work/impl.h output -- rename it. Patch.configureTemplate() points
        // @PXR_WORK_IMPL_HEADER@ at this same name.
        if source.path.hasSuffix("/workTBB/impl.h")
        {
          sourceFile = "implTBB.h"
        }

        let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(sourceFile)")

        if isConfigTemplate
        {
          // configure_file(): resolve CMake @VAR@ placeholders before the
          // normal include-rewriting pipeline runs.
          var template = try String(contentsOf: source, encoding: .utf8)
          Patch.configureTemplate(to: &template)
          try template.write(to: source, atomically: true, encoding: .utf8)
        }

        // ensure subdirectories (ex. Pegtl/internal/) exist before moving.
        try FileManager.default.createDirectory(at: dest.deletingLastPathComponent(), withIntermediateDirectories: true)

        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        log.info("updating header: \(dest.path)")
        updateSource(fileURL: dest, target: target, exclusions: exclusions)

        // headers like Tf/instantiateSingleton.h are meant to be included
        // once, directly by the .cpp that needs them -- keep out of umbrella.
        let blacklistedIncludes = [
          "tf.h",
          "instantiatePool.h",
          "instantiateSingleton.h",
          "instantiateStacked.h",
          "instantiateType.h",
          "pyModule.h",
          "CLI11.h",
        ]
        let includeOnceHeader = blacklistedIncludes.contains(where: dest.path.contains)
        
        // Garch's per-platform GL headers (ex. glPlatformContextDarwin.h,
        // glPlatformDebugWindowGLX.h) would pull in Windows.h/GL/glx.h on
        // every platform if added to the umbrella -- detect them by their
        // <Name><Platform>.h naming and leave them out, they're reachable
        // via their dispatcher header or own .cpp/.mm.
        let platformVariantHeader: Bool =
        {
          let baseName = (sourceFile as NSString).deletingPathExtension
          guard sourceFile.hasSuffix(".h") else { return false }
          
          if baseName.hasPrefix("glPlatform") {
            return ["Darwin", "GLX", "Windows"].contains { baseName.hasSuffix($0) }
          }
          
          // & not supporting vulkan quite yet.
          return baseName.lowercased().hasPrefix("hgivulkan") || baseName.lowercased().hasPrefix("vulkan")
        }()

        if !preservesSubdirectory && !includeOnceHeader && !platformVariantHeader
        {
          // generate this target's umbrella header, appending all its
          // headers to this single file.
          let umbrellaPath = "\(packagePath)/Sources/\(target)/include/\(target)/\(target).h"
          let umbrellaURL = URL(fileURLWithPath: umbrellaPath)
          generateUmbrellaHeader(fileURL: umbrellaURL, for: target, appending: sourceFile)
        }

        return dest
      }

      // ----- copy resources (Resources/, shaders/, textures/) ---

      // path of this file relative to its library (ex. "plugInfo.json",
      // "schema.usda", "shaders/simpleLighting.glslfx",
      // "examples/usdPhysicsJoints.usda").
      let libRelative = (isPluginLibrary ? suffixParts.dropFirst(2) : suffixParts.dropFirst(1)).joined(separator: "/")

      var resourceRelPath: String? = nil
      if ["plugInfo.json", "schema.usda", "generatedSchema.usda"].contains(libRelative) || libRelative.hasPrefix("examples/")
      {
        resourceRelPath = "Resources/\(libRelative)"
      }
      else if libRelative.hasPrefix("shaders/") || libRelative.hasPrefix("textures/")
      {
        resourceRelPath = libRelative
      }

      if let resourceRelPath,
         let resourceSubdir = resourceRelPath.split(separator: "/").first,
         existingResourceDirs.contains("\(target)/\(resourceSubdir)")
      {
        let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(resourceRelPath)")

        try FileManager.default.createDirectory(at: dest.deletingLastPathComponent(), withIntermediateDirectories: true)
        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        log.info("updating resource: \(dest.path)")

        if ["json", "usda", "usd", "glslfx"].contains(source.pathExtension.lowercased())
        {
          var resourceSrc = try String(contentsOf: dest, encoding: .utf8)

          if libRelative == "plugInfo.json"
          {
            Patch.pluginfoTemplate(to: &resourceSrc)
          }

          Patch.apply(to: &resourceSrc, fileURL: dest, target: target, relativePath: resourceRelPath)
          try resourceSrc.write(to: dest, atomically: true, encoding: .utf8)
        }
        else
        {
          // binary resource (ex. a texture) -- substitute a hand-edited
          // override wholesale, if one exists for this target.
          let overridePath = (Bundle.module.resourceURL?.path ?? ".") + "/Resources/\(target)/\(resourceRelPath)"
          if FileManager.default.fileExists(atPath: overridePath)
          {
            try? FileManager.default.removeItem(at: dest)
            try FileManager.default.copyItem(atPath: overridePath, toPath: dest.path)
          }
        }

        return dest
      }

      // ----------------------------------------------------------

      return nil
    }

    // ----- restore hand-written files with no upstream pixar -----
    // ----- counterpart (ex. Arch/swiftInterop.h) from Resources ---

    try restoreResourceOnlyFiles(packagePath: packagePath)

    return updatedFiles
  }

  /**
   * The Swift target names (ex. "Arch", "Tf", "UsdShade") for every library
   * this package's fresh upstream checkout contains, derived from the
   * top-level subdirectory names of `pxr/<rawValue>/`, plus the libs under
   * `pxr/<rawValue>/plugin/` (ex. "usdAbc" -> "UsdAbc").
   */
  private func targets(packagePath: String) -> [String]
  {
    let pxrDir = "\(packagePath)/.build/OpenUSD/pxr/\(rawValue)"
    guard let entries = try? FileManager.default.contentsOfDirectory(atPath: pxrDir)
    else { return [] }

    var result: [String] = []

    for entry in entries
    {
      // recurse into plugin/, it's a grouping dir, not a target itself.
      if entry == "plugin"
      {
        if let pluginEntries = try? FileManager.default.contentsOfDirectory(atPath: "\(pxrDir)/plugin")
        {
          for pluginEntry in pluginEntries
          {
            var target = pluginEntry.capitalized
            ensureCasing(for: &target)
            result.append(target)
          }
        }
        continue
      }

      var target = entry.capitalized
      ensureCasing(for: &target)
      result.append(target)
    }

    return result
  }

  /**
   * The `<Target>/Resources`, `shaders`, and `textures` dirs that already
   * exist on disk, before `enumerate()` nukes and repopulates them. only
   * dirs in this set get refreshed, so we don't create resource dirs
   * Package.swift doesn't declare for a target.
   */
  private func resourceDirectories(packagePath: String) -> Set<String>
  {
    var result: Set<String> = []

    for target in targets(packagePath: packagePath)
    {
      for subdir in ["Resources", "shaders", "textures"]
      {
        if FileManager.default.fileExists(atPath: "\(packagePath)/Sources/\(target)/\(subdir)")
        {
          result.insert("\(target)/\(subdir)")
        }
      }
    }

    return result
  }

  /**
   * Removes generated headers/sources for every target before `enumerate()`
   * repopulates them, so files upstream has since renamed or deleted don't
   * survive as stale leftovers.
   *
   *  - `Sources/<Target>/include/<Target>/` is removed entirely.
   *  - only top-level `.cpp`/`.cc`/`.c`/`.cxx`/`.m`/`.mm` files directly in
   *    `Sources/<Target>/` are removed -- other files (ex.
   *    `Gf/ilmbase_half.README`) aren't produced by `enumerate()`.
   *  - `Resources`/`shaders`/`textures` are removed, but only if already in
   *    `resourceDirectories`.
   *  - `Python/Py<Target>/` is left untouched -- hand-maintained.
   */
  private func nukeStaleTargetFiles(packagePath: String, resourceDirectories: Set<String>) throws
  {
    let sourceExtensions: Set<String> = ["m", "mm", "cpp", "cc", "c", "cxx"]

    for target in targets(packagePath: packagePath)
    {
      let targetDir = "\(packagePath)/Sources/\(target)"
      guard FileManager.default.fileExists(atPath: targetDir, isDirectory: nil) else { continue }

      try? FileManager.default.removeItem(atPath: "\(targetDir)/include/\(target)")

      for subdir in ["Resources", "shaders", "textures"] where resourceDirectories.contains("\(target)/\(subdir)")
      {
        try? FileManager.default.removeItem(atPath: "\(targetDir)/\(subdir)")
      }

      guard let topLevel = try? FileManager.default.contentsOfDirectory(atPath: targetDir)
      else { continue }

      for item in topLevel where sourceExtensions.contains((item as NSString).pathExtension)
      {
        try? FileManager.default.removeItem(atPath: "\(targetDir)/\(item)")
      }
    }
  }

  /**
   * Copies files from `Sources/OpenUSD/Resources/<Target>/` that have no
   * upstream pixar counterpart (ex. `Arch/swiftInterop.h`) into
   * `Sources/<Target>/...` -- `enumerate()`'s main loop never visits these,
   * and `Patch.apply` can only override existing files, not add new ones.
   * Skips files that already exist, and registers new headers in the
   * target's umbrella header.
   */
  private func restoreResourceOnlyFiles(packagePath: String) throws
  {
    guard let resourceRoot = Bundle.module.resourceURL?.appendingPathComponent("Resources")
    else { return }

    for target in targets(packagePath: packagePath)
    {
      let resourceDir = resourceRoot.appendingPathComponent(target)
      guard let files = try? FileManager.default.contentsOfDirectory(atPath: resourceDir.path)
      else { continue }

      for file in files
      {
        let ext = (file as NSString).pathExtension
        let isHeader = ["h", "hpp", "hxx"].contains(ext)
        let isSource = ["m", "mm", "cpp", "cc", "c", "cxx"].contains(ext)
        guard isHeader || isSource else { continue }

        let dest = isHeader
          ? URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(file)")
          : URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(file)")

        guard !FileManager.default.fileExists(atPath: dest.path) else { continue }

        try createTargetDirectories(packagePath: packagePath, target: target)
        try FileManager.default.copyItem(at: resourceDir.appendingPathComponent(file), to: dest)
        log.info("restoring resource-only file: \(dest.path)")

        if isHeader
        {
          let umbrellaPath = "\(packagePath)/Sources/\(target)/include/\(target)/\(target).h"
          generateUmbrellaHeader(fileURL: URL(fileURLWithPath: umbrellaPath), for: target, appending: file)
        }
      }

      // restore resource files (ex. "shaders/widgetShader.glslfx") with no
      // upstream counterpart -- nothing for enumerate() to copy.
      for subdir in ["Resources", "shaders", "textures"]
      {
        let subdirURL = resourceDir.appendingPathComponent(subdir)
        guard let enumerator = FileManager.default.enumerator(atPath: subdirURL.path)
        else { continue }

        for entry in enumerator
        {
          guard let relPath = entry as? String else { continue }

          let source = subdirURL.appendingPathComponent(relPath)
          var isDirectory: ObjCBool = false
          guard FileManager.default.fileExists(atPath: source.path, isDirectory: &isDirectory), !isDirectory.boolValue
          else { continue }

          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(subdir)/\(relPath)")
          guard !FileManager.default.fileExists(atPath: dest.path) else { continue }

          try FileManager.default.createDirectory(at: dest.deletingLastPathComponent(), withIntermediateDirectories: true)
          try FileManager.default.copyItem(at: source, to: dest)
          log.info("restoring resource-only file: \(dest.path)")
        }
      }
    }
  }

  private func generateUmbrellaHeader(fileURL: URL, for target: String, appending header: String)
  {
    do
    {
      // get the existing contents of the umbrella header, if any.
      var umbrellaHeader = (try? String(contentsOf: fileURL, encoding: .utf8)) ?? ""

      // check for the include guard (ex. '__PXR_BASE_ARCH_H__').
      let includeGuard = "__PXR_\(rawValue.uppercased())_\(target.uppercased())_H__"
      let skeletonPath = (Bundle.module.resourceURL?.path ?? ".") + "/Resources/\(target)/\(target).h"
      let skeleton = try? String(contentsOfFile: skeletonPath, encoding: .utf8)

      if !umbrellaHeader.contains("// __PXR_HEADERS__"), let skeleton, skeleton.contains("// __PXR_HEADERS__")
      {
        // some umbrellas have hand-edited structure (ex. Arch.h's
        // "#if defined(__cplusplus)" split) that a prior flattened
        // regeneration may have lost -- restore it from the skeleton in
        // Resources, which carries a "// __PXR_HEADERS__" marker for
        // where to insert.
        umbrellaHeader = skeleton
      }
      else if let guardRange = umbrellaHeader.range(of: "#ifndef \(includeGuard)")
      {
        // discard anything before the guard -- this path may collide
        // (case-insensitively) with a leftover pristine header (ex. tf.h).
        umbrellaHeader = String(umbrellaHeader[guardRange.lowerBound...])
      }
      else if let skeleton
      {
        umbrellaHeader = skeleton
      }
      else
      {
        // create the include guard opener if it does not exist.
        umbrellaHeader = "#ifndef \(includeGuard)\n#define \(includeGuard)\n\n// \(target)\n"
      }

      if umbrellaHeader.contains("#include <\(target)/\(header)>")
      {
        // already present, leave as-is.
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#include <\(target)/\(header)>", with: "#include <\(target)/\(header)>")
      }
      else if umbrellaHeader.contains("// __PXR_HEADERS__")
      {
        // insert at the marker, preserving hand-edited structure around it.
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "// __PXR_HEADERS__", with: "#include <\(target)/\(header)>\n// __PXR_HEADERS__")
      }
      else
      {
        // append new header entries.
        umbrellaHeader = umbrellaHeader.appending("#include <\(target)/\(header)>\n")
      }

      // check for the closing include guard (ex. '__PXR_BASE_ARCH_H__').
      if umbrellaHeader.contains("#endif  // \(includeGuard)") || umbrellaHeader.contains("#endif // \(includeGuard)")
      {
        // remove the closing guard -- it may no longer be at the bottom,
        // and re-running shouldn't keep appending blank lines.
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#endif  // \(includeGuard)\n", with: "")
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#endif // \(includeGuard)\n", with: "")
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#endif  // \(includeGuard)", with: "")
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#endif // \(includeGuard)", with: "")

        // re-append it to the end of the file.
        umbrellaHeader = umbrellaHeader.appending("#endif  // \(includeGuard)\n")
      }
      else
      {
        // append the closing include guard.
        umbrellaHeader = umbrellaHeader.appending("#endif  // \(includeGuard)\n")
      }

      // write the modified file contents back out to the umbrella header.
      try umbrellaHeader.write(to: fileURL, atomically: true, encoding: .utf8)
    }
    catch
    {
      log.error("error: failed to generate umbrella header '\(fileURL.path)'. \(error.localizedDescription).")
    }
  }

  private func updateSource(fileURL: URL, target: String, exclusions: SourceExclusions)
  {
    do
    {
      var pxrSrc = try String(contentsOf: fileURL, encoding: .utf8)

      /* apply any/all potential patches to upstream source files. */

      Patch.headers(to: &pxrSrc)
      Patch.xmacroFragmentHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.platformGuardedSource(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.arcRetainReleaseGuards(to: &pxrSrc, fileExtension: fileURL.pathExtension)
      Patch.pythonIncludes(to: &pxrSrc)
      Patch.pythonGuards(to: &pxrSrc, fileBaseName: fileURL.deletingPathExtension().lastPathComponent, pythonOnlyBasenames: exclusions.pythonOnly)
      Patch.addMissingTokens(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent, target: target)
      Patch.apply(to: &pxrSrc, fileURL: fileURL, target: target)

      /* 1. match includes such as:
       * #include "[pxr/base/tf]/token.h"
       * #include "[pxr/imaging/glf]/texture.h"
       * #include "[pxr/usd/sdf]/layer.h"
       * #include "[pxr/usdImaging/hd]/engine.h"
       * #include "[pxr/usd/plugin/usdAbc]/alembicData.h"
       * #include "[pxr/exec/execIr]/tokens.h" */
      let includeMatch = /(?:\G(?!\A)\s*,\s*|\b(?:pxr\/base\/|pxr\/imaging\/|pxr\/usd\/|pxr\/usdImaging\/|pxr\/exec\/)+(?:plugin\/)?)(\w+)/
      while let match = try includeMatch.firstMatch(in: pxrSrc)
      {
        /* 2. replace include with capitalized version.
         * #include "[pxr/base/tf]/token.h"        -> #include "Tf/token.h"
         * #include "[pxr/imaging/glf]/texture.h"  -> #include "Glf/texture.h"
         * #include "[pxr/usd/sdf]/layer.h"        -> #include "Sdf/layer.h"
         * #include "[pxr/usdImaging/hd]/engine.h" -> #include "Hd/engine.h"
         * #include "[pxr/usd/plugin/usdAbc]/alembicData.h" -> #include "UsdAbc/alembicData.h" */
        let include = pxrSrc[match.range]
        var newInclude = (include.split(separator: "/").last ?? "").capitalized

        ensureCasing(for: &newInclude)
        pxrSrc = pxrSrc.replacingOccurrences(of: include, with: newInclude)
      }

      // collapse vendored library include paths that end up doubled after
      // the capitalization above (ex. "Pegtl/pegtl/config.hpp" -> "Pegtl/config.hpp").
      Patch.vendoredIncludes(to: &pxrSrc, target: target)

      // rewrite references to a pristine header that collides (case-
      // insensitively) with this target's generated umbrella header, since
      // such headers are renamed on disk (ex. "Tf/tf.h" -> "Tf/tfImpl.h").
      Patch.collidingUmbrellaInclude(to: &pxrSrc, target: target)
      
      // because plain-C header/source code should not bring in Arch's entire
      // C++ clang module, which is problematic.
      Patch.nanocolorHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.openexrCSource(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)

      try pxrSrc.write(to: fileURL, atomically: true, encoding: .utf8)
    }
    catch
    {
      log.error("error: failed to update source '\(fileURL.path)'. \(error.localizedDescription).")
    }
  }

  /**
   * Create target directories for the given package.
   */
  private func createTargetDirectories(packagePath: String, target: String) throws
  {
    // create target directory, if it doesn't exist.
    let targetDir = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)")
    if FileManager.default.fileExists(atPath: targetDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetDir, withIntermediateDirectories: true, attributes: nil)
    }

    // create target include directory, if it doesn't exist.
    let targetIncDir = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)")
    if FileManager.default.fileExists(atPath: targetIncDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetIncDir, withIntermediateDirectories: true, attributes: nil)
    }
  }

  /**
   * Create python target directories for the given package.
   */
  private func createPythonDirectories(packagePath: String, target: String) throws
  {
    // create python target directory, if it doesn't exist.
    let targetPyDir = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)")
    if FileManager.default.fileExists(atPath: targetPyDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetPyDir, withIntermediateDirectories: true, attributes: nil)
    }

    // create python target include directory, if it doesn't exist.
    let targetPyIncDir = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/include/Py\(target)")
    if FileManager.default.fileExists(atPath: targetPyIncDir.path, isDirectory: nil) == false
    {
      try FileManager.default.createDirectory(at: targetPyIncDir, withIntermediateDirectories: true, attributes: nil)
    }
  }

  /**
   * Get the path from the given enumerator element.
   */
  private func path(from enumerated: NSEnumerator.Element) -> String
  {
    enumerated as? String ?? ""
  }

  /**
   * Canonical casing for targets where `.capitalized` gets it wrong (ex.
   * `usdImagingGL` -> `Usdimaginggl`, but the target is `UsdImagingGL`).
   * add new libraries with internal capitalization here.
   */
  private static let targetCasing: [String: String] = [
    "camerautil": "CameraUtil",
    "esfusd": "EsfUsd",
    "execgeom": "ExecGeom",
    "execir": "ExecIr",
    "execusd": "ExecUsd",
    "geomutil": "GeomUtil",
    "hdar": "HdAr",
    "hdgp": "HdGp",
    "hdmtlx": "HdMtlx",
    "hdsi": "HdSi",
    "hdst": "HdSt",
    "hdstorm": "HdStorm",
    "hgigl": "HgiGL",
    "hgiinterop": "HgiInterop",
    "hgimetal": "HgiMetal",
    "hgivulkan": "HgiVulkan",
    "hioopenvdb": "HioOpenVDB",
    "pxosd": "PxOsd",
    "sdrglslfx": "SdrGlslfx",
    "sdrosl": "SdrOsl",
    "usdabc": "UsdAbc",
    "usdapputils": "UsdAppUtils",
    "usddraco": "UsdDraco",
    "usdexecimaging": "UsdExecImaging",
    "usdgeom": "UsdGeom",
    "usdhydra": "UsdHydra",
    "usdimaging": "UsdImaging",
    "usdimaginggl": "UsdImagingGL",
    "usdirimaging": "UsdIRImaging",
    "usdlux": "UsdLux",
    "usdmedia": "UsdMedia",
    "usdmtlx": "UsdMtlx",
    "usdphysics": "UsdPhysics",
    "usdproc": "UsdProc",
    "usdprocimaging": "UsdProcImaging",
    "usdprofiles": "UsdProfiles",
    "usdrender": "UsdRender",
    "usdri": "UsdRi",
    "usdripxrimaging": "UsdRiPxrImaging",
    "usdsemantics": "UsdSemantics",
    "usdshade": "UsdShade",
    "usdshaders": "UsdShaders",
    "usdskel": "UsdSkel",
    "usdskelimaging": "UsdSkelImaging",
    "usdui": "UsdUI",
    "usdutils": "UsdUtils",
    "usdviewq": "UsdViewQ",
    "usdvol": "UsdVol",
    "usdvolimaging": "UsdVolImaging",
  ]

  /**
   * Fix casing via `targetCasing` (ex. `Usdimaginggl` -> `UsdImagingGL`).
   * targets already correct after `.capitalized` aren't in the table.
   */
  private func ensureCasing(for target: inout String)
  {
    if let canonical = Pxr.targetCasing[target.lowercased()]
    {
      target = canonical
    }
  }

  private enum Patch
  {
    /**
     * Overrides upstream source wholesale with the matching file from
     * Resources/<target>/<key>, if one exists -- this is where all wabi
     * modifications to openusd source live. `relativePath` lets resource
     * files (ex. "shaders/simpleLighting.glslfx") be matched by their path
     * under Resources/<target>/ instead of just their basename. */
    public static func apply(to source: inout String, fileURL: URL, target: String, relativePath: String? = nil)
    {
      // if a upstream source file matches a existing file in resources...

      let key = relativePath ?? fileURL.lastPathComponent
      let resourceDir = (Bundle.module.resourceURL?.path ?? ".") + "/Resources/\(target)/\(key)"
      guard
        FileManager.default.fileExists(atPath: resourceDir),
        let patch = FileManager.default.contents(atPath: resourceDir)
      else { return }

      // then, patch the upstream source with our resources file contents.

      log.info("patching source: \(fileURL.path)")
      source = String(decoding: patch, as: UTF8.self)
    }

    /**
     * Resolves `@PLUG_INFO_*@` placeholders that CMake's configure_file()
     * would normally fill in. SwiftUSD builds everything into one bundle,
     * so `LibraryPath` is empty (statically linked) and `ResourcePath`/
     * `Root` are ".". */
    public static func pluginfoTemplate(to source: inout String)
    {
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_LIBRARY_PATH@\"", with: "\"\"")
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_RESOURCE_PATH@\"", with: "\".\"")
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_ROOT@\"", with: "\".\"")
    }

    /**
     * Resolves CMake `@VAR@` placeholders in `.h.in` templates, the way
     * `configure_file()` would. `@PXR_WORK_IMPL_HEADER@` is impl.h.in's
     * only placeholder -- point it at Work/implTBB.h, matching the rename
     * `enumerate()` gives workTBB/impl.h. */
    public static func configureTemplate(to source: inout String)
    {
      source = source.replacingOccurrences(of: "@PXR_WORK_IMPL_HEADER@", with: "\"Work/implTBB.h\"")
    }

    /**
     * Collapses doubled directory segments left after the include-rewrite
     * loop capitalizes vendored lib prefixes (ex. `Pegtl/pegtl/config.hpp`
     * -> `Pegtl/config.hpp`). must run after that loop. */
    public static func vendoredIncludes(to source: inout String, target: String)
    {
      // only collapse the doubled directory segment (trailing slash) --
      // "Pegtl/pegtl.hpp" itself is a real header and must be left alone.
      source = source.replacingOccurrences(of: "Pegtl/pegtl/", with: "Pegtl/")
      source = source.replacingOccurrences(of: "Work/workTBB", with: "Work")
    }

    /**
     * Rewrites `#include "<Target>/<target>.h"` to `.../<target>Impl.h"`,
     * matching `enumerate()`'s rename of pristine headers that'd collide
     * (case-insensitively) with the generated umbrella (ex. `tf.h` ->
     * `tfImpl.h`, vs generated `Tf.h`). no-op if no such collision. */
    public static func collidingUmbrellaInclude(to source: inout String, target: String)
    {
      let lower = target.lowercased()
      for (open, close) in [("\"", "\""), ("<", ">")]
      {
        source = source.replacingOccurrences(
          of: "#include \(open)\(target)/\(lower).h\(close)",
          with: "#include \(open)\(target)/\(lower)Impl.h\(close)"
        )
      }
    }

    /**
     * `crateDataTypes.h` is an X-macro fragment `#include`-d inside an
     * `enum class TypeEnum { ... }` body. its leading
     * `#include "pxr/pxrns.h"` re-imports the module inside that enum body,
     * which trips `-Wmodules-import-nested-redundant`. strip it. */
    public static func xmacroFragmentHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "crateDataTypes.h" else { return }
      source = source.replacingOccurrences(of: "#include \"pxr/pxrns.h\"\n\n", with: "")
    }

    /**
     * Some libararies (from 'dev') reference tokens that do not yet exist, such as the in-development UsdExecImaging/UsdIRImaging
     * targets referencing nonexistent ExecIr tokens, minor modifications needed in order to pre-release these libraries with v26.05,
     * append them to their existing `*_TOKENS` declarations here. */
    public static func addMissingTokens(to source: inout String, fileBaseName: String, target: String)
    {
      guard fileBaseName == "tokens.h" else { return }
      
      if target == "ExecIr"
      {
        source = source.replacingOccurrences(
          of: "    ((outSpaceToken, \"Out:Space\"))\n",
          with: "    ((outSpaceToken, \"Out:Space\"))              \\\n"
            + "                                                \\\n"
            + "    ((posedSpace, \"posed:space\"))               \\\n"
            + "                                                \\\n"
            + "    ((guideDisplayColor, \"guide:displayColor\")) \\\n"
            + "    ((guideDisplayOpacity, \"guide:displayOpacity\")) \\\n"
            + "    ((guideLength, \"guide:length\"))\n"
        )
      }
    }

    /**
     * replace `ARCH_PRAGMA_UNUSED_FUNCTION` with a self-contained fallback instead,
     * so openexr-c.c (a plain-C source file) never needs to import the entire Arch C++ Clang module. */
    public static func openexrCSource(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "openexr-c.c" else { return }

      source = source.replacingOccurrences(of: "#include \"Arch/pragmas.h\"\n", with: "")
      source = source.replacingOccurrences(
        of: "ARCH_PRAGMA_UNUSED_FUNCTION",
        with: "#if defined(__clang__)\n"
          + "_Pragma(\"clang diagnostic ignored \\\"-Wunused-function\\\"\")\n"
          + "#elif defined(__GNUC__)\n"
          + "_Pragma(\"GCC diagnostic ignored \\\"-Wunused-function\\\"\")\n"
          + "#elif defined(_MSC_VER)\n"
          + "__pragma(warning(disable:4505))\n"
          + "#endif"
      )
    }

    /**
     * give NCAPI a self-contained fallback instead, so nanocolor.h (a plain-C header) never needs to import
     * the entire Arch C++ Clang module. */
    public static func nanocolorHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "nanocolor.h" else { return }

      source = source.replacingOccurrences(of: "#include \"Arch/export.h\"\n", with: "")
      source = source.replacingOccurrences(
        of: "#ifndef NCAPI\n#define NCAPI ARCH_HIDDEN\n#endif",
        with: """
        #ifndef NCAPI
        #  if defined(_WIN32) || defined(__CYGWIN__)
        #    define NCAPI
        #  elif defined(__GNUC__) || defined(__clang__)
        #    define NCAPI __attribute__((visibility("hidden")))
        #  else
        #    define NCAPI
        #  endif
        #endif
        """
      )
    }

    /**
     * Garch's per-platform GL `.cpp` variants (ex.
     * `glPlatformContextWindows.cpp`, `glPlatformDebugWindowGLX.cpp`) have
     * no guard of their own, so SwiftPM compiles all of them on every
     * platform -- wrap each in `#if` for its platform, mirroring the Darwin
     * `.mm` counterparts. idempotent: bails if guard already present. */
    public static func platformGuardedSource(to source: inout String, fileBaseName: String)
    {
      let guardMacro: String
      var prefix = ""
      switch fileBaseName
      {
      case "glPlatformContextWindows.cpp", "glPlatformDebugWindowWindows.cpp":
        guardMacro = "defined(_WIN32)"
      case "glPlatformContextGLX.cpp", "glPlatformDebugWindowGLX.cpp":
        guardMacro = "defined(__ANDROID__) || defined(__linux__)"
      case "vulkan.cpp":
        guardMacro = "0"
      case "metal.mm":
        // ARCH_OS_OSX isn't a compiler-predefined macro -- pull in
        // Arch/defines.h before checking it, matching the guard
        // hgiInterop.mm uses around its #include "HgiInterop/metal.h".
        guardMacro = "PXR_METAL_SUPPORT_ENABLED && defined(ARCH_OS_OSX)"
        prefix = "#include \"Arch/defines.h\"\n\n"
      default:
        return
      }

      guard !source.contains("#if \(guardMacro)") else { return }

      source = prefix + "#if \(guardMacro)\n\n" + source + "\n#endif // \(guardMacro)\n"
    }

    /**
     * Guards `#include "boost/python/..."` with
     * `#if PXR_PYTHON_SUPPORT_ENABLED`, since those headers aren't available
     * when python support is off. skipped if the file already has the
     * guard, so re-running doesn't re-wrap. */
    public static func pythonIncludes(to source: inout String)
    {
      // Package.swift always defines PXR_PYTHON_SUPPORT_ENABLED (to 0 or 1),
      // so #ifdef/#ifndef checks are always true/false. rewrite to value
      // checks so the macro's value is honored.
      source = source.replacingOccurrences(of: "#ifdef PXR_PYTHON_SUPPORT_ENABLED", with: "#if PXR_PYTHON_SUPPORT_ENABLED")
      source = source.replacingOccurrences(of: "#ifndef PXR_PYTHON_SUPPORT_ENABLED", with: "#if !PXR_PYTHON_SUPPORT_ENABLED")

      guard !source.contains("PXR_PYTHON_SUPPORT_ENABLED") else { return }

      let lines = source.components(separatedBy: "\n")
      var result: [String] = []
      result.reserveCapacity(lines.count)

      for line in lines
      {
        let trimmed = line.trimmingCharacters(in: .whitespaces)
        if trimmed.hasPrefix("#include"), trimmed.contains("boost/python")
        {
          result.append("#if PXR_PYTHON_SUPPORT_ENABLED")
          result.append(line)
          result.append("#endif // PXR_PYTHON_SUPPORT_ENABLED")
        }
        else
        {
          result.append(line)
        }
      }

      source = result.joined(separator: "\n")
    }

    /**
     * Wraps a file's body (everything after license/guard/#includes) in
     * `#if PXR_PYTHON_SUPPORT_ENABLED`, if its basename is in
     * `pythonOnlyBasenames` -- mirrors upstream CMake excluding these
     * entirely when python support is off. no-op otherwise. */
    public static func pythonGuards(to source: inout String, fileBaseName: String, pythonOnlyBasenames: Set<String>)
    {
      guard pythonOnlyBasenames.contains(fileBaseName) else { return }

      let lines = source.components(separatedBy: "\n")

      // find end of preamble (license/guard/#includes) -- track `/* */`
      // blocks so #if/#endif-looking text inside one (ex.
      // scriptModuleLoader.cpp's notes) isn't mistaken for real directives.
      var bodyStart = 0
      var inBlockComment = false
      while bodyStart < lines.count
      {
        let trimmed = lines[bodyStart].trimmingCharacters(in: .whitespaces)
        if inBlockComment
        {
          if trimmed.contains("*/") { inBlockComment = false }
          bodyStart += 1
          continue
        }
        if trimmed.hasPrefix("/*")
        {
          if !trimmed.contains("*/") { inBlockComment = true }
          bodyStart += 1
          continue
        }
        if trimmed.isEmpty || trimmed.hasPrefix("//") || trimmed.hasPrefix("#")
        {
          bodyStart += 1
          continue
        }
        break
      }
      guard bodyStart < lines.count else { return }

      // for headers, the trailing `#endif` closes the `#ifndef`/`#define`
      // include guard and must remain outside the wrapper.
      var bodyEnd = lines.count
      while bodyEnd > bodyStart, lines[bodyEnd - 1].trimmingCharacters(in: .whitespaces).isEmpty
      {
        bodyEnd -= 1
      }
      var trailingGuardEndif: String? = nil
      if bodyEnd > bodyStart, lines[bodyEnd - 1].trimmingCharacters(in: .whitespaces).hasPrefix("#endif")
      {
        trailingGuardEndif = lines[bodyEnd - 1]
        bodyEnd -= 1
        while bodyEnd > bodyStart, lines[bodyEnd - 1].trimmingCharacters(in: .whitespaces).isEmpty
        {
          bodyEnd -= 1
        }
      }

      var result = Array(lines[0..<bodyStart])
      result.append("#if PXR_PYTHON_SUPPORT_ENABLED")
      result.append(contentsOf: lines[bodyStart..<bodyEnd])
      result.append("#endif // PXR_PYTHON_SUPPORT_ENABLED")
      if let trailingGuardEndif
      {
        result.append("")
        result.append(trailingGuardEndif)
      }

      source = result.joined(separator: "\n")
    }

    /**
     * Patches openusd headers for the pxr namespace, tbb headers, etc. */
    public static func headers(to source: inout String)
    {
      /* ----- pxr namespace headers. ----- */

      source = source.replacingOccurrences(of: "pxr/pxr.h", with: "pxr/pxrns.h")
      
      /* ----- umbrella collisions. ------- */
      
      // we never want to bring in the entire tf module (umbrella header),
      // we want openusd's tf.h header implementation that we renamed to
      // tf/tfImpl.h (see `collidingUmbrellaInclude(to:target:)`).
      source = source.replacingOccurrences(of: "tf/tf.h", with: "Tf/tfImpl.h")
      source = source.replacingOccurrences(of: "trace/trace.h", with: "Trace/traceImpl.h")
      source = source.replacingOccurrences(of: "ar/ar.h", with: "Ar/arImpl.h")
      
      /* ----- pxr external headers. ----- */

      source = source.replacingOccurrences(of: "pxr/external/", with: "")
      
      /* ----- hgi headers. -------------- */

      source = source.replacingOccurrences(of: "#include \"shaderSection.h\"", with: "#include \"Hgi/shaderSection.h\"")
      
      // bad things happen if you attempt to import a module's own umbrella into itself.
      source = source.replacingOccurrences(of: "hgiInterop.h", with: "hgiInteropImpl.h")
      
      source = source.replacingOccurrences(of: "#if defined(PXR_GL_SUPPORT_ENABLED)", with: "#if PXR_GL_SUPPORT_ENABLED")
      source = source.replacingOccurrences(of: "#if defined(PXR_VULKAN_SUPPORT_ENABLED)", with: "#if PXR_VULKAN_SUPPORT_ENABLED")
      source = source.replacingOccurrences(of: "#if defined(PXR_METAL_SUPPORT_ENABLED)", with: "#if PXR_METAL_SUPPORT_ENABLED")
      
      /* ------ refbase ------------------- */

      source = source.replacingOccurrences(of: "virtual ~SdfLayer();", with: "virtual ~SdfLayer() noexcept;")
      source = source.replacingOccurrences(of: "virtual ~UsdStage();", with: "virtual ~UsdStage() noexcept;")

      /* ----- tbb headers. --------------- */

      // currently, metaversekit places tbb in a OneTBB parent directory, so add that here.
      // the normal <tbb/xxx.h> include paths can only be utilized once Swift on Linux is
      // fixed, possibly as soon as Swift 6, refer to the following PR:
      // https://github.com/swiftlang/swift/pull/75662
      source = source.replacingOccurrences(of: "#include \"tbb/concurrent_queue.h\"", with: "#include <OneTBB/tbb/concurrent_queue.h>")
      source = source.replacingOccurrences(of: "#include \"tbb/concurrent_unordered_map.h\"", with: "#include <OneTBB/tbb/concurrent_unordered_map.h>")
      source = source.replacingOccurrences(of: "#include \"tbb/concurrent_vector.h\"", with: "#include <OneTBB/tbb/concurrent_vector.h>")
      source = source.replacingOccurrences(of: "#include \"tbb/concurrent_hash_map.h\"", with: "#include <OneTBB/tbb/concurrent_hash_map.h>")
      source = source.replacingOccurrences(of: "#include \"tbb/concurrent_unordered_set.h\"", with: "#include <OneTBB/tbb/concurrent_unordered_set.h>")
      source = source.replacingOccurrences(of: "<tbb/", with: "<OneTBB/tbb/")
      // modern versions of tbb no longer have atomic, get it from std.
      source = source.replacingOccurrences(of: "<tbb/atomic.h>", with: "<atomic>")
      source = source.replacingOccurrences(of: "tbb::atomic", with: "std::atomic")
      // modern versions of tbb no longer have mutex, get it from std.
      source = source.replacingOccurrences(of: "<tbb/mutex.h>", with: "<mutex>")
      source = source.replacingOccurrences(of: "tbb::mutex", with: "std::mutex")
      // modern versions of tbb no longer contain a task_scheduler_init.
      source = source.replacingOccurrences(of: "#include <tbb/task_scheduler_init.h>", with: "#if WITH_TBB_LEGACY\n#include <OneTBB/tbb/task_scheduler_init.h>\n#endif /* WITH_TBB_LEGACY */")

      /* ---- materialx headers ----------- */

      source = source.replacingOccurrences(of: "#include <MaterialXCore/Document.h>", with: "#include <MaterialX/MXCoreDocument.h>")
      source = source.replacingOccurrences(of: "#include <MaterialXCore/Util.h>", with: "#include <MaterialX/MXCoreUtil.h>")
      source = source.replacingOccurrences(of: "#include <MaterialXFormat/Util.h>", with: "#include <MaterialX/MXFormatUtil.h>")
      source = source.replacingOccurrences(of: "#include <MaterialXFormat/XmlIo.h>", with: "#include <MaterialX/MXFormatXmlIo.h>")

      /* ---- opensubdiv headers ----------- */

      // MetaverseKit's OpenSubdiv module exposes a flattened
      // "OpenSubdiv/OSD*.h" set, not upstream's "opensubdiv/<lib>/<header>.h"
      // layout -- rewrite PxOsd/HdSt's includes to match.
      let openSubdivHeaders: [(String, String)] = [
        ("opensubdiv/version.h", "OpenSubdiv/OSDVersion.h"),
        ("opensubdiv/far/topologyRefiner.h", "OpenSubdiv/OSDAdaptiveTopologyRefiner.h"),
        ("opensubdiv/far/topologyRefinerFactory.h", "OpenSubdiv/OSDAdaptiveTopologyRefinerFactory.h"),
        ("opensubdiv/far/patchTable.h", "OpenSubdiv/OSDAdaptivePatchTable.h"),
        ("opensubdiv/far/patchTableFactory.h", "OpenSubdiv/OSDAdaptivePatchTableFactory.h"),
        ("opensubdiv/far/stencilTable.h", "OpenSubdiv/OSDAdaptiveStencilTable.h"),
        ("opensubdiv/far/stencilTableFactory.h", "OpenSubdiv/OSDAdaptiveStencilTableFactory.h"),
        ("opensubdiv/osd/mtlPatchShaderSource.h", "OpenSubdiv/OSDSurfaceMTLPatchShaderSource.h"),
        ("opensubdiv/osd/glslPatchShaderSource.h", "OpenSubdiv/OSDSurfaceGLSLPatchShaderSource.h"),
      ]
      for (upstream, flattened) in openSubdivHeaders
      {
        source = source.replacingOccurrences(of: "#include <\(upstream)>", with: "#include <\(flattened)>")
      }
      
      /* ---- nanocolor headers ------------ */
      
      source = source.replacingOccurrences(of: "#include \"nc/nanocolor.h\"", with: "#include \"nanocolor.h\"")
      
      /* ---- gf headers ------------------- */
      
      source = source.replacingOccurrences(of: "#include \"colorSpace_data.h\"", with: "#include \"Gf/colorSpace_data.h\"")

      /* ---- metal types ------------------ */

      // `didModifyRange:` is on MTLBuffer, not MTLResource --
      // HgiMetalBlitCmds::CopyTextureCpuToGpu assigns to an
      // id<MTLResource> local before calling it.
      source = source.replacingOccurrences(of: "id<MTLResource> resource = metalBuffer->GetBufferId();", with: "id<MTLBuffer> resource = metalBuffer->GetBufferId();")

      /* ---- objc id -> void* bridging ---- */

      // GarchSelectCoreProfileMacVisual returns void*, but
      // NSOpenGLPixelFormat alloc is an objc object pointer -- needs an
      // explicit __bridge cast.
      source = source.replacingOccurrences(of: "return [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];", with: "return (__bridge void*)[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];")

      // GetRawResource() returns a uint64_t, but id<MTLTexture> is an objc
      // object pointer -- a C-style cast from integer to objc pointer is
      // disallowed under ARC, so round-trip through void* with __bridge.
      source = source.replacingOccurrences(of: "colorTexture = id<MTLTexture>(color->GetRawResource());", with: "colorTexture = (__bridge id<MTLTexture>)(void*)color->GetRawResource();")
      source = source.replacingOccurrences(of: "depthTexture = id<MTLTexture>(depth->GetRawResource());", with: "depthTexture = (__bridge id<MTLTexture>)(void*)depth->GetRawResource();")
    }

    /**
     * Guards `retain`/`release` calls in `.m`/`.mm` files with
     * `#if !__has_feature(objc_arc)`, since they're a compile error under
     * ARC but required without it. consecutive retain/release-only lines
     * are wrapped together. lines already inside such a guard are left
     * as-is. */
    public static func arcRetainReleaseGuards(to source: inout String, fileExtension: String)
    {
      guard fileExtension == "m" || fileExtension == "mm" else { return }

      let retainReleaseLine = /^\s*\[.+\s(?:retain|release)\];\s*$/

      let lines = source.components(separatedBy: "\n")
      var result: [String] = []
      result.reserveCapacity(lines.count)

      var ifDepth = 0
      var arcGuardDepth = 0

      var i = 0
      while i < lines.count
      {
        let line = lines[i]
        let trimmed = line.trimmingCharacters(in: .whitespaces)

        if trimmed.hasPrefix("#if")
        {
          ifDepth += 1
          if trimmed.contains("!__has_feature(objc_arc)")
          {
            arcGuardDepth = ifDepth
          }
          result.append(line)
          i += 1
          continue
        }

        if trimmed.hasPrefix("#endif")
        {
          if ifDepth == arcGuardDepth { arcGuardDepth = 0 }
          ifDepth -= 1
          result.append(line)
          i += 1
          continue
        }

        if arcGuardDepth == 0, (try? retainReleaseLine.firstMatch(in: line)) != nil
        {
          var group: [String] = []
          while i < lines.count, (try? retainReleaseLine.firstMatch(in: lines[i])) != nil
          {
            group.append(lines[i])
            i += 1
          }

          result.append("#if !__has_feature(objc_arc)")
          result.append(contentsOf: group)
          result.append("#endif // !__has_feature(objc_arc)")
          continue
        }

        result.append(line)
        i += 1
      }

      source = result.joined(separator: "\n")
    }
  }
}
