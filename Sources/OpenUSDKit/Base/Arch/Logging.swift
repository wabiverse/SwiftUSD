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
#if !os(Android)
  import Rainbow
#else
  // Rainbow is not available on Android; provide no-op color stubs so the
  // rest of Logging.swift compiles unchanged on all platforms.
  private extension String {
    var blue: String { self }
    var cyan: String { self }
    var yellow: String { self }
    var magenta: String { self }
    var green: String { self }
    var red: String { self }
    var lightWhite: String { self }
  }
#endif

/* --- xxx --- */

public final class Msg
{
  public static let logger = Logger(label: "foundation.wabi.openusd")

  private init()
  {}
}

/* --- xxx --- */

public extension Msg
{
  func point(_ subject: String, to msgArgs: Any...)
  {
    Msg.logger.info("\("[ INFO ] ".blue)\(subject.cyan)\(String(repeating: " ", count: max(35 - subject.count, 1)))\("-> ".yellow + msgArgs.flatMap { "\($0)".magenta })")
  }

  func info(_ msgArgs: Any...)
  {
    Msg.logger.info("\("[ INFO ] ".blue + msgArgs.flatMap { "\($0)".lightWhite })")
  }

  func debug(_ msgArgs: Any...)
  {
    Msg.logger.debug("\("[ DEBUG ] ".magenta + msgArgs.flatMap { "\($0)".lightWhite })")
  }

  func success(_ msgArgs: Any...)
  {
    Msg.logger.info("\("[ SUCCESS ] ".green + msgArgs.flatMap { "\($0)".lightWhite })")
  }

  func warn(_ msgArgs: Any...)
  {
    Msg.logger.warning("\("[ WARN ] ".yellow + msgArgs.flatMap { "\($0)".lightWhite })")
  }

  func error(_ msgArgs: Any...)
  {
    Msg.logger.error("\("[ ERROR ] ".red + msgArgs.flatMap { "\($0)".lightWhite })")
  }
}

/* --- xxx --- */
