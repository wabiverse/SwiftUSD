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
import SwiftCrossUI

/* setup the platform backend. */

#if os(Android)
  import AndroidBackend
  public typealias PlatformBackend = AndroidBackend
#elseif os(Linux)
  import GtkBackend
  public typealias PlatformBackend = GtkBackend
#elseif os(Windows)
  import WinUIBackend
  public typealias PlatformBackend = WinUIBackend
#elseif os(macOS)
  import AppKitBackend
  public typealias PlatformBackend = AppKitBackend
#else
  import UIKitBackend
  public typealias PlatformBackend = UIKitBackend
#endif
