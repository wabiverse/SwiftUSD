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
import PackagePlugin

@main
struct UsdGenSchemaPlugin: CommandPlugin
{
  /// This entry point is called when operating on a Swift package.
  func performCommand(context: PluginContext, arguments: [String]) throws
  {
    let genSchema = try context.tool(named: "UsdGenSchema")

    try run(command: genSchema.path, with: arguments)
  }
}

#if canImport(XcodeProjectPlugin)
  import XcodeProjectPlugin

  extension UsdGenSchemaPlugin: XcodeCommandPlugin
  {
    /// This entry point is called when operating on an Xcode project.
    func performCommand(context: XcodePluginContext, arguments: [String]) throws
    {
      let genSchema = try context.tool(named: "UsdGenSchema")

      try run(command: genSchema.path, with: arguments)
    }
  }
#endif

extension UsdGenSchemaPlugin
{
  /// Run a command with the given arguments.
  func run(command: Path, with arguments: [String]) throws
  {
    let exec = URL(fileURLWithPath: command.string)

    let process = try Process.run(exec, arguments: arguments)
    process.waitUntilExit()

    // Check whether the subprocess invocation was successful.
    if process.terminationReason == .exit,
       process.terminationStatus == 0
    {
      print("UsdGenSchemaPlugin succesfully completed.")
    }
    else
    {
      let problem = "\(process.terminationReason):\(process.terminationStatus)"
      Diagnostics.error("UsdGenSchemaPlugin failed: \(problem)")
    }
  }
}
