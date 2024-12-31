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

import Hdx

private extension Hdx
{
  /**
   * Private struct to hold the static
   * data for the Hdx library. */
  struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar.HdxColorCorrectionTokens_StaticTokenType()
  }
}

public extension Hdx
{
  /**
   * # Hdx.Tokens
   *
   * ## Overview
   *
   * Public, client facing api to access
   * the static Hdx tokens. */
  enum ColorCorrectionTokens: String, CaseIterable
  {
    case sRGB

    public var token: Tf.Token
    {
      switch self
      {
        case .sRGB: StaticData.shared.tokens.sRGB
      }
    }
  }
}

public extension Tf.Token
{
  static let sRGB = Hdx.ColorCorrectionTokens.sRGB.token
}
