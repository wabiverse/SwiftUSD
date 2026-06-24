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

#if canImport(Ar)
  import Ar
#else
  import OpenUSD
#endif

public extension Ar
{
  static func getAllResolvers() -> [String]
  {
    // 1. we get the base type.
    let base = Overlay.FindTypeByName("ArResolver")

    guard
      // 2. we verify the base type is valid.
      let all = base.pointee.IsUnknown() == false
      // 3. we get all that derive from the base type.
      ? Pixar.TfType.GetDirectlyDerivedTypes(base.pointee) : nil,
      // 4. we ensure the list is not empty.
      all().empty() == false
    else { return [] }

    var result: [String] = []
    let resolvers = all()
    for i in 0..<Int(resolvers.size()) {
      result.append(String(cString: Overlay.GetTypeName(resolvers[i])))
    }

    return result
  }
}
