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

/// register all usd plugins & resources with plug registry,
/// automatically install the plugins and resources if they
/// cannot be found.
public func registerPlugins()
{
  /* Setup all usd resources (python, plugins, resources). */
  #if os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
    Pixar.Bundler.shared.setup(.resources, installPlugins: true)
  #else
    Pixar.Bundler.shared.setup(.resources, installPlugins: false)
  #endif
}

/// path to a user's documents directory.
public func documentsDirPath() -> String
{
  #if os(macOS) || os(iOS) || os(visionOS) || os(tvOS) || os(watchOS)
    let paths = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)
    return paths[0].path
  #else
    return "."
  #endif
}
