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

  @discardableResult
  mutating func createInput(for name: Pixar.TfToken, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(name, Pixar.SdfGetValueTypeNameForType(type))
  }

  /**
   * Common shader inputs, for convenience.
   */
  enum InputName: CaseIterable
  {
    case baseColor
    case roughness
    case metallic
    case file
    case st

    public func getToken() -> Pixar.TfToken
    {
      switch self
      {
        case .baseColor: Pixar.TfToken("baseColor")
        case .roughness: Pixar.TfToken("roughness")
        case .metallic: Pixar.TfToken("metallic")
        case .file: Pixar.TfToken("file")
        case .st: Pixar.TfToken("st")
      }
    }
  }

  @discardableResult
  mutating func createInput(for name: InputName, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(name.getToken(), Pixar.SdfGetValueTypeNameForType(type))
  }

  @discardableResult
  mutating func createInput(for name: String, type: Pixar.SdfValueTypeNameType) -> Pixar.UsdShadeInput
  {
    CreateInput(Pixar.TfToken(name), Pixar.SdfGetValueTypeNameForType(type))
  }

  func connectableAPI() -> Pixar.UsdShadeConnectableAPI
  {
    ConnectableAPI()
  }
}
