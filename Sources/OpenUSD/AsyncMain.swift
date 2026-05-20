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

#if os(macOS)
  import Darwin
#endif

@main
struct AsyncMain
{
  static func main() async
  {
    #if os(macOS)
      // Kill all running processes on exit
      for signal in Signal.allCases
      {
        trap(signal)
        { _ in
          processes.terminateAll()
          Foundation.exit(1)
        }
      }

      // Disable colored output if run from Xcode (the Xcode console does not support colors)
      if ProcessInfo.processInfo.environment["__XCODE_BUILT_PRODUCTS_DIR_PATHS"] != nil
      {
        setenv("NO_COLOR", "1", 1)
      }
    #endif

    await OpenUSD.main()
  }
}
