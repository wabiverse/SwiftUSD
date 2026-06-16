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

public struct SourceExclusions: Sendable
{
  let pythonOnly: Set<String>
  let testOnly: Set<String>

  public init(checkoutRoot: String)
  {
    pythonOnly = collectPythonOnlyBasenames(checkoutRoot: checkoutRoot)
    testOnly = collectTestingFiles(checkoutRoot: checkoutRoot)
  }
}

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

public enum Pxr: String, CaseIterable
{
  case base
  case imaging
  case usd
  case usdImaging
  case exec

  public func enumerate(packagePath: String, exclusions: SourceExclusions) async throws -> [URL]
  {
    guard let list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/\(rawValue)")
    else { log.critical("Failed to list \(rawValue) directory."); return [] }

    let existingResourceDirs = resourceDirectories(packagePath: packagePath)
    try nukeStaleTargetFiles(packagePath: packagePath, resourceDirectories: existingResourceDirs)

    let updatedFiles: [URL] = try list.compactMap
    { pxrPath in

      let suffix = path(from: pxrPath).split(separator: "pxr/\(rawValue)/").last ?? ""
      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")
      let suffixParts = suffix.split(separator: "/")

      // plugin/ is a grouping dir; the actual target name is the second component.
      let isPluginLibrary = suffixParts.first == "plugin"
      var target = String((isPluginLibrary ? suffixParts.dropFirst().first : suffixParts.first) ?? "").capitalized
      ensureCasing(for: &target)

      // skip plugins with no Sources/<Target> (hioAvif, hdEmbree, etc.).
      let isUnbuiltPlugin = isPluginLibrary && !FileManager.default.fileExists(atPath: "\(packagePath)/Sources/\(target)")

      #if os(Windows)
        let platformExcludes = false
      #else
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

      if ["m", "mm", "cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if sourceFile.contains("wrap") || sourceFile.contains("module")
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(sourceFile)")
          let priorPy = try? String(contentsOf: dest, encoding: .utf8)
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          if updateSource(fileURL: dest, target: target, exclusions: exclusions, priorContent: priorPy) {
            log.info("updating python module: \(dest.path)")
          }

          return dest
        }
        else
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(sourceFile)")
          let priorSrc = try? String(contentsOf: dest, encoding: .utf8)
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          if updateSource(fileURL: dest, target: target, exclusions: exclusions, priorContent: priorSrc) {
            log.info("updating source: \(dest.path)")
          }

          return dest
        }
      }

      // CMake configure_file() templates (ex. "impl.h.in" -> "impl.h").
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

