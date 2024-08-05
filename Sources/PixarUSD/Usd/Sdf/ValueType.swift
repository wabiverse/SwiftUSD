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

import Sdf

public typealias SdfValueTypeNameType = Pixar.SdfValueTypeNameType
public typealias SdfValueTypeName = Pixar.SdfValueTypeName

public extension Sdf
{
  typealias ValueTypeNameType = SdfValueTypeNameType
  typealias ValueTypeName = SdfValueTypeName
}

public extension Sdf
{
  static func getValueType(for type: SdfValueTypeNameType) -> Sdf.ValueTypeName
  {
    Pixar.SdfGetValueType(type)
  }
}
