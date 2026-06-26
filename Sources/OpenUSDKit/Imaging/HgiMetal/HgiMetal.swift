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
  #if canImport(HgiMetal)
    import HgiMetal
  #else
    import OpenUSD
  #endif

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

#if !canImport(HgiMetal)
extension Pixar
{
  public typealias HgiMetal = Overlay.HgiMetalWrapper
}

extension Pixar.HgiMetal
{
  public static func Create() -> Pixar.HgiMetal
  {
    Overlay.HgiMetalWrapper(nil)
  }
}

extension Overlay
{
  public static func GetValue(_ value: Pixar.HgiMetal) -> VtValue
  {
    value.VtValueWrappingHgiRawPtr()
  }
}
#endif
