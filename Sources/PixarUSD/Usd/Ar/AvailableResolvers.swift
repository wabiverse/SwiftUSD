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

import Ar

public extension Ar
{
  static func getAllResolvers() -> [String]
  {
    // 1. we get the base type.
    let base = Pixar.TfType.FindByName("ArResolver")

    guard
      // 2. we verify the base type is valid.
      let all = base.pointee.IsUnknown() == false
      // 3. we get all that derive from the base type.
      ? Pixar.TfType.GetDirectlyDerivedTypes(base.pointee) : nil,
      // 4. we ensure the list is not empty.
      all().empty() == false
    else { return [] }

    return all().map
    {
      // return list of all type names.
      String($0.GetTypeName().pointee)
    }
  }
}
