/* --------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                          ::
 * --------------------------------------------------------------
 * This program is free software; you can redistribute it, and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Check out
 * the GNU General Public License for more details.
 *
 * You should have received a copy for this software license, the
 * GNU General Public License along with this program; or, if not
 * write to the Free Software Foundation, Inc., to the address of
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *       Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import CxxStdlib
import Foundation
import Sdf

public typealias SdfPath = Pixar.SdfPath

public extension Pixar.Sdf
{
  typealias Path = SdfPath
}

public extension Pixar.Sdf.Path
{
  init(_ path: String)
  {
    self.init(std.string(path))
  }

  private borrowing func GetNameCopy() -> std.string
  {
    __GetNameUnsafe().pointee
  }

  func getAsString() -> String
  {
    String(GetAsString())
  }

  func append(path: Pixar.Sdf.Path) -> Pixar.Sdf.Path
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
