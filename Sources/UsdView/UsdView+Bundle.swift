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

public extension Bundle
{
  static let usdview: Bundle = {
    // in bundled app contexts, swift bundler nests compiled resources under
    // Contents/Resources - check there before falling back to .module.
    if let url = Bundle.main.resourceURL?.appendingPathComponent("Contents/Resources"),
       FileManager.default.fileExists(atPath: url.appendingPathComponent("default.metallib").path),
       let bundle = Bundle(url: url)
    { return bundle }
    return .module
  }()
}
