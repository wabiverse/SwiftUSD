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

public enum Command: String
{
  case git

  public func run(with arguments: [String]) throws
  {
    let (output, error, exitCode) = runCommand(cmd: "/usr/bin/whereis", args: rawValue)
    if exitCode != 0
    {
      fatalError("\(rawValue) error: \(error).")
    }

    var exe = "/usr/bin/env"
    var args = arguments
    for item in output
    {
      if item.contains(rawValue)
      {
        for match in item.split(separator: " ")
        {
          if match.split(separator: "/").last.map(String.init) == rawValue
          {
            exe = String(match)
            break
          }
        }
      }
    }

    if exe == "/usr/bin/env"
    {
      args = [rawValue] + arguments
    }

    let exec = URL(fileURLWithPath: exe)

    let process = try Process.run(exec, arguments: args)
    process.waitUntilExit()

    // Check whether the subprocess invocation was successful.
    if process.terminationReason == .exit, process.terminationStatus == 0
    {
      print("\(rawValue) success: completed.")
    }
    else
    {
      let problem = "\(process.terminationReason):\(process.terminationStatus)"
      fatalError("\(rawValue) failed: \(problem)")
    }
  }

  func runCommand(cmd: String, args: String...) -> (output: [String], error: [String], exitCode: Int32)
  {
    var output: [String] = []
    var error: [String] = []

    let task = Process()
    task.launchPath = cmd
    task.arguments = args

    let outpipe = Pipe()
    task.standardOutput = outpipe
    let errpipe = Pipe()
    task.standardError = errpipe

    task.launch()

    let outdata = outpipe.fileHandleForReading.readDataToEndOfFile()
    if var string = String(data: outdata, encoding: .utf8)
    {
      string = string.trimmingCharacters(in: .newlines)
      output = string.components(separatedBy: "\n")
    }

    let errdata = errpipe.fileHandleForReading.readDataToEndOfFile()
    if var string = String(data: errdata, encoding: .utf8)
    {
      string = string.trimmingCharacters(in: .newlines)
      error = string.components(separatedBy: "\n")
    }

    task.waitUntilExit()
    let status = task.terminationStatus

    return (output, error, status)
  }
}
