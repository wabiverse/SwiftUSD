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
 *       Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

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
