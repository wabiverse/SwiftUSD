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

import HgiGL

public enum HgiGL
{
  public static func createHgi() -> Pixar.HgiGL
  {
    Pixar.HgiGL.Create()
  }
}

public extension Pixar.HgiGL
{
  private borrowing func GetPrimaryDeviceCopy() -> Pixar.HgiGLDevice
  {
    GetPrimaryDevice()
  }

  var device: Pixar.HgiGLDevice
  {
    GetPrimaryDeviceCopy()
  }

  var value: VtValue
  {
    Overlay.GetValue(self)
  }
}
