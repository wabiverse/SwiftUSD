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
import Foundation
import Sdf

public typealias SdfPath = Pixar.SdfPath

public extension Sdf
{
  typealias Path = SdfPath
}

public extension Sdf.Path
{
  init(_ path: String)
  {
    self.init(std.string(path))
  }

  static func emptyPath() -> Sdf.Path
  {
    Sdf.Path.EmptyPath().pointee
  }

  static func absoluteRootPath() -> Sdf.Path
  {
    Sdf.Path.AbsoluteRootPath().pointee
  }

  static func reflexiveRelativePath() -> Sdf.Path
  {
    Sdf.Path.ReflexiveRelativePath().pointee
  }

  private borrowing func GetNameCopy() -> std.string
  {
    __GetNameUnsafe().pointee
  }

  func getAsString() -> String
  {
    String(GetAsString())
  }

  func append(path: Sdf.Path) -> Sdf.Path
  {
    AppendPath(path)
  }

  var string: String
  {
    String(GetAsString())
  }

  var name: String
  {
    String(GetNameCopy())
  }
}
