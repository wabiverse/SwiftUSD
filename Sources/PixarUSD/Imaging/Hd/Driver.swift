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

import Hd

/**
 * ``HdDriver``
 *
 * ## Overview
 *
 * Represents a device object, commonly a render
 * device, that is owned by the application and passed to
 * HdRenderIndex. The RenderIndex passes it to the render
 * delegate and rendering tasks. The application manages
 * the lifetime (destruction) of HdDriver and must ensure
 * it remains valid while Hydra is running. */
public typealias HdDriver = Pixar.HdDriver

public extension Hd
{
  /**
   * ``Driver``
   *
   * ## Overview
   *
   * Represents a device object, commonly a render
   * device, that is owned by the application and passed to
   * HdRenderIndex. The RenderIndex passes it to the render
   * delegate and rendering tasks. The application manages
   * the lifetime (destruction) of HdDriver and must ensure
   * it remains valid while Hydra is running. */
  typealias Driver = HdDriver
}

public extension Hd.Driver
{
  init(name: Hgi.Tokens, driver: Vt.Value)
  {
    self.init(name: name.token, driver: driver)
  }
}
