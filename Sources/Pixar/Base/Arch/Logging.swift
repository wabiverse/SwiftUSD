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
import Rainbow

/* --- xxx --- */

public final class Msg
{
  public static let Log = Msg()

  private init()
  {
    #if os(macOS)
      // Disable colored output for Xcode (only applies to macOS platform).
      Rainbow.enabled = ProcessInfo.processInfo.environment["__XCODE_BUILT_PRODUCTS_DIR_PATHS"] == nil
    #endif /* os(macOS) */
  }
}

/* --- xxx --- */

public extension Msg
{
  func point(_ subject: String, to msgArgs: Any...)
  {
    print(
      "[ INFO ] ".blue +
        subject.cyan +
        String(repeating: " ", count: max(35 - subject.count, 1)) +
        "-> ".yellow +
        msgArgs.flatMap { "\($0)".magenta }
    )
  }

  func info(_ msgArgs: Any...)
  {
    print("[ INFO ] ".blue + msgArgs.flatMap { "\($0)".cyan })
  }

  func debug(_ msgArgs: Any...)
  {
    print("[ DEBUG ] ".magenta + msgArgs.flatMap { "\($0)".cyan })
  }

  func success(_ msgArgs: Any...)
  {
    print("[ SUCCESS ] ".green + msgArgs.flatMap { "\($0)".cyan })
  }

  func warn(_ msgArgs: Any...)
  {
    print("[ WARN ] ".yellow + msgArgs.flatMap { "\($0)".cyan })
  }

  func error(_ msgArgs: Any...)
  {
    print("[ ERROR ] ".red + msgArgs.flatMap { "\($0)".cyan })
  }
}

/* --- xxx --- */
