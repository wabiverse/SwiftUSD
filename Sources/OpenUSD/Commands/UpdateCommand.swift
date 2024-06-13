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

/// The subcommand for creating app bundles for a package.
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
    var packageDirectory: URL = URL(fileURLWithPath: ".")

    // Start timing
    let elapsed = try await Stopwatch.time
    {
      if let pkgDir = arguments.packageDirectory
      {
        packageDirectory = pkgDir
      }

      // 1. clone the pixar usd repository.
      if FileManager.default.fileExists(atPath: "\(packageDirectory.path)/.build/OpenUSD", isDirectory: nil)
      {
        try FileManager.default.removeItem(atPath: "\(packageDirectory.path)/.build/OpenUSD")
      }
      try Command.git.run(with: ["clone", "https://github.com/PixarAnimationStudios/USD.git", "\(packageDirectory.path)/.build/OpenUSD"])

      // 2. loop pxr.base and copy respective library source to Sources/**.
      try Pxr.base.enumerate(packagePath: packageDirectory.path)

      // 3. loop pxr.imaging and copy respective library source to Sources/**.
      try Pxr.imaging.enumerate(packagePath: packageDirectory.path)

      // 4. loop pxr.usd and copy respective library source to Sources/**.
      try Pxr.usd.enumerate(packagePath: packageDirectory.path)

      // 5. loop pxr.usdImaging and copy respective library source to Sources/**.
      try Pxr.usdImaging.enumerate(packagePath: packageDirectory.path)
    }

    // Output the time elapsed and app bundle location
    log.info(
      "Done in \(elapsed.secondsString). USD source updated at '\(packageDirectory.relativePath)'"
    )
  }
}

func path(from enumerated: NSEnumerator.Element) -> String
{
  return enumerated as? String ?? ""
}

public enum Pxr: String
{
  case base
  case imaging
  case usd
  case usdImaging

  public func enumerate(packagePath: String) throws
  {
    var list: NSEnumerator? = nil

    switch self
    {
      case .base:
        list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/base")
      case .imaging:
        list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/imaging")
      case .usd:
        list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/usd")
      case .usdImaging:
        list = FileManager.default.enumerator(atPath: "\(packagePath)/.build/OpenUSD/pxr/usdImaging")
    }

    try list?.forEach
    { pxrPath in
      let suffix = path(from: pxrPath).split(separator: "pxr/\(rawValue)/").last ?? ""
      let target = (suffix.split(separator: "/").first ?? "").capitalized

      let source = URL(fileURLWithPath: ".build/OpenUSD/pxr/\(rawValue)/\(path(from: pxrPath))")
      if source.path.contains("testenv")
      {
        return
      }
      print("updating source:", source.path)

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

      let cxxDestination = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/\(source.lastPathComponent)")
      let hppDestination = URL(fileURLWithPath: "\(packagePath)/Sources/\(target)/include/\(target)/\(source.lastPathComponent)")
      let pyCxxDestination = URL(fileURLWithPath: "\(packagePath)/Python/Py\(target)/\(source.lastPathComponent)")

      // copy source files to destination (Sources/Target/*)
      if ["cpp", "cc", "c", "cxx"].contains(source.pathExtension)
      {
        if source.lastPathComponent.contains("wrap") || source.lastPathComponent.contains("module")
        {
          // move wrap and module files to Python/PyTarget/*
          try? FileManager.default.removeItem(at: pyCxxDestination)
          try FileManager.default.moveItem(at: source, to: pyCxxDestination) 
        }
        else
        {
          // move source files to Sources/Target/*
          try? FileManager.default.removeItem(at: cxxDestination)
          try FileManager.default.moveItem(at: source, to: cxxDestination) 
        }
      }

      // copy header files to destination (Sources/Target/include/Target/*)
      if ["h", "hpp", "hxx"].contains(source.pathExtension)
      {
        try? FileManager.default.removeItem(at: hppDestination)
        try FileManager.default.moveItem(at: source, to: hppDestination)
      }
    }
  }
}
