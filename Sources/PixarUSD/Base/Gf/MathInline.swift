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

import Gf

public extension Gf
{
  /// Check if two values are within a specified **epsilon** of each other.
  /// - Parameter a: A value to compare.
  /// - Parameter b: A value to compare.
  /// - Parameter epsilon: The tolerance to use.
  ///
  /// - Returns: `true` if the values are within **epsilon** of each other.
  @inline(__always)
  static func isClose(_ a: Double, _ b: Double, within epsilon: Double) -> Bool
  {
    pxr.GfIsClose(a, b, epsilon)
  }

  /// Converts an angle in radians to degrees.
  /// - Parameter radians: The angle in radians.
  ///
  /// - Returns: The angle in degrees.
  @inline(__always)
  static func radiansToDegrees(angle radians: Double) -> Double
  {
    pxr.GfRadiansToDegrees(radians)
  }

  /// Converts an angle in degrees to radians.
  /// - Parameter radians: The angle in degrees.
  ///
  /// - Returns: The angle in radians.
  @inline(__always)
  static func degreesToRadians(angle degrees: Double) -> Double
  {
    pxr.GfDegreesToRadians(degrees)
  }

  /* ----- Figure out why explicit type is needed ----- */

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inline(__always)
  static func sqr(_ x: Int) -> Double
  {
    pxr.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inline(__always)
  static func sqr(_ x: Float) -> Double
  {
    pxr.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inline(__always)
  static func sqr(_ x: Double) -> Double
  {
    pxr.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inline(__always)
  static func sqr(_ x: GfVec2f) -> Double
  {
    pxr.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inline(__always)
  static func sqr(_ x: GfVec3f) -> Double
  {
    pxr.GfSqr(x)
  }

  /// Return sqrt(f).
  @inline(__always)
  static func sqrt(_ f: Double) -> Double
  {
    pxr.GfSqrt(f)
  }

  /// Return sqrt(f).
  @inline(__always)
  static func sqrt(_ f: Float) -> Float
  {
    pxr.GfSqrt(f)
  }

  /// Return exp(f).
  @inline(__always)
  static func exp(_ f: Double) -> Double
  {
    pxr.GfExp(f)
  }

  /// Return exp(f).
  @inline(__always)
  static func exp(_ f: Float) -> Float
  {
    pxr.GfExp(f)
  }

  /// Return log(f).
  @inline(__always)
  static func log(_ f: Double) -> Double
  {
    pxr.GfLog(f)
  }

  /// Return log(f).
  @inline(__always)
  static func log(_ f: Float) -> Float
  {
    pxr.GfLog(f)
  }

  /// Return floor(f).
  @inline(__always)
  static func floor(_ f: Double) -> Double
  {
    pxr.GfFloor(f)
  }

  /// Return floor(f).
  @inline(__always)
  static func floor(_ f: Float) -> Float
  {
    pxr.GfFloor(f)
  }

  /// Return ceil(f).
  @inline(__always)
  static func ceil(_ f: Double) -> Double
  {
    pxr.GfCeil(f)
  }

  /// Return ceil(f).
  @inline(__always)
  static func ceil(_ f: Float) -> Float
  {
    pxr.GfCeil(f)
  }

  /// Return abs(f).
  @inline(__always)
  static func abs(_ f: Double) -> Double
  {
    pxr.GfAbs(f)
  }

  /// Return abs(f).
  @inline(__always)
  static func abs(_ f: Float) -> Float
  {
    pxr.GfAbs(f)
  }

  /// Return round(f).
  @inline(__always)
  static func round(_ f: Double) -> Double
  {
    pxr.GfRound(f)
  }

  /// Return round(f).
  @inline(__always)
  static func round(_ f: Float) -> Float
  {
    pxr.GfRound(f)
  }

  /// Return pow(f, p).
  @inline(__always)
  static func pow(_ f: Double, _ p: Double) -> Double
  {
    pxr.GfPow(f, p)
  }

  /// Return pow(f, p).
  @inline(__always)
  static func pow(_ f: Float, _ p: Float) -> Float
  {
    pxr.GfPow(f, p)
  }

  /// Return sin(v).
  @inline(__always)
  static func sin(_ v: Double) -> Double
  {
    pxr.GfSin(v)
  }

  /// Return sin(v).
  @inline(__always)
  static func sin(_ v: Float) -> Float
  {
    pxr.GfSin(v)
  }

  /// Return cos(v).
  @inline(__always)
  static func cos(_ v: Double) -> Double
  {
    pxr.GfCos(v)
  }

  /// Return cos(v).
  @inline(__always)
  static func cos(_ v: Float) -> Float
  {
    pxr.GfCos(v)
  }

  /// Return sin(v) in s and cos(v) in c.
  @inline(__always)
  static func sinCos(_ v: Double, _ s: inout Double, _ c: inout Double)
  {
    pxr.GfSinCos(v, &s, &c)
  }

  /// Return sin(v) in s and cos(v) in c.
  @inline(__always)
  static func sinCos(_ v: Float, _ s: inout Float, _ c: inout Float)
  {
    pxr.GfSinCos(v, &s, &c)
  }

  /// Return the resulting of clamping value to lie between
  /// min and max. This function is also defined for GfVecs.
  @inline(__always)
  static func clamp(_ value: Double, _ min: Double, _ max: Double) -> Double
  {
    pxr.GfClamp(value, min, max)
  }

  /// Return the resulting of clamping value to lie between
  /// min and max. This function is also defined for GfVecs.
  @inline(__always)
  static func clamp(_ value: Float, _ min: Float, _ max: Float) -> Float
  {
    pxr.GfClamp(value, min, max)
  }

  /// The mod function with "correct" behaviour for negative numbers.
  ///
  /// If a = `n b` for some integer n, zero is returned.
  /// Otherwise, for positive a, the value returned is `fmod(a,b)`,
  /// and for negative `a`, the value returned is `fmod(a,b) + b`.
  @inline(__always)
  static func mod(_ a: Double, _ b: Double) -> Double
  {
    pxr.GfMod(a, b)
  }

  /// The mod function with "correct" behaviour for negative numbers.
  ///
  /// If a = `n b` for some integer n, zero is returned.
  /// Otherwise, for positive a, the value returned is `fmod(a,b)`,
  /// and for negative `a`, the value returned is `fmod(a,b) + b`.
  @inline(__always)
  static func mod(_ a: Float, _ b: Float) -> Float
  {
    pxr.GfMod(a, b)
  }

  /* -------------------------------------------------- */
}
