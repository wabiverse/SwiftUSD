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
#if canImport(PyBundle)
  import PyBundle
#endif /* canImport(PyBundle) */

func embedPython()
{
  #if canImport(PyBundle)
    /* embed & init python. */
    PyBundler.shared.pyInit()
    PyBundler.shared.pyInfo()
  #endif /* canImport(PyBundle) */
}

enum PythonInterpreterExamples
{
  static func run()
  {
    Msg.logger.info("running python interpreter examples...")

    embedPython()

    Msg.logger.info("python interpreter examples complete.")
  }
}
