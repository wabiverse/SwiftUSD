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

import Combine
import MetalKit
import SwiftUI

public extension Hydra
{
  enum MTLEnvironment
  {
    struct ColorPixelFormatKey: EnvironmentKey
    {
      static let defaultValue: MTLPixelFormat = .bgra8Unorm
    }

    struct FramebufferOnlyKey: EnvironmentKey
    {
      static let defaultValue: Bool = true
    }

    struct DrawableSizeKey: EnvironmentKey
    {
      static var defaultValue: CGSize? = nil
    }

    struct AutoResizeDrawableKey: EnvironmentKey
    {
      static var defaultValue: Bool = true
    }

    struct ClearColorKey: EnvironmentKey
    {
      static var defaultValue: MTLClearColor = .init(red: 0.0, green: 0.0, blue: 0.0, alpha: 1.0)
    }

    struct PreferredFramesPerSecondKey: EnvironmentKey
    {
      static var defaultValue: Int = 60
    }

    struct IsPausedKey: EnvironmentKey
    {
      static var defaultValue: Bool = false
    }

    struct EnableSetNeedsDisplayKey: EnvironmentKey
    {
      static var defaultValue: Bool = false
    }

    struct PresentWithTransactionKey: EnvironmentKey
    {
      static var defaultValue: Bool = false
    }

    struct SetNeedsDisplayTriggerKey: EnvironmentKey
    {
      static var defaultValue: Hydra.MTLView.SetNeedsDisplayTrigger? = nil
    }
  }
}

extension EnvironmentValues
{
  var colorPixelFormat: MTLPixelFormat
  {
    get { self[Hydra.MTLEnvironment.ColorPixelFormatKey.self] }
    set { self[Hydra.MTLEnvironment.ColorPixelFormatKey.self] = newValue }
  }

  var framebufferOnly: Bool
  {
    get { self[Hydra.MTLEnvironment.FramebufferOnlyKey.self] }
    set { self[Hydra.MTLEnvironment.FramebufferOnlyKey.self] = newValue }
  }

  var drawableSize: CGSize?
  {
    get { self[Hydra.MTLEnvironment.DrawableSizeKey.self] }
    set { self[Hydra.MTLEnvironment.DrawableSizeKey.self] = newValue }
  }

  var autoResizeDrawable: Bool
  {
    get { self[Hydra.MTLEnvironment.AutoResizeDrawableKey.self] }
    set { self[Hydra.MTLEnvironment.AutoResizeDrawableKey.self] = newValue }
  }

  var clearColor: MTLClearColor
  {
    get { self[Hydra.MTLEnvironment.ClearColorKey.self] }
    set { self[Hydra.MTLEnvironment.ClearColorKey.self] = newValue }
  }

  var preferredFramesPerSecond: Int
  {
    get { self[Hydra.MTLEnvironment.PreferredFramesPerSecondKey.self] }
    set { self[Hydra.MTLEnvironment.PreferredFramesPerSecondKey.self] = newValue }
  }

  var enableSetNeedsDisplay: Bool
  {
    get { self[Hydra.MTLEnvironment.EnableSetNeedsDisplayKey.self] }
    set { self[Hydra.MTLEnvironment.EnableSetNeedsDisplayKey.self] = newValue }
  }

  var isPaused: Bool
  {
    get { self[Hydra.MTLEnvironment.IsPausedKey.self] }
    set { self[Hydra.MTLEnvironment.IsPausedKey.self] = newValue }
  }

  var presentWithTransaction: Bool
  {
    get { self[Hydra.MTLEnvironment.PresentWithTransactionKey.self] }
    set { self[Hydra.MTLEnvironment.PresentWithTransactionKey.self] = newValue }
  }

  var setNeedsDisplayTrigger: Hydra.MTLView.SetNeedsDisplayTrigger?
  {
    get { self[Hydra.MTLEnvironment.SetNeedsDisplayTriggerKey.self] }
    set { self[Hydra.MTLEnvironment.SetNeedsDisplayTriggerKey.self] = newValue }
  }
}

public extension View
{
  func colorPixelFormat(_ value: MTLPixelFormat) -> some View
  {
    environment(\.colorPixelFormat, value)
  }

  func framebufferOnly(_ value: Bool) -> some View
  {
    environment(\.framebufferOnly, value)
  }

  func drawableSize(_ value: CGSize?) -> some View
  {
    environment(\.drawableSize, value)
  }

  func autoResizeDrawable(_ value: Bool) -> some View
  {
    environment(\.autoResizeDrawable, value)
  }

  func clearColor(_ value: MTLClearColor) -> some View
  {
    environment(\.clearColor, value)
  }

  func preferredFramesPerSecond(_ value: Int) -> some View
  {
    environment(\.preferredFramesPerSecond, value)
  }

  func isPaused(_ value: Bool) -> some View
  {
    environment(\.isPaused, value)
  }

  func enableSetNeedsDisplay(_ value: Bool) -> some View
  {
    environment(\.enableSetNeedsDisplay, value)
  }

  func presentWithTransaction(_ value: Bool) -> some View
  {
    environment(\.presentWithTransaction, value)
  }

  func setNeedsDisplayTrigger(_ value: Hydra.MTLView.SetNeedsDisplayTrigger?) -> some View
  {
    environment(\.setNeedsDisplayTrigger, value)
  }

  @ViewBuilder
  func drawingMode(_ value: Hydra.MTLView.DrawingMode) -> some View
  {
    switch value
    {
      case let .timeUpdates(preferredFramesPerSecond):
        isPaused(false).enableSetNeedsDisplay(false).preferredFramesPerSecond(preferredFramesPerSecond)

      case let .drawNotifications(setNeedsDisplayTrigger):
        isPaused(true).enableSetNeedsDisplay(true).setNeedsDisplayTrigger(setNeedsDisplayTrigger)
    }
  }
}
