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
