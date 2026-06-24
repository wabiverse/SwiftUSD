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

import ArgumentParser
import Foundation

struct UpdateArguments: ParsableArguments
{
  /// The version of OpenUSD to migrate to.
  @Argument(
    help: "The version of OpenUSD to migrate to.")
  var usdVersion: String?

  /// The directory containing the package to update.
  @Option(
    name: [.customShort("d"), .customLong("directory")],
    help: "The directory containing the package to update.",
    transform: URL.init(fileURLWithPath:)
  )
  var packageDirectory: URL?
}