        let priorHeader = try? String(contentsOf: dest, encoding: .utf8)
        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        if updateSource(fileURL: dest, target: target, exclusions: exclusions, priorContent: priorHeader) {
          log.info("updating header: \(dest.path)")
        }

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
          // X-macro data fragment, only valid when included inside an enum/switch body.
          "crateDataTypes.h",
          // Private implementation header: includes crateDataTypes.h inside an enum
          // body which Clang modules can't handle (converts #include to module import).
          "crateFile.h",
          // Python boost binding utility header (uses pxr_boost::python, PyObject).
          "wrapUtils.h",
          // TF_WRAP(...) fragment file, only valid inside a Python module registration
          // body, not a standalone compilable header.
          "generatedSchema.module.h",
          // Raw data fragments - designed to be #included inside array/struct
          // declarations in .cpp files; not valid as standalone headers.
          "ilmbase_eLut.h",
          "ilmbase_toFloat.h",
          // Private nested struct definition for GfColorSpace::_Data; only valid
          // after GfColorSpace is declared (included mid-class in colorSpace.h).
          "colorSpace_data.h",
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
        let priorResource = try? String(contentsOf: dest, encoding: .utf8)
        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)

        if ["json", "usda", "usd", "glslfx"].contains(source.pathExtension.lowercased())
        {
          var resourceSrc = try String(contentsOf: dest, encoding: .utf8)

          if libRelative == "plugInfo.json"
          {
            Patch.pluginfoTemplate(to: &resourceSrc)
          }

          Patch.apply(to: &resourceSrc, fileURL: dest, target: target, relativePath: resourceRelPath)

          if libRelative == "plugInfo.json"
          {
            Patch.pluginfoName(to: &resourceSrc, target: target)
          }
          if libRelative == "schema.usda" || libRelative == "generatedSchema.usda"
          {
            Patch.schemaUsda(to: &resourceSrc, target: target)
          }

          if priorResource != resourceSrc {
            try resourceSrc.write(to: dest, atomically: true, encoding: .utf8)
            log.info("updating resource: \(dest.path)")
          }
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
          // always log binary resources can't cheaply diff binary content
          log.info("updating resource: \(dest.path)")
        }

        return dest
      }

      return nil
    }

    try restoreResourceOnlyFiles(packagePath: packagePath)

    return updatedFiles
  }

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

  // Removes generated headers/sources so stale upstream renames/deletes don't survive across runs.
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

  // Copies Resources/<Target>/ files with no upstream counterpart into Sources/<Target>/ (e.g. swiftInterop.h).
  private func restoreResourceOnlyFiles(packagePath: String) throws
  {
    guard let resourceRoot = Bundle.module.resourceURL
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

      // Tf umbrella: pxrTslRobinMap must precede all other Tf headers so dependent modules see it via the module system.
      if target == "Tf", !umbrellaHeader.contains("<Tf/pxrTslRobinMap/robin_map.h>")
      {
        let mark = "#define \(includeGuard)\n"
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: mark, with: "\(mark)#include <Tf/pxrTslRobinMap/robin_map.h>\n#include <Tf/pxrTslRobinMap/robin_set.h>\n")
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

  @discardableResult
  private func updateSource(fileURL: URL, target: String, exclusions: SourceExclusions, priorContent: String? = nil) -> Bool
  {
    do
    {
      var pxrSrc = try String(contentsOf: fileURL, encoding: .utf8)

      /* apply any/all potential patches to upstream source files. */

      Patch.headers(to: &pxrSrc)
      Patch.xmacroFragmentHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.fileSystemHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.cleanupTrackerHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.predicateExpressionParserHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
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
      
      // rewrite same-directory double-quote includes to angle-bracket module
      // includes, required by SwiftPM's layout where all headers live under
      // include/<Target>/. For files in a preserved subdirectory (e.g.
      // Pegtl/internal/), pass the subdirectory so intra-subdir includes
      // resolve to <Target/subdir/file> instead of the flattened <Target/file>.
      let includeRoot = "include/\(target)/"
      let subdirectory: String? = {
        let p = fileURL.path
        guard let r = p.range(of: includeRoot) else { return nil }
        let rel = String(p[r.upperBound...])  // e.g. "internal/rules.hpp" or "foo.h"
        let parts = rel.split(separator: "/")
        guard parts.count > 1 else { return nil }
        return parts.dropLast().joined(separator: "/")
      }()
      Patch.sameDirectoryIncludes(to: &pxrSrc, target: target, subdirectory: subdirectory)

      // because plain-C header/source code should not bring in Arch's entire
      // C++ clang module, which is problematic.
      Patch.nanocolorHeader(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.openexrCSource(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)
      Patch.materialXShaderGen(to: &pxrSrc, fileBaseName: fileURL.lastPathComponent)

      let changed = priorContent.map { $0 != pxrSrc } ?? true
      try pxrSrc.write(to: fileURL, atomically: true, encoding: .utf8)
      return changed
    }
    catch
    {
      log.error("error: failed to update source '\(fileURL.path)'. \(error.localizedDescription).")
      return false
    }
  }

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

  private func path(from enumerated: NSEnumerator.Element) -> String
  {
    enumerated as? String ?? ""
  }

  // Canonical casing for targets where .capitalized gets it wrong (e.g. UsdImagingGL -> Usdimaginggl).
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

  private func ensureCasing(for target: inout String)
  {
    if let canonical = Pxr.targetCasing[target.lowercased()]
    {
      target = canonical
    }
  }

  private enum Patch
  {
    /** Overrides upstream source wholesale with Resources/<target>/<key> if it exists. */
    public static func apply(to source: inout String, fileURL: URL, target: String, relativePath: String? = nil)
    {
      let key = relativePath ?? fileURL.lastPathComponent
      let resourceDir = (Bundle.module.resourceURL?.path ?? ".") + "/Resources/\(target)/\(key)"
      guard
        FileManager.default.fileExists(atPath: resourceDir),
        let patch = FileManager.default.contents(atPath: resourceDir)
      else { return }

      log.info("patching source: \(fileURL.path)")
      source = String(decoding: patch, as: UTF8.self)
    }

    /** Resolves @PLUG_INFO_*@ CMake placeholders (statically linked bundle; ResourcePath = "."). */
    public static func pluginfoTemplate(to source: inout String)
    {
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_LIBRARY_PATH@\"", with: "\"\"")
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_RESOURCE_PATH@\"", with: "\".\"")
      source = source.replacingOccurrences(of: "\"@PLUG_INFO_ROOT@\"", with: "\".\"")
    }

    /** Fixes plugInfo.json "Name" to use SwiftUSD capitalized target name (e.g. "usdGeom" -> "UsdGeom"). */
    public static func pluginfoName(to source: inout String, target: String)
    {
      let lower = target.prefix(1).lowercased() + target.dropFirst()
      source = source.replacingOccurrences(of: "\"Name\": \"\(lower)\"", with: "\"Name\": \"\(target)\"")
    }

    /** Patches schema.usda: fixes libraryName/libraryPath, pxr/ includes, and subLayer paths to SwiftUSD conventions. */
    public static func schemaUsda(to source: inout String, target: String)
    {
      let lower = target.prefix(1).lowercased() + target.dropFirst()

      // libraryName/libraryPath: strip pxr/ prefix, capitalize to match SwiftUSD target.
      source = source.replacingOccurrences(of: "= \"\(lower)\"",           with: "= \"\(target)\"")
      source = source.replacingOccurrences(of: "= \"pxr/base/\(lower)\"",  with: "= \"\(target)\"")
      source = source.replacingOccurrences(of: "= \"pxr/usd/\(lower)\"",   with: "= \"\(target)\"")

      // pxr/ includes embedded in customData C++ snippets -> SwiftUSD target paths.
      for (pxr, swift) in [
        ("pxr/base/gf/",      "Gf/"),
        ("pxr/base/tf/",      "Tf/"),
        ("pxr/usd/sdf/",      "Sdf/"),
        ("pxr/usd/sdr/",      "Sdr/"),
        ("pxr/usd/usd/",      "Usd/"),
        ("pxr/usd/usdGeom/",  "UsdGeom/"),
        ("pxr/usd/usdShade/", "UsdShade/"),
        ("pxr/usd/usdLux/",   "UsdLux/"),
        ("pxr/usd/usdSkel/",  "UsdSkel/"),
        ("pxr/usd/usdVol/",   "UsdVol/"),
        ("pxr/usd/usdPhysics/","UsdPhysics/"),
        ("pxr/usd/usdRender/","UsdRender/"),
        ("pxr/usd/usdRi/",    "UsdRi/"),
      ] {
        source = source.replacingOccurrences(of: "\"\(pxr)", with: "\"\(swift)")
      }

      // subLayer references: @usd/schema.usda@ -> @Usd/schema.usda@ etc.
      for (lower, upper) in [
        ("usd/schema.usda",     "Usd/schema.usda"),
        ("usdGeom/schema.usda", "UsdGeom/schema.usda"),
        ("usdShade/schema.usda","UsdShade/schema.usda"),
      ] {
        source = source.replacingOccurrences(of: "@\(lower)@", with: "@\(upper)@")
      }
    }

    /** Resolves @PXR_WORK_IMPL_HEADER@ in impl.h.in to Work/implTBB.h (matching enumerate()'s rename). */
    public static func configureTemplate(to source: inout String)
    {
      source = source.replacingOccurrences(of: "@PXR_WORK_IMPL_HEADER@", with: "\"Work/implTBB.h\"")
    }

    /** Collapses doubled directory segments from vendored-lib prefix capitalisation (e.g. Pegtl/pegtl/ -> Pegtl/). */
    public static func vendoredIncludes(to source: inout String, target: String)
    {
      source = source.replacingOccurrences(of: "Pegtl/pegtl/", with: "Pegtl/")
      source = source.replacingOccurrences(of: "Work/workTBB",  with: "Work")
    }

    /** Rewrites #include "<Target>/<target>.h" -> <target>Impl.h to avoid umbrella-name collisions. */
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

    /** crateDataTypes.h is an X-macro fragment; strip its pxrns.h import to avoid redundant-module-import inside enum body. */
    public static func xmacroFragmentHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "crateDataTypes.h" else { return }
      source = source.replacingOccurrences(of: "#include \"pxr/pxrns.h\"\n\n", with: "")
    }

    /** Hoists <limits.h>/<sys/param.h> above PXR_NAMESPACE_OPEN_SCOPE in fileSystem.h (modules forbid sys includes inside namespaces). */
    public static func fileSystemHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "fileSystem.h" else { return }
      source = source.replacingOccurrences(
        of: "PXR_NAMESPACE_OPEN_SCOPE\n\n/// \\addtogroup group_arch_SystemFunctions\n///@{\n#if !defined(ARCH_OS_WINDOWS)\n    #ifdef _POSIX_VERSION\n        #include <limits.h>                     /* for PATH_MAX */\n    #else\n        #include <sys/param.h>                  /* for MAXPATHLEN */\n    #endif\n#else",
        with: "#if !defined(ARCH_OS_WINDOWS)\n    #ifdef _POSIX_VERSION\n        #include <limits.h>                     /* for PATH_MAX */\n    #else\n        #include <sys/param.h>                  /* for MAXPATHLEN */\n    #endif\n#endif\n\nPXR_NAMESPACE_OPEN_SCOPE\n\n/// \\addtogroup group_arch_SystemFunctions\n///@{\n#if defined(ARCH_OS_WINDOWS)"
      )
    }

    /** Hoists #include <vector> above PXR_NAMESPACE_OPEN_SCOPE in cleanupTracker.h. */
    public static func cleanupTrackerHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "cleanupTracker.h" else { return }
      source = source.replacingOccurrences(
        of: "#include \"Sdf/spec.h\"\n\nPXR_NAMESPACE_OPEN_SCOPE\n\nSDF_DECLARE_HANDLES(SdfSpec);\n\n#include <vector>",
        with: "#include \"Sdf/spec.h\"\n\n#include <vector>\n\nPXR_NAMESPACE_OPEN_SCOPE\n\nSDF_DECLARE_HANDLES(SdfSpec);"
      )
    }

    /** Replaces duplicate-default-arg fwd-decl of Sdf_EvalQuotedString with #include parserHelpers.h before the namespace. */
    public static func predicateExpressionParserHeader(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "predicateExpressionParser.h" else { return }
      // Replace: fwd-decl inside namespace -> include parserHelpers.h before namespace
      source = source.replacingOccurrences(
        of: "#include <memory>\n\nPXR_NAMESPACE_OPEN_SCOPE\n\n// fwd decl, from parserHelpers.cpp.\nstd::string\nSdf_EvalQuotedString(const char* x, size_t n,\n                     size_t trimBothSides, unsigned int* numLines=NULL);",
        with: "#include <memory>\n\n#include \"Sdf/parserHelpers.h\"\n\nPXR_NAMESPACE_OPEN_SCOPE"
      )
    }

    /** Appends missing token declarations for in-dev targets (e.g. ExecIr tokens needed by UsdExecImaging). */
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

    /** Replaces ARCH_PRAGMA_UNUSED_FUNCTION with inline _Pragma equivalent so openexr-c.c avoids importing the Arch C++ module. */
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

    /** MaterialX 1.38.X TypeDesc has no operator==; use getName() string comparison. */
    public static func materialXShaderGen(to source: inout String, fileBaseName: String)
    {
      guard fileBaseName == "materialXShaderGen.cpp" else { return }
      for (old, new) in [
        ("return typeDesc == *mx::Type::NONE;",          "return typeDesc.getName() == mx::Type::NONE->getName();"),
        ("return typeDesc == *mx::Type::SURFACESHADER;", "return typeDesc.getName() == mx::Type::SURFACESHADER->getName();"),
        ("return typeDesc == *mx::Type::FILENAME;",      "return typeDesc.getName() == mx::Type::FILENAME->getName();"),
      ] { source = source.replacingOccurrences(of: old, with: new) }
    }

    /** Rewrites double-quote same-directory includes to angle-bracket module includes (e.g. "foo.h" -> <Target/foo.h>). subdirectory preserves vendored sub-paths. */
    public static func sameDirectoryIncludes(to source: inout String, target: String, subdirectory: String? = nil)
    {
      // Apple SDK header - angle brackets.
      source = source.replacingOccurrences(of: "#include \"TargetConditionals.h\"", with: "#include <TargetConditionals.h>")

      // Gf/nc/ vendored nanocolor sub-library.
      source = source.replacingOccurrences(of: "#include \"nanocolor.h\"", with: "#include <Gf/nc/nanocolor.h>")

      // Tf/pxrLZ4/ vendored LZ4 sub-library.
      source = source.replacingOccurrences(of: "#include \"lz4.h\"", with: "#include <Tf/pxrLZ4/lz4.h>")

      // Tf/pxrDoubleConversion/ vendored double-conversion sub-library.
      if target == "Tf"
      {
        for h in ["bignum.h", "bignum-dtoa.h", "cached-powers.h", "diy-fp.h",
                  "double-to-string.h", "fast-dtoa.h", "fixed-dtoa.h", "ieee.h",
                  "string-to-double.h", "strtod.h", "utils.h"]
        {
          source = source.replacingOccurrences(of: "#include \"\(h)\"", with: "#include <Tf/pxrDoubleConversion/\(h)>")
        }
        // Tf/pxrTslRobinMap/ vendored robin-map sub-library. The general rule below
        // would produce <Tf/robin_hash.h> etc. (flattened), but the files live under
        // pxrTslRobinMap/ and must be included with that sub-path.
        for h in ["robin_hash.h", "robin_growth_policy.h", "robin_map.h", "robin_set.h"]
        {
          source = source.replacingOccurrences(of: "#include \"\(h)\"", with: "#include <Tf/pxrTslRobinMap/\(h)>")
        }
      }

      // general rule: any remaining `#include "X.h"` with no path separator ->
      // `#include <Target/X.h>` (top-level) or `#include <Target/subdir/X.h>` when
      // the file lives in a preserved subdirectory (e.g. Pegtl/internal/).
      guard let regex = try? NSRegularExpression(pattern: #"#include "([^/"]+\.(?:h|hpp|hxx))""#)
      else { return }

      let nsSource = source as NSString
      let range = NSRange(location: 0, length: nsSource.length)
      let prefix = subdirectory.map { "\(target)/\($0)" } ?? target
      source = regex.stringByReplacingMatches(in: source, range: range, withTemplate: "#include <\(prefix)/$1>")
    }

    /** Replaces ARCH_HIDDEN-based NCAPI in nanocolor.h with a self-contained visibility macro (avoids importing Arch C++ module). */
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

    /** Wraps platform-specific Garch .cpp variants in #if guards (SwiftPM compiles all sources; upstream relied on CMake exclusion). */
    public static func platformGuardedSource(to source: inout String, fileBaseName: String)
    {
      let guardMacro: String
      var prefix = ""
      switch fileBaseName
      {
      case "glPlatformContextDarwin.mm", "glPlatformDebugWindowDarwin.mm":
        guardMacro = "defined(__APPLE__)"
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

    /** Guards boost/python includes and rewrites #ifdef->#if checks for PXR_PYTHON_SUPPORT_ENABLED. */
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

    /** Wraps python-only files in #if PXR_PYTHON_SUPPORT_ENABLED (mirrors CMake's source exclusion when python is off). */
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

    /** Global source patches: namespace, include paths, ABI fixes. */
    public static func headers(to source: inout String)
    {
      source = source.replacingOccurrences(of: "pxr/pxr.h",    with: "pxr/pxrns.h")
      source = source.replacingOccurrences(of: "pxr/external/", with: "")

      // Impl-renamed umbrella headers (see collidingUmbrellaInclude).
      source = source.replacingOccurrences(of: "tf/tf.h",      with: "Tf/tfImpl.h")
      source = source.replacingOccurrences(of: "trace/trace.h", with: "Trace/traceImpl.h")
      source = source.replacingOccurrences(of: "ar/ar.h",      with: "Ar/arImpl.h")
      source = source.replacingOccurrences(of: "hgi/hgi.h",    with: "Hgi/hgiImpl.h")
      source = source.replacingOccurrences(of: "hgiInterop.h", with: "hgiInteropImpl.h")

      source = source.replacingOccurrences(of: "#include \"pegtl/",           with: "#include \"Pegtl/")
      source = source.replacingOccurrences(of: "#include \"pxr/imaging/hdsi/", with: "#include \"HdSi/")
      source = source.replacingOccurrences(of: "#include \"shaderSection.h\"",  with: "#include \"Hgi/shaderSection.h\"")

      // Inject Tf_RetainReleaseHelper friendship alongside Tf_RefPtr_Counter.
      source = source.replacingOccurrences(of: "friend struct Tf_RefPtr_Counter;", with: "friend struct Tf_RefPtr_Counter;\n    friend class Tf_RetainReleaseHelper;")

      // vt/dictionary.h + sdf/types.h included inside a namespace - hoist around it.
      source = source.replacingOccurrences(
        of: "#include \"pxr/base/vt/dictionary.h\"\n#include \"pxr/usd/sdf/types.h\"",
        with: "PXR_NAMESPACE_CLOSE_SCOPE\n#include \"pxr/base/vt/dictionary.h\"\n#include \"pxr/usd/sdf/types.h\"\nPXR_NAMESPACE_OPEN_SCOPE"
      )

      // Normalize feature-flag macros from defined() to direct #if form.
      source = source.replacingOccurrences(of: "#if defined(PXR_GL_SUPPORT_ENABLED)",     with: "#if PXR_GL_SUPPORT_ENABLED")
      source = source.replacingOccurrences(of: "#if defined(PXR_VULKAN_SUPPORT_ENABLED)", with: "#if PXR_VULKAN_SUPPORT_ENABLED")
      source = source.replacingOccurrences(of: "#if defined(PXR_METAL_SUPPORT_ENABLED)",  with: "#if PXR_METAL_SUPPORT_ENABLED")

      // noexcept on virtual dtors avoids ABI-mismatch warnings.
      source = source.replacingOccurrences(of: "virtual ~SdfLayer();", with: "virtual ~SdfLayer() noexcept;")
      source = source.replacingOccurrences(of: "virtual ~UsdStage();", with: "virtual ~UsdStage() noexcept;")

      // TF_FATAL_ERROR / TF_RUNTIME_ERROR: printf-style macros - pass c_str() for std::string args.
      source = source.replacingOccurrences(
        of: "TF_FATAL_ERROR(\"Attempted to get value for key '\" + key +\n                       \"', which is not in the dictionary.\");",
        with: "TF_FATAL_ERROR(\"Attempted to get value for key '%s', \"\n                       \"which is not in the dictionary.\", key.c_str());"
      )
      source = source.replacingOccurrences(of: "TF_RUNTIME_ERROR(errs);", with: "TF_RUNTIME_ERROR(\"%s\", errs.c_str());")

      // TBB: MetaverseKit places tbb under OneTBB/; deprecated atomic/mutex/task_scheduler_init -> std.
      source = source.replacingOccurrences(of: "<tbb/", with: "<OneTBB/tbb/")
      source = source.replacingOccurrences(of: "\"tbb/", with: "\"OneTBB/tbb/")
      source = source.replacingOccurrences(of: "<tbb/atomic.h>", with: "<atomic>")
      source = source.replacingOccurrences(of: "tbb::atomic", with: "std::atomic")
      source = source.replacingOccurrences(of: "<tbb/mutex.h>", with: "<mutex>")
      source = source.replacingOccurrences(of: "tbb::mutex", with: "std::mutex")
      source = source.replacingOccurrences(of: "#include <OneTBB/tbb/task_scheduler_init.h>",
        with: "#if WITH_TBB_LEGACY\n#include <OneTBB/tbb/task_scheduler_init.h>\n#endif")

      // MaterialX: upstream uses per-submodule paths; MetaverseKit exposes a flat MX*.h layout.
      let materialXHeaders: [(String, String)] = [
        ("MaterialXCore/Document.h",                         "MaterialX/MXCoreDocument.h"),
        ("MaterialXCore/Util.h",                             "MaterialX/MXCoreUtil.h"),
        ("MaterialXCore/Library.h",                          "MaterialX/MXCoreLibrary.h"),
        ("MaterialXCore/Node.h",                             "MaterialX/MXCoreNode.h"),
        ("MaterialXCore/Value.h",                            "MaterialX/MXCoreValue.h"),
        ("MaterialXCore/Generated.h",                        "MaterialX/MXCoreGenerated.h"),
        ("MaterialXFormat/Util.h",                           "MaterialX/MXFormatUtil.h"),
        ("MaterialXFormat/XmlIo.h",                          "MaterialX/MXFormatXmlIo.h"),
        ("MaterialXFormat/Environ.h",                        "MaterialX/MXFormatEnviron.h"),
        ("MaterialXGenShader/Shader.h",                      "MaterialX/MXGenShader.h"),
        ("MaterialXGenShader/ShaderGenerator.h",             "MaterialX/MXGenShaderGenerator.h"),
        ("MaterialXGenShader/Syntax.h",                      "MaterialX/MXGenShaderSyntax.h"),
        ("MaterialXGenShader/Util.h",                        "MaterialX/MXGenShaderUtil.h"),
        ("MaterialXGenShader/DefaultColorManagementSystem.h","MaterialX/MXGenShaderDefaultColorManagementSystem.h"),
        ("MaterialXGenGlsl/GlslShaderGenerator.h",           "MaterialX/MXGenGlslShaderGenerator.h"),
        ("MaterialXGenGlsl/Nodes/SurfaceNodeGlsl.h",         "MaterialX/MXGenGlslSurfaceNodeGlsl.h"),
        ("MaterialXGenGlsl/VkShaderGenerator.h",             "MaterialX/MXGenGlslVkShaderGenerator.h"),
        ("MaterialXGenMsl/MslShaderGenerator.h",             "MaterialX/MXGenMslShaderGenerator.h"),
        ("MaterialXGenMsl/Nodes/SurfaceNodeMsl.h",           "MaterialX/MXGenMslSurfaceNodeMsl.h"),
        ("MaterialXGenMsl/MslResourceBindingContext.h",      "MaterialX/MXGenMslResourceBindingContext.h"),
        ("MaterialXRender/Util.h",                           "MaterialX/MXRenderUtil.h"),
        ("MaterialXRender/LightHandler.h",                   "MaterialX/MXRenderLightHandler.h"),
        ("MaterialXRenderGlsl/TextureBaker.h",               "MaterialX/MXRenderGlslTextureBaker.h"),
      ]
      for (upstream, flat) in materialXHeaders
      {
        source = source.replacingOccurrences(of: "#include <\(upstream)>", with: "#include <\(flat)>")
      }

      // OpenSubdiv: upstream uses "opensubdiv/<lib>/<hdr>"; MetaverseKit exposes flat "OpenSubdiv/OSD*.h".
      let openSubdivHeaders: [(String, String)] = [
        ("opensubdiv/version.h",                    "OpenSubdiv/OSDVersion.h"),
        ("opensubdiv/far/topologyRefiner.h",        "OpenSubdiv/OSDAdaptiveTopologyRefiner.h"),
        ("opensubdiv/far/topologyRefinerFactory.h", "OpenSubdiv/OSDAdaptiveTopologyRefinerFactory.h"),
        ("opensubdiv/far/patchTable.h",             "OpenSubdiv/OSDAdaptivePatchTable.h"),
        ("opensubdiv/far/patchTableFactory.h",      "OpenSubdiv/OSDAdaptivePatchTableFactory.h"),
        ("opensubdiv/far/stencilTable.h",           "OpenSubdiv/OSDAdaptiveStencilTable.h"),
        ("opensubdiv/far/stencilTableFactory.h",    "OpenSubdiv/OSDAdaptiveStencilTableFactory.h"),
        ("opensubdiv/osd/mtlPatchShaderSource.h",   "OpenSubdiv/OSDSurfaceMTLPatchShaderSource.h"),
        ("opensubdiv/osd/glslPatchShaderSource.h",  "OpenSubdiv/OSDSurfaceGLSLPatchShaderSource.h"),
      ]
      for (upstream, flattened) in openSubdivHeaders
      {
        source = source.replacingOccurrences(of: "#include <\(upstream)>", with: "#include <\(flattened)>")
      }
      
      source = source.replacingOccurrences(of: "#include \"nc/nanocolor.h\"",      with: "#include \"nanocolor.h\"")
      source = source.replacingOccurrences(of: "#include \"colorSpace_data.h\"",   with: "#include \"Gf/colorSpace_data.h\"")

      // didModifyRange: is on MTLBuffer, not MTLResource.
      source = source.replacingOccurrences(of: "id<MTLResource> resource = metalBuffer->GetBufferId();", with: "id<MTLBuffer> resource = metalBuffer->GetBufferId();")

      // ObjC id -> void* bridging: NSOpenGLPixelFormat alloc needs __bridge for a void* return.
      source = source.replacingOccurrences(of: "return [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];", with: "return (__bridge void*)[[NSOpenGLPixelFormat alloc] initWithAttributes:attribs];")

      // GetRawResource() is uint64_t; C-style cast to id<MTLTexture> disallowed under ARC - go via void*.
      source = source.replacingOccurrences(of: "colorTexture = id<MTLTexture>(color->GetRawResource());", with: "colorTexture = (__bridge id<MTLTexture>)(void*)color->GetRawResource();")
      source = source.replacingOccurrences(of: "depthTexture = id<MTLTexture>(depth->GetRawResource());", with: "depthTexture = (__bridge id<MTLTexture>)(void*)depth->GetRawResource();")
    }

    /** Wraps [obj retain]/[obj release] lines in #if !__has_feature(objc_arc) guards (.m/.mm only). */
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
