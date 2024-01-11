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

import XCTest
@testable import PixarUSD

/* ---- xxx ----
 *  ARCH  TESTS
 * ---- xxx ---- */

final class ArchTests: XCTestCase
{
  func testCwd()
  {
    Msg.logger.log(level: .info, "Pixar.Arch.getCwd() -> \(Pixar.Arch.getCwd())")
  }

  func testExecutablePath()
  {
    Msg.logger.log(level: .info, "Pixar.Arch.getExecutablePath() -> \(Pixar.Arch.getExecutablePath())")
  }

  func testPageSize()
  {
    Msg.logger.log(level: .info, "Pixar.Arch.getPageSize() -> \(Pixar.Arch.getPageSize())")
  }

  func testIsMainThread()
  {
    Msg.logger.log(level: .info, "Pixar.Arch.isMainThread() -> \(Pixar.Arch.isMainThread())")
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
    Msg.logger.log(level: .info, "Pixar.Js.Array -> \(array)")

    let jsArray = JsArray()
    Msg.logger.log(level: .info, "JsArray -> \(jsArray)")

    XCTAssertEqual(array.count, jsArray.count)
  }

  func testObject()
  {
    let object = Pixar.Js.Object()
    Msg.logger.log(level: .info, "Pixar.Js.Object -> \(object)")

    let jsObject = JsObject()
    Msg.logger.log(level: .info, "JsObject -> \(jsObject)")

    XCTAssertEqual(object.empty(), jsObject.empty())
  }

  func testParseError()
  {
    let parseError = Pixar.Js.ParseError()
    Msg.logger.log(level: .info, "Pixar.Js.ParseError -> \(parseError)")

    let jsParseError = JsParseError()
    Msg.logger.log(level: .info, "ParseError -> \(jsParseError)")

    XCTAssertEqual(parseError.reason, jsParseError.reason)
  }

  func testValue()
  {
    let value = Pixar.Js.Value(true)
    Msg.logger.log(level: .info, "Pixar.Js.Value -> \(value.GetBool())")
    XCTAssertEqual(value.GetBool(), true)

    let jsValue = JsValue(true)
    Msg.logger.log(level: .info, "JsValue -> \(jsValue.GetBool())")
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
    Msg.logger.log(level: .info, "Pixar.Gf.Vec2f -> \(vec2f)")

    let gfVec2f = GfVec2f(1.0, 2.0)
    Msg.logger.log(level: .info, "GfVec2f -> \(gfVec2f)")

    XCTAssertEqual(vec2f, gfVec2f)
    XCTAssertEqual(MemoryLayout<GfVec2f>.size, MemoryLayout<(Float, Float)>.size)
  }

  func testVec3f()
  {
    let vec3fA = GfVec3f(1.0, 2.0, 3.0)
    Msg.logger.log(level: .info, "GfVec3f(1.0, 2.0, 3.0) -> \(vec3fA)")

    let vec3fB = GfVec3f(4.0, 5.0, 6.0)
    Msg.logger.log(level: .info, "GfVec3f(4.0, 5.0, 6.0) -> \(vec3fB)")

    var vec3fC = vec3fA + vec3fB
    Msg.logger.log(level: .info, "vec3fC=(vec3fA + vec3fB) -> \(vec3fC)")

    vec3fC *= vec3fA
    Msg.logger.log(level: .info, "vec3fC*=(vec3fA) -> \(vec3fC)")

    Msg.logger.log(level: .info, "MemoryLayout<SIMD3<Float>>.size -> \(MemoryLayout<SIMD3<Float>>.size)")
    Msg.logger.log(level: .info, "MemoryLayout<GfVec3f>.size -> \(MemoryLayout<GfVec3f>.size)")
    Msg.logger.log(level: .info, "MemoryLayout<(Float, Float, Float)>.size -> \(MemoryLayout<(Float, Float, Float)>.size)")

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
      Msg.logger.log(level: .info, "Pixar.Ar.getAllResolvers() -> None")
    }

    for (i, r) in resolvers.enumerated()
    {
      Msg.logger.log(level: .info, "Pixar.Ar.getAllResolvers() [\(i + 1)/\(resolvers.count)] -> \(r)")
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
      Msg.logger.log(level: .info, "Pixar.Kind.Tokens [\(i + 1)/\(tokens.count)] -> \(t.getToken().string)")
    }

    XCTAssertEqual(tokens.count, 5)
  }
}
