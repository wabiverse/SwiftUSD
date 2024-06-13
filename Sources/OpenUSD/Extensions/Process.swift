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

import Foundation

/// All processes that have been created using `Process.create(_:arguments:directory:pipe:)`.
///
/// If the program is killed, all processes in this array are terminated before the program exits.
var processes: [Process] = []

extension Process
{
  /// A string created by concatenating all of the program's arguments together. Suitable for error messages,
  /// but not necessarily 100% correct.
  var argumentsString: String
  {
    // TODO: This could instead be `commandString` and we infer the human friendly name from the executableURL
    //   (remembering that if the url is `/usr/bin/env`, the path we care about is actually the first argument)
    // TODO: This is pretty janky (i.e. what if an arg contains spaces)
    arguments?.joined(separator: " ") ?? ""
  }

  /// Sets the pipe for the process's stdout and stderr.
  /// - Parameter excludeStdError: If `true`, only stdout is piped.
  /// - Parameter pipe: The pipe.
  func setOutputPipe(_ pipe: Pipe, excludeStdError: Bool = false)
  {
    standardOutput = pipe
    if !excludeStdError
    {
      standardError = pipe
    }
  }

  /// Gets the process's stdout and stderr as `Data`.
  /// - Parameter excludeStdError: If `true`, only stdout is returned.
  /// - Returns: The process's stdout and stderr. If an error occurs, a failure is returned.
  func getOutputData(excludeStdError: Bool = false) -> Result<Data, ProcessError>
  {
    let pipe = Pipe()
    setOutputPipe(pipe, excludeStdError: excludeStdError)

    return runAndWait().map
    { _ in
      let data = pipe.fileHandleForReading.readDataToEndOfFile()
      return data
    }.mapError
    { error in
      switch error
      {
        case let .nonZeroExitStatus(status):
          let data = pipe.fileHandleForReading.readDataToEndOfFile()
          return .nonZeroExitStatusWithOutput(data, status)
        default:
          return error
      }
    }
  }

  /// Gets the process's stdout and stderr as a string.
  /// - Parameter excludeStdError: If `true`, only stdout is returned.
  /// - Returns: The process's stdout and stderr. If an error occurs, a failure is returned.
  func getOutput(excludeStdError: Bool = false) -> Result<String, ProcessError>
  {
    getOutputData(excludeStdError: excludeStdError)
      .flatMap
      { data in
        guard let output = String(data: data, encoding: .utf8)
        else
        {
          return .failure(.invalidUTF8Output(output: data))
        }

        return .success(output)
      }
  }

  /// Runs the process and waits for it to complete.
  /// - Returns: Returns a failure if the process has a non-zero exit status of fails to run.
  func runAndWait() -> Result<Void, ProcessError>
  {
    log.debug("Running command: '\(executableURL?.path ?? "")' with arguments: \(arguments ?? [])")

    do
    {
      try run()
    }
    catch
    {
      return .failure(.failedToRunProcess(error))
    }

    waitUntilExit()

    let exitStatus = Int(terminationStatus)
    if exitStatus != 0
    {
      return .failure(.nonZeroExitStatus(exitStatus))
    }

    return .success()
  }

  /// Adds environment variables to the process's environment.
  /// - Parameter variables: The key value pairs to add.
  func addEnvironmentVariables(_ variables: [String: String])
  {
    if var environment
    {
      for (key, value) in variables
      {
        environment[key] = value
      }
      self.environment = environment
    }
    else
    {
      environment = variables
    }
  }

  /// Creates a new process (but doesn't run it).
  /// - Parameters:
  ///   - tool: The tool.
  ///   - arguments: The tool's arguments.
  ///   - directory: The directory to run the command in. Defaults to the current directory.
  ///   - pipe: The pipe for the process's stdout and stderr. Defaults to `nil`.
  ///   - runSilentlyWhenNotVerbose: If `true`, output is captured even when no pipe is provided id Swift Bundler wasn't run with `-v`.
  ///                                Defaults to `true`.
  /// - Returns: The new process.
  static func create(
    _ tool: String,
    arguments: [String] = [],
    directory: URL? = nil,
    pipe: Pipe? = nil,
    runSilentlyWhenNotVerbose: Bool = true
  ) -> Process
  {
    let process = Process()

    if let pipe
    {
      process.setOutputPipe(pipe)
    }
    else if log.logLevel == .info && runSilentlyWhenNotVerbose
    {
      // Silence output by default when not verbose.
      process.setOutputPipe(Pipe())
    }

    process.currentDirectoryURL = directory?.standardizedFileURL.absoluteURL

    // If tool isn't a path, assume it's on the user's PATH
    if tool.hasPrefix("/") || tool.hasPrefix("./")
    {
      process.executableURL = URL(fileURLWithPath: tool)
      process.arguments = arguments
    }
    else
    {
      process.executableURL = URL(fileURLWithPath: "/usr/bin/env")
      process.arguments = [tool] + arguments
    }

    // Fix an issue to do with Xcode breaking SwiftPackageManager (https://stackoverflow.com/a/67613515)
    if ProcessInfo.processInfo.environment.keys.contains("OS_ACTIVITY_DT_MODE")
    {
      var env = ProcessInfo.processInfo.environment
      env["OS_ACTIVITY_DT_MODE"] = nil
      process.environment = env
    }

    processes.append(process)

    return process
  }

  /// Gets the full path to the specified tool (using the `which` shell command). If
  /// you don't need to explicitly know the path from Swift, just pass the name of the
  /// tool to `Process.create` instead (which will detect that it's not a path and instead
  /// run the tool through `/usr/bin/env` which will find the tool on the user's `PATH`).
  /// - Parameter tool: The tool to expand into a full path.
  /// - Returns: The absolute path to the tool, or a failure if the tool can't be located.
  static func locate(_ tool: String) -> Result<String, ProcessError>
  {
    Process.create(
      "/bin/sh",
      arguments: [
        "-c",
        "which \(tool)",
      ]
    ).getOutput().map
    { path in
      path.trimmingCharacters(in: .whitespacesAndNewlines)
    }
  }
}
