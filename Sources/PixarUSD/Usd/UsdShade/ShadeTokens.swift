/* --------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                          ::
 * --------------------------------------------------------------
 * This program is free software; you can redistribute it, and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Check out
 * the GNU General Public License for more details.
 *
 * You should have received a copy for this software license, the
 * GNU General Public License along with this program; or, if not
 * write to the Free Software Foundation, Inc., to the address of
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *       Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import UsdShade

public extension Pixar.UsdShade
{
  /**
   * Private struct to hold the static
   * data for the Pixar.UsdShade library. */
  private struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar.UsdShadeTokensType()
  }
}

public extension Pixar.UsdShade
{
  /**
   * # Pixar.UsdShade.Tokens
   *
   * ### Overview
   *
   * Public, client facing api to access
   * the static Pixar.UsdShade tokens. */
  enum Tokens: CaseIterable
  {
    case allPurpose
    case bindMaterialAs
    case coordSys
    case coordSys_MultipleApplyTemplate_Binding
    case displacement
    case fallbackStrength
    case full
    case id
    case infoId
    case infoImplementationSource
    case inputs
    case interfaceOnly
    case materialBind
    case materialBinding
    case materialBindingCollection
    case materialVariant
    case outputs
    case outputsDisplacement
    case outputsSurface
    case outputsVolume
    case preview
    case sdrMetadata
    case sourceAsset
    case sourceCode
    case strongerThanDescendants
    case subIdentifier
    case surface
    case universalRenderContext
    case universalSourceType
    case volume
    case weakerThanDescendants
    case connectableAPI
    case coordSysAPI
    case material
    case materialBindingAPI
    case nodeDefAPI
    case nodeGraph
    case shader

    public func getToken() -> Pixar.Tf.Token
    {
      switch self
      {
        case .allPurpose: StaticData.shared.tokens.allPurpose
        case .bindMaterialAs: StaticData.shared.tokens.bindMaterialAs
        case .coordSys: StaticData.shared.tokens.coordSys
        case .coordSys_MultipleApplyTemplate_Binding: StaticData.shared.tokens.coordSys_MultipleApplyTemplate_Binding
        case .displacement: StaticData.shared.tokens.displacement
        case .fallbackStrength: StaticData.shared.tokens.fallbackStrength
        case .full: StaticData.shared.tokens.full
        case .id: StaticData.shared.tokens.id
        case .infoId: StaticData.shared.tokens.infoId
        case .infoImplementationSource: StaticData.shared.tokens.infoImplementationSource
        case .inputs: StaticData.shared.tokens.inputs
        case .interfaceOnly: StaticData.shared.tokens.interfaceOnly
        case .materialBind: StaticData.shared.tokens.materialBind
        case .materialBinding: StaticData.shared.tokens.materialBinding
        case .materialBindingCollection: StaticData.shared.tokens.materialBindingCollection
        case .materialVariant: StaticData.shared.tokens.materialVariant
        case .outputs: StaticData.shared.tokens.outputs
        case .outputsDisplacement: StaticData.shared.tokens.outputsDisplacement
        case .outputsSurface: StaticData.shared.tokens.outputsSurface
        case .outputsVolume: StaticData.shared.tokens.outputsVolume
        case .preview: StaticData.shared.tokens.preview
        case .sdrMetadata: StaticData.shared.tokens.sdrMetadata
        case .sourceAsset: StaticData.shared.tokens.sourceAsset
        case .sourceCode: StaticData.shared.tokens.sourceCode
        case .strongerThanDescendants: StaticData.shared.tokens.strongerThanDescendants
        case .subIdentifier: StaticData.shared.tokens.subIdentifier
        case .surface: StaticData.shared.tokens.surface
        case .universalRenderContext: StaticData.shared.tokens.universalRenderContext
        case .universalSourceType: StaticData.shared.tokens.universalSourceType
        case .volume: StaticData.shared.tokens.volume
        case .weakerThanDescendants: StaticData.shared.tokens.weakerThanDescendants
        case .connectableAPI: StaticData.shared.tokens.ConnectableAPI
        case .coordSysAPI: StaticData.shared.tokens.CoordSysAPI
        case .material: StaticData.shared.tokens.Material
        case .materialBindingAPI: StaticData.shared.tokens.MaterialBindingAPI
        case .nodeDefAPI: StaticData.shared.tokens.NodeDefAPI
        case .nodeGraph: StaticData.shared.tokens.NodeGraph
        case .shader: StaticData.shared.tokens.Shader
      }
    }
  }
}
