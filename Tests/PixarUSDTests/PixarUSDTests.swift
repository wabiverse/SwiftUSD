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

import XCTest
@testable import PixarUSD

/* ---- xxx ----
 *  ARCH  TESTS
 * ---- xxx ---- */

final class ArchTests: XCTestCase
{
  func testCwd()
  {
    Msg.logger.log(level: .info, "Arch.getCwd() -> \(Arch.getCwd())")
  }

  func testExecutablePath()
  {
    Msg.logger.log(level: .info, "Arch.getExecutablePath() -> \(Arch.getExecutablePath())")
  }

  func testPageSize()
  {
    Msg.logger.log(level: .info, "Arch.getPageSize() -> \(Arch.getPageSize())")
  }

  func testIsMainThread()
  {
    Msg.logger.log(level: .info, "Arch.isMainThread() -> \(Arch.isMainThread())")
  }

  func testAlignMemoryOfSize()
  {
    let size = 1024
    let alignedPtr = Arch.alignMemory(of: size)
    XCTAssert(alignedPtr >= 1024)
  }

  func testAlignMemoryOfPointer()
  {
    let size = 1024
    let alignment = 16
    let ptr = UnsafeMutableRawPointer.allocate(byteCount: size, alignment: alignment)
    defer { ptr.deallocate() }
    let alignedPtr = Arch.alignMemory(of: ptr)
    XCTAssert(alignedPtr != nil)
  }

  func testAlignedAlloc()
  {
    let size = 1024
    let alignment = 16
    let alignedPtr = Arch.alignedAlloc(byteCount: size, alignment: alignment)
    XCTAssert(alignedPtr != nil)
  }

  func testAlignedFree()
  {
    let size = 1024
    let alignment = 16
    var alignedPtr = Arch.alignedAlloc(byteCount: size, alignment: alignment)
    XCTAssert(alignedPtr != nil)
    Arch.alignedFree(pointer: &alignedPtr)
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
    let array = Js.Array()
    Msg.logger.log(level: .info, "Js.Array -> \(array)")

    let jsArray = JsArray()
    Msg.logger.log(level: .info, "JsArray -> \(jsArray)")

    XCTAssertEqual(array.count, jsArray.count)
  }

  func testObject()
  {
    let object = Js.Object()
    Msg.logger.log(level: .info, "Js.Object -> \(object)")

    let jsObject = JsObject()
    Msg.logger.log(level: .info, "JsObject -> \(jsObject)")

    XCTAssertEqual(object.empty(), jsObject.empty())
  }

  func testParseError()
  {
    let parseError = Js.ParseError()
    Msg.logger.log(level: .info, "Js.ParseError -> \(parseError)")

    let jsParseError = JsParseError()
    Msg.logger.log(level: .info, "ParseError -> \(jsParseError)")

    XCTAssertEqual(parseError.reason, jsParseError.reason)
  }

  func testValue()
  {
    let value = Js.Value(true)
    Msg.logger.log(level: .info, "Js.Value -> \(value.GetBool())")
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
    let vec2f = Gf.Vec2f(1.0, 2.0)
    Msg.logger.log(level: .info, "Gf.Vec2f -> \(vec2f)")

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
    let resolvers = Ar.getAllResolvers()

    if resolvers.isEmpty
    {
      Msg.logger.log(level: .info, "Ar.getAllResolvers() -> None")
    }

    for (i, r) in resolvers.enumerated()
    {
      Msg.logger.log(level: .info, "Ar.getAllResolvers() [\(i + 1)/\(resolvers.count)] -> \(r)")
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
    let tokens = Kind.Tokens.allCases

    for (i, t) in tokens.enumerated()
    {
      Msg.logger.log(level: .info, "Kind.Tokens [\(i + 1)/\(tokens.count)] -> \(t.getToken().string)")
    }

    XCTAssertEqual(tokens.count, 5)
  }
}
