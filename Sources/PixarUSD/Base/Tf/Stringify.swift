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

/**
 * A macro that produces a string containing
 * the source code that generated the value.
 *
 * For example:
 *
 *   #stringify(x + y)
 *
 * produces a string `"x + y"`. */
@freestanding(expression)
public macro stringify<T>(_ value: T) -> String = #externalMacro(module: "PixarMacros", type: "StringifyMacro")
