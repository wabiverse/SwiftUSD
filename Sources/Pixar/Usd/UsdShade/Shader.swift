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
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

import UsdShade

public typealias UsdShadeShader = Pixar.UsdShadeShader

public extension Pixar.UsdShade
{
  typealias Shader = UsdShadeShader
}

public extension Pixar.UsdShade.Shader
{
  @discardableResult
  static func define(_ stage: StageRefPtr, path: Pixar.Sdf.Path) -> Pixar.UsdShade.Shader
  {
    Pixar.UsdShade.Shader.Define(stage.pointee.getPtr(), path)
  }

  @discardableResult
  static func define(_ stage: StageRefPtr, path: String) -> Pixar.UsdShade.Shader
  {
    Pixar.UsdShade.Shader.define(stage, path: .init(path))
  }

  @discardableResult
  func createIdAttr(_ defaultValue: Pixar.VtValue, writeSparsely: Bool = false) -> Pixar.UsdAttribute
  {
    CreateIdAttr(defaultValue, writeSparsely)
  }

  @discardableResult
  func createIdAttr(_ defaultValue: Pixar.TfToken, writeSparsely: Bool = false) -> Pixar.UsdAttribute
  {
    createIdAttr(Pixar.VtValue(defaultValue), writeSparsely: writeSparsely)
  }

  @discardableResult
  func createIdAttr(_ defaultValue: String, writeSparsely: Bool = false) -> Pixar.UsdAttribute
  {
    createIdAttr(Pixar.TfToken(defaultValue), writeSparsely: writeSparsely)
  }

  /**
   * Common shader ids, for convenience.
   */
  enum ShaderId: String, CaseIterable
  {
    case usdPreviewSurface = "UsdPreviewSurface"
    case usdUVTexture = "UsdUVTexture"

    public func getToken() -> Pixar.TfToken
    {
      Pixar.TfToken(rawValue)
    }
  }

  @discardableResult
  func createIdAttr(_ defaultValue: ShaderId, writeSparsely: Bool = false) -> Pixar.UsdAttribute
  {
    createIdAttr(defaultValue.getToken(), writeSparsely: writeSparsely)
  }

  @discardableResult
  mutating func createInput(for name: Pixar.TfToken, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(name, Pixar.Sdf.getValueType(for: type))
  }

  /**
   * Common shader inputs, for convenience.
   */
  enum InputName: String, CaseIterable
  {
    /* ----- usd preview surface. ----- */

    case diffuseColor
    case roughness
    case specularColor
    case metallic
    case emissiveColor
    case clearcoat
    case clearcoatRoughness
    case opacity
    case ior
    case normal
    case displacement
    case occlusion

    /* ---------- usd uv texture. ----- */

    case file
    case st
    case wrapS
    case wrapT
    case fallback
    case scale
    case bias
    case sourceColorSpace

    public func getToken() -> Pixar.TfToken
    {
      Pixar.TfToken(rawValue)
    }
  }

  @discardableResult
  mutating func createInput(for name: InputName, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(name.getToken(), Pixar.Sdf.getValueType(for: type))
  }

  @discardableResult
  mutating func createInput(for name: String, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(Pixar.TfToken(name), Pixar.Sdf.getValueType(for: type))
  }

  func connectableAPI() -> Pixar.UsdShadeConnectableAPI
  {
    ConnectableAPI()
  }
}
