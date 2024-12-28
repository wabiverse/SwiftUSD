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

#if canImport(UsdImagingGL)
  import UsdImagingGL

  public typealias UsdImagingGLRenderParams = Pixar.UsdImagingGLRenderParams

  public extension UsdImagingGL
  {
    typealias RenderParams = UsdImagingGLRenderParams
  }
#endif // canImport(UsdImagingGL)
