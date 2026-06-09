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

/// path to a user's documents directory.
public func documentsDirPath() -> String
{
  #if os(macOS) || os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
    let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
    return paths[0].path
  #elseif os(Android)
    // On Android, the working directory is `/` (no write permission).
    // Use the app's private files directory, which is already set by
    // UsdView.init() before createScene() is called.
    let filesDir = Pixar.Bundler.androidFilesDir
    return filesDir.isEmpty ? "/data/local/tmp" : filesDir
  #else
    return "."
  #endif
}
