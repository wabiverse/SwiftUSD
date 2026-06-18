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

#if canImport(Metal)
  import Metal
  import HgiMetal

  public enum HgiMetal
  {
    public static func createHgi() -> Pixar.HgiMetal
    {
      Pixar.HgiMetal.Create()
    }
  }

  public extension Pixar.HgiMetal
  {
    var apiVersion: Int
    {
      Int(GetAPIVersion())
    }

    private borrowing func GetPrimaryDeviceCopy() -> MTLDevice
    {
      GetPrimaryDevice()
    }

    var device: MTLDevice
    {
      GetPrimaryDeviceCopy()
    }

    var value: VtValue
    {
      Overlay.GetValue(self)
    }
  }
#endif /* canImport(Metal) */
