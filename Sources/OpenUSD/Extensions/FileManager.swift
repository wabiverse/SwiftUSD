/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import Foundation

extension FileManager
{
  /// The type of an item on the file system.
  enum ItemType
  {
    case file
    case directory
  }

  /// Gets whether an item of a specific type exists at the given `URL` or not.
  /// - Parameters:
  ///   - url: The URL of the item to check for.
  ///   - type: The type that the item must be.
  /// - Returns: `true` if an item of the specified type exists at the specified location.
  func itemExists(at url: URL, withType type: ItemType) -> Bool
  {
    var isDirectory: ObjCBool = false
    if fileExists(atPath: url.path, isDirectory: &isDirectory)
    {
      if isDirectory.boolValue, type == .directory
      {
        return true
      }
      else if !isDirectory.boolValue, type == .file
      {
        return true
      }
    }
    return false
  }

  /// Creates a directory.
  /// - Parameter url: The directory to create.
  /// - Throws: An error if directory creation fails.
  func createDirectory(at url: URL) throws
  {
    try createDirectory(at: url, withIntermediateDirectories: true, attributes: nil)
  }
}
