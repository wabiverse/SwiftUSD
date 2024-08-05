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
import Rainbow

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
          for process in processes
          {
            process.terminate()
          }
          Foundation.exit(1)
        }
      }

      // Disable colored output if run from Xcode (the Xcode console does not support colors)
      Rainbow.enabled = ProcessInfo.processInfo.environment["__XCODE_BUILT_PRODUCTS_DIR_PATHS"] == nil
    #endif

    await OpenUSD.main()
  }
}
