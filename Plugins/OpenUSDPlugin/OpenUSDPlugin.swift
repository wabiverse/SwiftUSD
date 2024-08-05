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

import Foundation
import PackagePlugin

@main
struct OpenUSDPlugin: CommandPlugin
{
  func performCommand(context: PluginContext, arguments: [String]) throws
  {
    let openusd = try context.tool(named: "OpenUSD")

    try run(command: openusd.path, with: arguments)
  }
}

extension OpenUSDPlugin
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
      print("openusd success: completed.")
    }
    else
    {
      let problem = "\(process.terminationReason):\(process.terminationStatus)"
      Diagnostics.error("openusd failed: \(problem)")
    }
  }
}
