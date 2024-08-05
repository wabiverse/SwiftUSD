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

extension String
{
  /// A quoted version of the string for interpolating into commands.
  /// **This is not secure**, it should only be used in example commands printed to the command-line.
  var quotedIfNecessary: String
  {
    let specialCharacters: [Character] = [" ", "\\", "\"", "!", "$", "'", "{", "}", ","]
    for character in specialCharacters
    {
      if contains(character)
      {
        return "'\(replacingOccurrences(of: "'", with: "'\\''"))'"
      }
    }
    return self
  }
}
