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

import CxxStdlib

// import Tf
import Plug

/* note: the typealiases are documented the same way twice,
 * keep it like this so that sourcekit shows documentation
 * regardless of which typealias a user might use in their
 * code. */

/**
 * # TfToken
 *
 * ### Overview
 *
 * **Token** for efficient comparison, assignment, and hashing of known strings.
 *
 * A TfToken is a handle for a registered string, and can be compared,
 * assigned, and hashed in constant time. It is useful when a bounded
 * number of strings are used as fixed symbols (but never modified). */
public typealias TfToken = Pixar.TfToken

public extension Pixar.Tf
{
  /**
   * # Tf.Token
   *
   * ### Overview
   *
   * **Token** for efficient comparison, assignment, and hashing of known strings.
   *
   * A TfToken is a handle for a registered string, and can be compared,
   * assigned, and hashed in constant time. It is useful when a bounded
   * number of strings are used as fixed symbols (but never modified). */
  typealias Token = TfToken
}

extension TfToken: Equatable
{
  public static func == (lhs: TfToken, rhs: TfToken) -> Bool
  {
    lhs.Hash() == rhs.Hash()
  }
}

public extension TfToken
{
  private borrowing func GetStringCopy() -> std.string
  {
    __GetStringUnsafe().pointee
  }

  init(_ value: String)
  {
    self.init(std.string(value))
  }

  var string: String
  {
    String(GetStringCopy())
  }

  var isEmpty: Bool
  {
    IsEmpty()
  }
}
