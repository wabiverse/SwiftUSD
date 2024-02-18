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

import Hgi

public enum Hgi
{}

public extension Hgi
{
  /// Helper function to return a ``__ObjC/Pixar/Hgi`` object for the current
  /// platform. For example on Linux this may return HgiGL while on macOS, it
  /// may return HgiMetal. Caller, usually the application, owns the lifetime
  /// of the Hgi object and the object is destroyed when the caller drops the
  /// unique ptr. Thread safety: Not thread safe.
  static func createPlatformDefaultHgi() -> Pixar.Hgi
  {
    /* Currently swift does not support std.unique_ptr,
     * use the deprecated GetPlatformDefaultHgi() call
     * instead of CreatePlatformDefaultHgi() for now. */
    Pixar.Hgi.GetPlatformDefaultHgi()
  }
}
