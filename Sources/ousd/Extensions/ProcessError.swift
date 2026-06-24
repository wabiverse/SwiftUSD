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

/// An error returned by custom methods added to `Process`.
enum ProcessError: LocalizedError
{
  case invalidUTF8Output(output: Data)
  case nonZeroExitStatus(Int)
  case nonZeroExitStatusWithOutput(Data, Int)
  case failedToRunProcess(Error)

  var errorDescription: String?
  {
    switch self
    {
      case .invalidUTF8Output:
        "Command output was not valid utf-8 data"
      case let .nonZeroExitStatus(status):
        "The process returned a non-zero exit status (\(status))"
      case let .nonZeroExitStatusWithOutput(data, status):
        "The process returned a non-zero exit status (\(status))\n\(String(data: data, encoding: .utf8) ?? "invalid utf8")"
      case .failedToRunProcess:
        "The process failed to run"
    }
  }
}
