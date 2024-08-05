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

import Arch

/**
 * # Memory Management
 *
 * Functions having to do with memory allocation / handling. */
public extension Arch
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
