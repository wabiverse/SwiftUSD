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

import Arch

/**
 * # Memory Management
 *
 * Functions having to do with memory allocation / handling. */
public extension Pixar.Arch
{
  /// Return suitably aligned memory size.
  ///
  /// Requests to `malloc()` or `::new` for a given size are often rounded
  /// upward.
  ///
  /// - Parameter byteCount: The number of bytes to request.
  ///
  /// - Returns: The amount that would actually be consumed by the system to satisfy it.
  /// This is needed for efficient user-defined memory management.
  ///
  static func alignMemory(of byteCount: Int) -> Int
  {
    Pixar.ArchAlignMemorySize(byteCount)
  }

  /// Align memory to the next "best" alignment value.
  ///
  /// This will take a pointer and bump it to the next ideal alignment
  /// boundary that will work for all data types.
  ///
  /// - Parameter base: The base pointer needing alignment.
  ///
  /// - Returns: A pointer to the aligned memory.
  ///
  static func alignMemory(of base: UnsafeMutableRawPointer!) -> UnsafeMutableRawPointer!
  {
    Pixar.ArchAlignMemory(base)
  }

  /// Aligned memory allocation.
  ///
  /// - Parameter byteCount: The number of bytes to allocate.
  /// - Parameter alignment: The alignment of the new region of allocated memory.
  ///
  /// - Returns: A pointer to the newly allocated memory.
  ///
  static func alignedAlloc(byteCount: Int, alignment: Int) -> UnsafeMutableRawPointer!
  {
    Pixar.ArchAlignedAlloc(alignment, byteCount)
  }

  /// Free memory allocated by ArchAlignedAlloc.
  ///
  /// This will take a pointer returned by ArchAlignedAlloc and free it.
  ///
  /// - Parameter pointer: The pointer to free.
  ///
  static func alignedFree(pointer: inout UnsafeMutableRawPointer!)
  {
    Pixar.ArchAlignedFree(pointer)
    pointer = nil
  }
}
