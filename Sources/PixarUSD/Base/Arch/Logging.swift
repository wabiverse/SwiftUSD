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

/* --- xxx --- */

public final class Msg
{
  public static let logger = Logger(label: "foundation.wabi.metaverse")

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
