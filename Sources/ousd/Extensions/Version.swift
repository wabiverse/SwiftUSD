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

import Version

extension Version
{
  /// A representation of the version using underscore separators and only including down to the least
  /// significant non-zero component.
  ///
  /// For example, `0.5.0` becomes `0_5` and `1.5.2` becomes `1_5_2`.
  var underscoredMinimal: String
  {
    var string = "\(major)"
    if minor != 0
    {
      string += "_\(minor)"
      if patch != 0
      {
        string += "_\(patch)"
      }
    }
    return string
  }
}
