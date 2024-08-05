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
 * ## Overview
 *
 * **Token** for efficient comparison, assignment, and hashing of known strings.
 *
 * A TfToken is a handle for a registered string, and can be compared,
 * assigned, and hashed in constant time. It is useful when a bounded
 * number of strings are used as fixed symbols (but never modified). */
public typealias TfToken = Pixar.TfToken

public extension Tf
{
  /**
   * # Tf.Token
   *
   * ## Overview
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
