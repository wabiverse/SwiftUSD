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
import Logging
import Rainbow

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
    /// The standard error stream used for logging errors.
    var standardError = FileHandle.standardError

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
let log = Logger(label: "OpenUSD")
{ _ in
  Handler()
}
