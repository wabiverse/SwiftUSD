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
      try Command.git.run(with: ["clone", "https://github.com/PixarAnimationStudios/USD.git", "\(pkgDir)/.build/OpenUSD"])

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
      let target = (suffix.split(separator: "/").first ?? "").capitalized
      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")

      // ---------------- skip testenv directories ---------------

      if source.path.contains("testenv") { return nil }

      // --------------- create target directories ---------------

      try createTargetDirectories(packagePath: packagePath, target: target)
      try createPythonDirectories(packagePath: packagePath, target: target)

      // ------ copy source files to dest (Sources/Target/*) -----

      if ["cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if source.lastPathComponent.contains("wrap") || source.lastPathComponent.contains("module")
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(source.lastPathComponent)")

          // move wrap and module files to Python/PyTarget/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating python module: \(dest.path)")
          updateSource(fileURL: dest)

          return dest
        }
        else
        {
          let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(source.lastPathComponent)")

          // move source files to Sources/Target/*
          try? FileManager.default.removeItem(at: dest)
          try FileManager.default.moveItem(at: source, to: dest)
          log.info("updating source: \(dest.path)")
          updateSource(fileURL: dest)

          return dest
        }
      }

      // ----- copy headers (Sources/Target/include/Target/*) -----

      if ["h", "hpp", "hxx"].contains(source.pathExtension)
      {
        let dest = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(source.lastPathComponent)")

        try? FileManager.default.removeItem(at: dest)
        try FileManager.default.moveItem(at: source, to: dest)
        log.info("updating header: \(dest.path)")
        updateSource(fileURL: dest)

        return dest
      }

      // ----------------------------------------------------------

      return nil
    }
  }

  private func updateSource(fileURL: URL)
  {
    do
    {
      let contents = try String(contentsOf: fileURL, encoding: .utf8)
      let pxrns = contents.replacingOccurrences(of: "pxr/pxr.h", with: "pxr/pxrns.h")

      var source = pxrns.replacingOccurrences(of: "pxr/\(Pxr.base.rawValue)/", with: "")
      source = source.replacingOccurrences(of: "pxr/\(Pxr.imaging.rawValue)/", with: "")
      source = source.replacingOccurrences(of: "pxr/\(Pxr.usd.rawValue)/", with: "")
      source = source.replacingOccurrences(of: "pxr/\(Pxr.usdImaging.rawValue)/", with: "")

      try source.write(to: fileURL, atomically: true, encoding: .utf8)
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
}
