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

import ArgumentParser
import Foundation

/**
 * The subcommand for changing the pixar
 * usd version for a specified package.
 */
struct UpdateCommand: AsyncCommand
{
  static var configuration = CommandConfiguration(
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
    // Validate parameters
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

    // Start timing
    let elapsed = try await Stopwatch.time
    {
      // 1. clone pixar official openusd repository.
      try Command.git.run(with: ["clone", "https://github.com/PixarAnimationStudios/OpenUSD.git", "\(pkgDir)/.build/OpenUSD"])

      // 2. update all usd source in this package, in parallel.
      async let bse = try Pxr.base.enumerate(packagePath: pkgDir)
      async let img = try Pxr.imaging.enumerate(packagePath: pkgDir)
      async let usd = try Pxr.usd.enumerate(packagePath: pkgDir)
      async let uim = try Pxr.usdImaging.enumerate(packagePath: pkgDir)

      // 3. wait for all usd source to be updated.
      let _ = try await [bse, img, usd, uim]
    }

    // Output the time elapsed and app bundle location
    log.info("done in \(elapsed.secondsString). usd source updated at '\(pkgDir)'.")
  }
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

  /**
   * List the given package path, updating the source files for this
   * package from upstream pixar, and return a list of updated files.
   */
  public func enumerate(packagePath: String) async throws -> [URL]
  {
    // ------------- list all files in the directory -------------

    guard let list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/\(rawValue)")
    else { log.critical("Failed to list \(rawValue) directory."); return [] }

    // ---------------- process each file in list ----------------

    return try list.compactMap
    { pxrPath in

      // ----------- determine target and source paths -----------

      let suffix = path(from: pxrPath).split(separator: "pxr/\(rawValue)/").last ?? ""
      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")
      var target = (suffix.split(separator: "/").first ?? "").capitalized

      ensureCasing(for: &target)

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
        platformExcludes
      { return nil }

      // --------------- create target directories ---------------

      try createTargetDirectories(packagePath: packagePath, target: target)
      try createPythonDirectories(packagePath: packagePath, target: target)

      var sourceFile = source.lastPathComponent
      ensureSourceFilename(in: target, for: &sourceFile)

      // ------ copy source files to dest (Sources/Target/*) -----

      if ["cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if sourceFile.contains("wrap") || sourceFile.contains("module")
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(sourceFile)")

          // move wrap and module files to Python/PyTarget/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating python module: \(dest.path)")
          updateSource(fileURL: dest, target: target)

          return dest
        }
        else
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(sourceFile)")

          // move source files to Sources/Target/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating source: \(dest.path)")
          updateSource(fileURL: dest, target: target)

          return dest
        }
      }

      // ----- copy headers (Sources/Target/include/Target/*) -----

      if ["h", "hpp", "hxx"].contains(source.pathExtension)
      {
        // pxr headers must not have the name of the umbrella header.
        if sourceFile == "\(target.first?.lowercased() ?? "").h"
        {
          // so we suffix them with (ex. ar.h -> arImpl.h).
          sourceFile = "\(target.first?.lowercased() ?? "")Impl.h"
        }

        let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(sourceFile)")

        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        log.info("updating header: \(dest.path)")
        updateSource(fileURL: dest, target: target)

        // generate this target's umbrella header...

        let umbrellaPath = "\(packagePath)/Sources/\(target)/include/\(target)/\(target).h"
        if !FileManager.default.fileExists(atPath: umbrellaPath, isDirectory: nil)
        {
          // copying over the existing umbrella header's file contents...
          let contents = FileManager.default.contents(atPath: umbrellaPath)

          // creating the umbrella header file if it does not exist...
          FileManager.default.createFile(atPath: umbrellaPath, contents: contents, attributes: nil)
        }

        // and appending all its headers to this single file.
        let umbrellaURL = URL(fileURLWithPath: umbrellaPath)
        generateUmbrellaHeader(fileURL: umbrellaURL, for: target, appending: sourceFile)

        return dest
      }

      // ----------------------------------------------------------

