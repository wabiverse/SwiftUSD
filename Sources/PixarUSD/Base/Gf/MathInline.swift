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

import Gf

public extension Gf
{
  /// Check if two values are within a specified **epsilon** of each other.
  /// - Parameter a: A value to compare.
  /// - Parameter b: A value to compare.
  /// - Parameter epsilon: The tolerance to use.
  ///
  /// - Returns: `true` if the values are within **epsilon** of each other.
  @inlinable
  static func isClose(_ a: Double, _ b: Double, within epsilon: Double) -> Bool
  {
    Pixar.GfIsClose(a, b, epsilon)
  }

  /// Converts an angle in radians to degrees.
  /// - Parameter radians: The angle in radians.
  ///
  /// - Returns: The angle in degrees.
  @inlinable
  static func radiansToDegrees(angle radians: Double) -> Double
  {
    Pixar.GfRadiansToDegrees(radians)
  }

  /// Converts an angle in degrees to radians.
  /// - Parameter radians: The angle in degrees.
  ///
  /// - Returns: The angle in radians.
  @inlinable
  static func degreesToRadians(angle degrees: Double) -> Double
  {
    Pixar.GfDegreesToRadians(degrees)
  }

  /* ----- Figure out why explicit type is needed ----- */

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inlinable
  static func sqr(_ x: Int) -> Double
  {
    Pixar.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inlinable
  static func sqr(_ x: Float) -> Double
  {
    Pixar.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inlinable
  static func sqr(_ x: Double) -> Double
  {
    Pixar.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inlinable
  static func sqr(_ x: GfVec2f) -> Double
  {
    Pixar.GfSqr(x)
  }

  /// Returns the inner product of **x** with itself: specifically, `x * x`.
  /// Defined for **Int**, **Float**, **Double**, and all **GfVec** types.
  @inlinable
  static func sqr(_ x: GfVec3f) -> Double
  {
    Pixar.GfSqr(x)
  }

  /// Return sqrt(f).
  @inlinable
  static func sqrt(_ f: Double) -> Double
  {
    Pixar.GfSqrt(f)
  }

  /// Return sqrt(f).
  @inlinable
  static func sqrt(_ f: Float) -> Float
  {
    Pixar.GfSqrt(f)
  }

  /// Return exp(f).
  @inlinable
  static func exp(_ f: Double) -> Double
  {
    Pixar.GfExp(f)
  }

  /// Return exp(f).
  @inlinable
  static func exp(_ f: Float) -> Float
  {
    Pixar.GfExp(f)
  }

  /// Return log(f).
  @inlinable
  static func log(_ f: Double) -> Double
  {
    Pixar.GfLog(f)
  }

  /// Return log(f).
  @inlinable
  static func log(_ f: Float) -> Float
  {
    Pixar.GfLog(f)
  }

  /// Return floor(f).
  @inlinable
  static func floor(_ f: Double) -> Double
  {
    Pixar.GfFloor(f)
  }

  /// Return floor(f).
  @inlinable
  static func floor(_ f: Float) -> Float
  {
    Pixar.GfFloor(f)
  }

  /// Return ceil(f).
  @inlinable
  static func ceil(_ f: Double) -> Double
  {
    Pixar.GfCeil(f)
  }

  /// Return ceil(f).
  @inlinable
  static func ceil(_ f: Float) -> Float
  {
    Pixar.GfCeil(f)
  }

  /// Return abs(f).
  @inlinable
  static func abs(_ f: Double) -> Double
  {
    Pixar.GfAbs(f)
  }

  /// Return abs(f).
  @inlinable
  static func abs(_ f: Float) -> Float
  {
    Pixar.GfAbs(f)
  }

  /// Return round(f).
  @inlinable
  static func round(_ f: Double) -> Double
  {
    Pixar.GfRound(f)
  }

  /// Return round(f).
  @inlinable
  static func round(_ f: Float) -> Float
  {
    Pixar.GfRound(f)
  }

  /// Return pow(f, p).
  @inlinable
  static func pow(_ f: Double, _ p: Double) -> Double
  {
    Pixar.GfPow(f, p)
  }

  /// Return pow(f, p).
  @inlinable
  static func pow(_ f: Float, _ p: Float) -> Float
  {
    Pixar.GfPow(f, p)
  }

  /// Return sin(v).
  @inlinable
  static func sin(_ v: Double) -> Double
  {
    Pixar.GfSin(v)
  }

  /// Return sin(v).
  @inlinable
  static func sin(_ v: Float) -> Float
  {
    Pixar.GfSin(v)
  }

  /// Return cos(v).
  @inlinable
  static func cos(_ v: Double) -> Double
  {
    Pixar.GfCos(v)
  }

  /// Return cos(v).
  @inlinable
  static func cos(_ v: Float) -> Float
  {
    Pixar.GfCos(v)
  }

  /// Return sin(v) in s and cos(v) in c.
  @inlinable
  static func sinCos(_ v: Double, _ s: inout Double, _ c: inout Double)
  {
    Pixar.GfSinCos(v, &s, &c)
  }

  /// Return sin(v) in s and cos(v) in c.
  @inlinable
  static func sinCos(_ v: Float, _ s: inout Float, _ c: inout Float)
  {
    Pixar.GfSinCos(v, &s, &c)
  }

  /// Return the resulting of clamping value to lie between
  /// min and max. This function is also defined for GfVecs.
  @inlinable
  static func clamp(_ value: Double, _ min: Double, _ max: Double) -> Double
  {
    Pixar.GfClamp(value, min, max)
  }

  /// Return the resulting of clamping value to lie between
  /// min and max. This function is also defined for GfVecs.
  @inlinable
  static func clamp(_ value: Float, _ min: Float, _ max: Float) -> Float
  {
    Pixar.GfClamp(value, min, max)
  }

  /// The mod function with "correct" behaviour for negative numbers.
  ///
  /// If a = `n b` for some integer n, zero is returned.
  /// Otherwise, for positive a, the value returned is `fmod(a,b)`,
  /// and for negative `a`, the value returned is `fmod(a,b) + b`.
  @inlinable
  static func mod(_ a: Double, _ b: Double) -> Double
  {
    Pixar.GfMod(a, b)
  }

  /// The mod function with "correct" behaviour for negative numbers.
  ///
  /// If a = `n b` for some integer n, zero is returned.
  /// Otherwise, for positive a, the value returned is `fmod(a,b)`,
  /// and for negative `a`, the value returned is `fmod(a,b) + b`.
  @inlinable
  static func mod(_ a: Float, _ b: Float) -> Float
  {
    Pixar.GfMod(a, b)
  }

  /* -------------------------------------------------- */
}
