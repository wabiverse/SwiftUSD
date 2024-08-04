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
import Logging
#if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS) || os(Linux)
import Rainbow
#endif

/// The standard error stream used for logging errors.
var standardError = FileHandle.standardError

/// Swift Bundler's basic log handler.
struct Handler: LogHandler
{
  var metadata: Logger.Metadata = [:]
  var logLevel: Logger.Level = .info

  subscript(metadataKey key: String) -> Logger.Metadata.Value?
  {
    get { metadata[key] }
    set { metadata[key] = newValue }
  }

  func log(level: Logger.Level, message: Logger.Message, metadata _: Logger.Metadata?, source _: String, file _: String, function _: String, line _: UInt)
  {
    let output = "\(level.coloring(level.rawValue + ":")) \(message)"

    switch level
    {
      case .critical, .error:
        print(output, to: &standardError)
      default:
        print(output)
    }
  }
}

/// The global logger.
var log = Logger(label: "OpenUSD")
{ _ in
  Handler()
}
