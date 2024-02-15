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

public enum Tf
{}

public extension Tf
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
