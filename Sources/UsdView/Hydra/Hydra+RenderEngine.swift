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

import Foundation
import PixarUSD

public enum Hydra
{
  public class RenderEngine: HdRenderEngine
  {
    public var stage: UsdStageRefPtr

    public var engine: any HdRenderEngine

    public required init(stage: UsdStageRefPtr)
    {
      self.stage = stage

      #if os(macOS) || os(iOS) // todo: visionOS, tvOS, watchOS
        engine = Hydra.MTLRenderer(stage: stage)
      #elseif os(Linux) || os(Windows) || os(Android)
        engine = Hydra.GLRenderer(stage: stage)
      #else
        engine = Hydra.NORenderer(stage: stage)
      #endif
    }

    public func info()
    {
      engine.info()
    }

    public func draw()
    {
      engine.draw()
    }
  }
}
