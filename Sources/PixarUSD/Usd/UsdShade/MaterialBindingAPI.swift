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

public typealias UsdShadeMaterialBindingAPI = Pixar_v23.UsdShadeMaterialBindingAPI

public extension Pixar.UsdShade
{
  typealias MaterialBindingAPI = UsdShadeMaterialBindingAPI
}

public extension Pixar.UsdShade.MaterialBindingAPI
{
  @discardableResult
  static func apply(_ prim: Pixar.Usd.Prim) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim)
  }

  /* ----- convenience. -----  */

  @discardableResult
  static func apply(_ prim: UsdGeomSphere) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCapsule) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCylinder) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCube) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCone) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomPlane) -> Pixar.UsdShade.MaterialBindingAPI
  {
    Pixar.UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  /* ------------------------  */

  @discardableResult
  func bind(_ material: Pixar.UsdShade.Material,
            strength: Pixar.UsdShade.Tokens = .fallbackStrength,
            purpose: Pixar.UsdShade.Tokens = .allPurpose) -> Bool
  {
    Bind(material, strength.getToken(), purpose.getToken())
  }
}