      return nil
    }
  }

  private func generateUmbrellaHeader(fileURL: URL, for target: String, appending header: String)
  {
    do
    {
      // get the existing contents of the umbrella header.
      var umbrellaHeader = try String(contentsOf: fileURL, encoding: .utf8)

      // check for the include guard (ex. '__PXR_BASE_ARCH_H__').
      let includeGuard = "__PXR_\(rawValue.uppercased())_\(target.uppercased())_H__"
      if !umbrellaHeader.contains("#ifndef \(includeGuard)")
      {
        // create the include guard opener if it does not exist.
        umbrellaHeader = umbrellaHeader.appending("#ifndef \(includeGuard)\n")
        umbrellaHeader = umbrellaHeader.appending("#define \(includeGuard)\n\n")
        umbrellaHeader = umbrellaHeader.appending("// \(target)\n")
      }

      if umbrellaHeader.contains("#include <\(target)/\(header)>")
      {
        // copy existing header entries in place to keep sorted, and mark the source as edited.
        umbrellaHeader = umbrellaHeader.replacingOccurrences(of: "#include <\(target)/\(header)>", with: "#include <\(target)/\(header)>")
      }
      else
      {
        // append new header entries.
        umbrellaHeader = umbrellaHeader.appending("#include <\(target)/\(header)>\n")
      }

      // check for the closing include guard (ex. '__PXR_BASE_ARCH_H__').
      if umbrellaHeader.contains("#endif  // \(includeGuard)") || umbrellaHeader.contains("#endif // \(includeGuard)")
      {
        // remove the closing include guard, since it may no longer be at the bottom of the file.
        // additional checks so we do not incidentally keep appending endless new lines each time
        // we update openusd source code.
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

  private func updateSource(fileURL: URL, target: String)
  {
    do
    {
      var pxrSrc = try String(contentsOf: fileURL, encoding: .utf8)

      /* apply any/all potential patches to upstream source files. */

      Patch.headers(to: &pxrSrc)
      Patch.apply(to: &pxrSrc, fileURL: fileURL, target: target)

      /* 1. match includes such as:
       * #include "[pxr/base/tf]/token.h"
       * #include "[pxr/imaging/glf]/texture.h"
       * #include "[pxr/usd/sdf]/layer.h"
       * #include "[pxr/usdImaging/hd]/engine.h" */
      let includeMatch = /(?:\G(?!\A)\s*,\s*|\b(?:pxr\/base\/|pxr\/imaging\/|pxr\/usd\/|pxr\/usdImaging\/)+)(\w+)/
      while let match = try includeMatch.firstMatch(in: pxrSrc)
      {
        /* 2. replace include with capitalized version.
         * #include "[pxr/base/tf]/token.h"        -> #include "Tf/token.h"
         * #include "[pxr/imaging/glf]/texture.h"  -> #include "Glf/texture.h"
         * #include "[pxr/usd/sdf]/layer.h"        -> #include "Sdf/layer.h"
         * #include "[pxr/usdImaging/hd]/engine.h" -> #include "Hd/engine.h" */
        let include = pxrSrc[match.range]
        var newInclude = (include.split(separator: "/").last ?? "").capitalized

        ensureCasing(for: &newInclude)
        pxrSrc = pxrSrc.replacingOccurrences(of: include, with: newInclude)

        // fixes any conflicting headers (ex. Arch/errno.h -> Arch/errno.h)
        ensureSourceFilename(in: target, for: &pxrSrc)
      }

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
   * Ensure the source filename is correct for the given path.
   */
  private func ensureSourceFilename(in target: String, for source: inout String)
  {
    switch self
    {
      case .base:
        if target.contains("Arch")
        {
          // since these names conflict with stdlib, we prefix them with pxr.
          source = source.replacingOccurrences(of: "Arch/errno.h", with: "Arch/errno.h")
          source = source.replacingOccurrences(of: "Arch/inttypes.h", with: "Arch/inttypes.h")
          source = source.replacingOccurrences(of: "Arch/math.h", with: "Arch/math.h")
          source = source.replacingOccurrences(of: "Arch/regex.h", with: "Arch/regex.h")
        }
      default:
        break
    }
  }

  /**
   * Ensure the casing is correct for the given target.
   */
  private func ensureCasing(for target: inout String)
  {
    for suffix in ["imaging", "app", "utils", "st", "physics", "mtlx", "gp", "proc", "vol", "skel", "util", "media"]
    {
      if target.contains(suffix)
      {
        target = target.replacingOccurrences(of: suffix, with: suffix.capitalized)
      }
    }

    if target.contains("Geom")
    {
      target = target.replacingOccurrences(of: "util", with: "Util")
    }

    if target.contains("Hgi")
    {
      target = target.replacingOccurrences(of: "metal", with: "Metal")
      target = target.replacingOccurrences(of: "gl", with: "GL")
      target = target.replacingOccurrences(of: "vulkan", with: "Vulkan")
      target = target.replacingOccurrences(of: "interop", with: "Interop")
    }

    if target.contains("Hio")
    {
      target = target.replacingOccurrences(of: "open", with: "Open")
      target = target.replacingOccurrences(of: "vdb", with: "VDB")
    }

    if target.contains("Px")
    {
      target = target.replacingOccurrences(of: "osd", with: "Osd")
    }

    if target.contains("Usd")
    {
      target = target.replacingOccurrences(of: "geom", with: "Geom")
      target = target.replacingOccurrences(of: "lux", with: "Lux")
      target = target.replacingOccurrences(of: "ri", with: "Ri")
      target = target.replacingOccurrences(of: "pxr", with: "Pxr")
      target = target.replacingOccurrences(of: "gl", with: "GL")
      target = target.replacingOccurrences(of: "render", with: "Render")
      target = target.replacingOccurrences(of: "hydra", with: "Hydra")
      target = target.replacingOccurrences(of: "viewq", with: "ViewQ")
      target = target.replacingOccurrences(of: "shade", with: "Shade")
      target = target.replacingOccurrences(of: "ui", with: "UI")
    }

    if target.contains("Hd")
    {
      target = target.replacingOccurrences(of: "ar", with: "Ar")
      target = target.replacingOccurrences(of: "si", with: "Si")
    }
  }

  private enum Patch
  {
    /**
     * Patches upstream pixar's openusd source code, with the contents of
     * any matching target/filename(.h|.cpp) in resources, this is so that
     * any changes that are required for openusd to work with swift, will
     * survive future releases of openusd, while also making any potential
     * modifications to openusd source code easy to maintain, and clearly
     * defined, all wabi openusd source code modifications will live here. */
    public static func apply(to source: inout String, fileURL: URL, target: String)
    {
      // if a upstream source file matches a existing file in resources...

      let resourceDir = (Bundle.module.resourceURL?.path ?? ".") + "/\(target)/\(fileURL.lastPathComponent)"
      guard
        FileManager.default.fileExists(atPath: resourceDir),
        let patch = FileManager.default.contents(atPath: resourceDir)
      else { return }

      // then, patch the upstream source with our resources file contents.

      log.info("patching source: \(fileURL.path)")
      source = String(decoding: patch, as: UTF8.self)
    }

    /**
     * Patches openusd headers for the pxr namespace, tbb headers, etc. */
    public static func headers(to source: inout String)
    {
      /* ----- pxr namespace headers. ----- */

      source = source.replacingOccurrences(of: "pxr/pxr.h", with: "pxr/pxrns.h")

      // since these names conflict with stdlib, we prefix them with pxr.
      source = source.replacingOccurrences(of: "Arch/errno.h", with: "Arch/errno.h")
      source = source.replacingOccurrences(of: "Arch/inttypes.h", with: "Arch/inttypes.h")
      source = source.replacingOccurrences(of: "Arch/math.h", with: "Arch/math.h")
      source = source.replacingOccurrences(of: "Arch/regex.h", with: "Arch/regex.h")

      /* ------ refbase ------------------- */

      source = source.replacingOccurrences(of: "virtual ~SdfLayer();", with: "virtual ~SdfLayer() noexcept;")
      source = source.replacingOccurrences(of: "virtual ~UsdStage();", with: "virtual ~UsdStage() noexcept;")

      /* ----- tbb headers. --------------- */

      // currently, metaversekit places tbb in a OneTBB parent directory, so add that here.
      // the normal <tbb/xxx.h> include paths can only be utilized once Swift on Linux is
      // fixed, possibly as soon as Swift 6, refer to the following PR:
      // https://github.com/swiftlang/swift/pull/75662
      source = source.replacingOccurrences(of: "<tbb/", with: "<OneTBB/tbb/")
      // modern versions of tbb no longer have atomic, get it from std.
      source = source.replacingOccurrences(of: "<tbb/atomic.h>", with: "<atomic>")
      source = source.replacingOccurrences(of: "tbb::atomic", with: "std::atomic")
      // not a safe assumption, migration to modern tbb requires slightly more intricate changes.
      // source = source.replacingOccurrences(of: "fetch_and_decrement()", with: "fetch_sub(1)")
      // source = source.replacingOccurrences(of: "fetch_and_increment()", with: "fetch_add(1)")
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
    }
  }
}
