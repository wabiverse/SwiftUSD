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
