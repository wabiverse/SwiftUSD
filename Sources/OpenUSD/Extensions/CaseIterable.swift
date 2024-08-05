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

extension CaseIterable where Self: RawRepresentable, RawValue == String
{
  /// A string containing all possible values (for use in command-line option help messages).
  static var possibleValuesString: String
  {
    "(" + allCases.map(\.rawValue).joined(separator: "|") + ")"
  }
}
