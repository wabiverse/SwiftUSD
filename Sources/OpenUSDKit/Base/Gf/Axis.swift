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

public protocol Axis: CaseIterable, Dimensional
{
  static var dimension: Int { get }
}

public enum Axis2: Int, Axis
{
  case x = 0
  case y = 1

  public typealias AxisCount = Axis2

  public static var dimension: Int { 2 }

  public func getAxis() -> Int
  {
    switch self
    {
      case .x: 0
      case .y: 1
    }
  }
}

public enum Axis3: Int, Axis
{
  case x = 0
  case y = 1
  case z = 2

  public typealias AxisCount = Axis3

  public static var dimension: Int { 3 }

  public func getAxis() -> Int
  {
    switch self
    {
      case .x: 0
      case .y: 1
      case .z: 2
    }
  }
}

public enum Axis4: Int, Axis
{
  case x = 0
  case y = 1
  case z = 2
  case w = 3

  public typealias AxisCount = Axis4

  public static var dimension: Int { 4 }

  public func getAxis() -> Int
  {
    switch self
    {
      case .x: 0
      case .y: 1
      case .z: 2
      case .w: 3
    }
  }
}

public enum Axis16: Int, Axis
{
  case m00 = 0
  case m01 = 1
  case m02 = 2
  case m03 = 3
  case m10 = 4
  case m11 = 5
  case m12 = 6
  case m13 = 7
  case m20 = 8
  case m21 = 9
  case m22 = 10
  case m23 = 11
  case m30 = 12
  case m31 = 13
  case m32 = 14
  case m33 = 15

  public typealias AxisCount = Axis16

  public static var dimension: Int { 16 }
}
