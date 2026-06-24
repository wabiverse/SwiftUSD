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

#if os(macOS)
  import Darwin

  /// A signal action, typealiased to avoid confusion with the `sigaction` function.
  typealias SignalAction = sigaction

  /// A signal that can be caught.
  enum Signal: Int32, CaseIterable
  {
    case hangUp = 1
    case interrupt = 2
    case quit = 3
    case abort = 6
    case kill = 9
    case alarm = 14
    case terminate = 15
  }

  /// Sets a trap for the specified signal.
  func trap(_ signal: Signal, action: @escaping @convention(c) (Int32) -> Void)
  {
    var signalAction = SignalAction(__sigaction_u: unsafeBitCast(action, to: __sigaction_u.self), sa_mask: 0, sa_flags: 0)
    sigaction(signal.rawValue, &signalAction, nil)
  }
#endif
