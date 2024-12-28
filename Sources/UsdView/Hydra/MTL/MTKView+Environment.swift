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

#if canImport(SwiftUI)
  import Combine
  import SwiftUI
  #if canImport(Metal) && !os(visionOS)
    import MetalKit

    extension MTKView
    {
      @discardableResult
      func apply(_ environment: EnvironmentValues) -> Self
      {
        colorPixelFormat = environment.colorPixelFormat
        framebufferOnly = environment.framebufferOnly
        if let drawableSize = environment.drawableSize
        {
          self.drawableSize = drawableSize
        }
        autoResizeDrawable = environment.autoResizeDrawable
        clearColor = environment.clearColor
        preferredFramesPerSecond = environment.preferredFramesPerSecond
        enableSetNeedsDisplay = environment.enableSetNeedsDisplay
        isPaused = environment.isPaused
        presentsWithTransaction = environment.presentWithTransaction

        return self
      }
    }
  #endif // canImport(Metal) && !os(visionOS)
#endif // canImport(SwiftUI)
