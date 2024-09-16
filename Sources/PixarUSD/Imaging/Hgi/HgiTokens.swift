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

import Hgi

private extension Hgi
{
  /**
   * Private struct to hold the static
   * data for the ``Hgi`` library. */
  struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar.HgiTokens_StaticTokenType()
  }
}

public extension Hgi
{
  /**
   * # ``Tokens``
   *
   * ## Overview
   *
   * Public, client facing api to access
   * the static ``Hgi`` tokens. */
  enum Tokens: CaseIterable
  {
    case taskDriver
    case renderDriver
    case openGL
    case metal
    case vulkan

    public var token: Tf.Token
    {
      switch self
      {
        case .taskDriver: StaticData.shared.tokens.taskDriver
        case .renderDriver: StaticData.shared.tokens.renderDriver
        case .openGL: StaticData.shared.tokens.OpenGL
        case .metal: StaticData.shared.tokens.Metal
        case .vulkan: StaticData.shared.tokens.Vulkan
      }
    }
  }
}
