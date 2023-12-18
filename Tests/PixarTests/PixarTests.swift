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
    Msg.Log.point("Pixar.Arch.getCwd()", to: Pixar.Arch.getCwd())
  }

  func testExecutablePath()
  {
    Msg.Log.point("Pixar.Arch.getExecutablePath()", to: Pixar.Arch.getExecutablePath())
  }

  func testPageSize()
  {
    Msg.Log.point("Pixar.Arch.getPageSize()", to: Pixar.Arch.getPageSize())
  }

  func testIsMainThread()
  {
    Msg.Log.point("Pixar.Arch.isMainThread()", to: Pixar.Arch.isMainThread())
  }

  func testMainThreadId()
  {
    Msg.Log.point("Pixar.Arch.getMainThreadId()", to: Pixar.Arch.getMainThreadId())
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
 *   JS  TESTS
 * ---- xxx ---- */

final class JsTests: XCTestCase
{
  func testArray()
  {
    let array = Pixar.Js.Array()
    Msg.Log.point("Pixar.Js.Array", to: array)

    let jsArray = JsArray()
    Msg.Log.point("JsArray", to: jsArray)

    XCTAssertEqual(array.count, jsArray.count)
  }

  func testObject()
  {
    let object = Pixar.Js.Object()
    Msg.Log.point("Pixar.Js.Object", to: object)

    let jsObject = JsObject()
    Msg.Log.point("JsObject", to: jsObject)

    XCTAssertEqual(object.empty(), jsObject.empty())
  }

  func testParseError()
  {
    let parseError = Pixar.Js.ParseError()
    Msg.Log.point("Pixar.Js.ParseError", to: parseError)

    let jsParseError = JsParseError()
    Msg.Log.point("ParseError", to: jsParseError)

    XCTAssertEqual(parseError.reason, jsParseError.reason)
  }

  func testValue()
  {
    let value = Pixar.Js.Value(true)
    Msg.Log.point("Pixar.Js.Value", to: value.GetBool())
    XCTAssertEqual(value.GetBool(), true)

    let jsValue = JsValue(true)
    Msg.Log.point("JsValue", to: jsValue.GetBool())
    XCTAssertEqual(jsValue.GetBool(), true)

    XCTAssertEqual(value.GetBool(), jsValue.GetBool())
  }
}

/* ---- xxx ----
 *   GF  TESTS
 * ---- xxx ---- */

final class GfTests: XCTestCase
{
  func testVec2f()
  {
    let vec2f = Pixar.Gf.Vec2f(1.0, 2.0)
    Msg.Log.point("Pixar.Gf.Vec2f", to: vec2f)

    let gfVec2f = GfVec2f(1.0, 2.0)
    Msg.Log.point("GfVec2f", to: gfVec2f)

    XCTAssertEqual(vec2f, gfVec2f)
    XCTAssertEqual(MemoryLayout<GfVec2f>.size, MemoryLayout<(Float, Float)>.size)
  }

  func testVec3f()
  {
    let vec3fA = GfVec3f(1.0, 2.0, 3.0)
    Msg.Log.point("GfVec3f(1.0, 2.0, 3.0)", to: vec3fA)

    let vec3fB = GfVec3f(4.0, 5.0, 6.0)
    Msg.Log.point("GfVec3f(4.0, 5.0, 6.0)", to: vec3fB)

    var vec3fC = vec3fA + vec3fB
    Msg.Log.point("vec3fC=(vec3fA + vec3fB)", to: vec3fC)

    vec3fC *= vec3fA
    Msg.Log.point("vec3fC*=(vec3fA)", to: vec3fC)

    Msg.Log.point("MemoryLayout<SIMD3<Float>>.size", to: MemoryLayout<SIMD3<Float>>.size)
    Msg.Log.point("MemoryLayout<GfVec3f>.size", to: MemoryLayout<GfVec3f>.size)
    Msg.Log.point("MemoryLayout<(Float, Float, Float)>.size", to: MemoryLayout<(Float, Float, Float)>.size)

    XCTAssertEqual(MemoryLayout<GfVec3f>.size, MemoryLayout<(Float, Float, Float)>.size)
  }
}

/* ---- xxx ----
 *   AR  TESTS
 * ---- xxx ---- */

final class ArTests: XCTestCase
{
  func testGetAllResolvers()
  {
    let resolvers = Pixar.Ar.getAllResolvers()

    if resolvers.isEmpty
    {
      Msg.Log.point("Pixar.Ar.getAllResolvers()", to: "None")
    }

    for (i, r) in resolvers.enumerated()
    {
      Msg.Log.point(
        "Pixar.Ar.getAllResolvers()"
          + "\(Msg.Colors.yellow.rawValue) -> "
          + "\(Msg.Colors.default.rawValue)["
          + "\(Msg.Colors.green.rawValue)\(i + 1) of \(resolvers.count)"
          + "\(Msg.Colors.default.rawValue)]",
        to: "\(r)"
      )
    }
  }
}

/* ---- xxx ----
 *  KIND  TESTS
 * ---- xxx ---- */

final class KindTests: XCTestCase
{
  func testKindTokens()
  {
    let tokens = Pixar.Kind.Tokens.allCases

    for (i, t) in tokens.enumerated()
    {
      Msg.Log.point(
        "Pixar.Kind.Tokens"
          + "\(Msg.Colors.yellow.rawValue) -> "
          + "\(Msg.Colors.default.rawValue)["
          + "\(Msg.Colors.green.rawValue)\(i + 1) of \(tokens.count)"
          + "\(Msg.Colors.default.rawValue)]",
        to: "\(t.getToken().string)"
      )
    }

    XCTAssertEqual(tokens.count, 5)
  }
}
