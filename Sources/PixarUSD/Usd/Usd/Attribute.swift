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
import Usd

public typealias UsdAttribute = Pixar.UsdAttribute

public extension Usd
{
  typealias Attribute = UsdAttribute
}

public extension Usd.Attribute
{
  func set(doc: String)
  {
    SetDocumentation(std.string(doc))
  }

  @discardableResult
  func set(_ value: String, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(std.string(value), time)
  }

  @discardableResult
  func set(_ value: Sdf.AssetPath, time: UsdTimeCode = UsdTimeCode.Default()) -> Bool
  {
    Set(value, time)
  }
}
