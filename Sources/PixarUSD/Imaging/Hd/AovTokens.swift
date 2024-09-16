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

import Hd

private extension Hd
{
  /**
   * Private struct to hold the static
   * data for the Hd library's AOV tokens. */
  struct AovStaticData
  {
    static let shared = AovStaticData()
    private init()
    {}

    let tokens = Pixar.HdAovTokens_StaticTokenType()
  }
}

public extension Hd
{
  /**
   * # Hd.AovTokens
   *
   * ## Overview
   *
   * Public, client facing api to access
   * the static Hd AOV tokens. */
  enum AovTokens: String, CaseIterable
  {
    case color
    case depth
    case depthStencil
    case cameraDepth
    case primId
    case instanceId
    case elementId
    case edgeId
    case pointId
    case pEye
    case nEye
    case patchCoord
    case primitiveParam
    case normal
    case primvars = "primvars:"
    case lpe = "lpe:"
    case shader = "shader:"

    public var token: Tf.Token
    {
      switch self
      {
        case .color: AovStaticData.shared.tokens.color
        case .depth: AovStaticData.shared.tokens.depth
        case .depthStencil: AovStaticData.shared.tokens.depthStencil
        case .cameraDepth: AovStaticData.shared.tokens.cameraDepth
        case .primId: AovStaticData.shared.tokens.primId
        case .instanceId: AovStaticData.shared.tokens.instanceId
        case .elementId: AovStaticData.shared.tokens.elementId
        case .edgeId: AovStaticData.shared.tokens.edgeId
        case .pointId: AovStaticData.shared.tokens.pointId
        case .pEye: AovStaticData.shared.tokens.Peye
        case .nEye: AovStaticData.shared.tokens.Neye
        case .patchCoord: AovStaticData.shared.tokens.patchCoord
        case .primitiveParam: AovStaticData.shared.tokens.primitiveParam
        case .normal: AovStaticData.shared.tokens.normal
        case .primvars: AovStaticData.shared.tokens.primvars
        case .lpe: AovStaticData.shared.tokens.lpe
        case .shader: AovStaticData.shared.tokens.shader
      }
    }
  }
}
