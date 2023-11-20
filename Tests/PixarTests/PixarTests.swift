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
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import XCTest
@testable import Pixar

/* ---- xxx ----
 *  ARCH  TESTS
 * ---- xxx ---- */

final class ArchTests: XCTestCase
{
  func testCwd()
  {
    PXRMSG.Log.point("Pixar.Arch.getCwd()", to: Pixar.Arch.getCwd())
  }

  func testExecutablePath()
  {
    PXRMSG.Log.point("Pixar.Arch.getExecutablePath()", to: Pixar.Arch.getExecutablePath())
  }

  func testPageSize()
  {
    PXRMSG.Log.point("Pixar.Arch.getPageSize()", to: Pixar.Arch.getPageSize())
  }

  func testIsMainThread()
  {
    PXRMSG.Log.point("Pixar.Arch.isMainThread()", to: Pixar.Arch.isMainThread())
  }

  func testMainThreadId()
  {
    PXRMSG.Log.point("Pixar.Arch.getMainThreadId()", to: Pixar.Arch.getMainThreadId())
  }

  func testAlignMemoryOfSize()
  {
    let size = 1024
    let alignedPtr = Pixar.Arch.alignMemory(of: size)
    XCTAssert(alignedPtr >= 1024)
  }

  func testAlignMemoryOfPointer()
  {
    let size = 1024
    let alignment = 16
    let ptr = UnsafeMutableRawPointer.allocate(byteCount: size, alignment: alignment)
    defer { ptr.deallocate() }
    let alignedPtr = Pixar.Arch.alignMemory(of: ptr)
    XCTAssert(alignedPtr != nil)
  }

  func testAlignedAlloc()
  {
    let size = 1024
    let alignment = 16
    let alignedPtr = Pixar.Arch.alignedAlloc(byteCount: size, alignment: alignment)
    XCTAssert(alignedPtr != nil)
  }

  func testAlignedFree()
  {
    let size = 1024
    let alignment = 16
    var alignedPtr = Pixar.Arch.alignedAlloc(byteCount: size, alignment: alignment)
    XCTAssert(alignedPtr != nil)
    Pixar.Arch.alignedFree(pointer: &alignedPtr)
    XCTAssert(alignedPtr == nil)
  }
}


/* ---- xxx ----
 *  Gf    TESTS
 * ---- xxx ---- */

final class GfTests: XCTestCase
{
  func testVec2f()
  {
    let vec2f = Pixar.Gf.Vec2f(1.0, 2.0)
    PXRMSG.Log.point("Pixar.Gf.Vec2f", to: vec2f)

    let gfVec2f = GfVec2f(1.0, 2.0)
    PXRMSG.Log.point("GfVec2f", to: gfVec2f)

    XCTAssertEqual(vec2f, gfVec2f)
  }
}
