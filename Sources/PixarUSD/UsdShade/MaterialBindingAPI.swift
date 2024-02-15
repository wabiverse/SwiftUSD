/* ----------------------------------------------------------------
 * :: :  M  E  T  A  V  E  R  S  E  :                            ::
 * ----------------------------------------------------------------
 * This software is Licensed under the terms of the Apache License,
 * version 2.0 (the "Apache License") with the following additional
 * modification; you may not use this file except within compliance
 * of the Apache License and the following modification made to it.
 * Section 6. Trademarks. is deleted and replaced with:
 *
 * Trademarks. This License does not grant permission to use any of
 * its trade names, trademarks, service marks, or the product names
 * of this Licensor or its affiliates, except as required to comply
 * with Section 4(c.) of this License, and to reproduce the content
 * of the NOTICE file.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND without even an
 * implied warranty of MERCHANTABILITY, or FITNESS FOR A PARTICULAR
 * PURPOSE. See the Apache License for more details.
 *
 * You should have received a copy for this software license of the
 * Apache License along with this program; or, if not, please write
 * to the Free Software Foundation Inc., with the following address
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *         Copyright (C) 2024 Wabi Foundation. All Rights Reserved.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

import UsdShade

public typealias UsdShadeMaterialBindingAPI = Pixar.UsdShadeMaterialBindingAPI

public extension UsdShade
{
  typealias MaterialBindingAPI = UsdShadeMaterialBindingAPI
}

public extension UsdShade.MaterialBindingAPI
{
  @discardableResult
  static func apply(_ prim: Usd.Prim) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim)
  }

  /* ----- convenience. -----  */

  @discardableResult
  static func apply(_ prim: UsdGeomSphere) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCapsule) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCylinder) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCube) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomCone) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  @discardableResult
  static func apply(_ prim: UsdGeomPlane) -> UsdShade.MaterialBindingAPI
  {
    UsdShade.MaterialBindingAPI.Apply(prim.GetPrim())
  }

  /* ------------------------  */

  @discardableResult
  func bind(_ material: UsdShade.Material,
            strength: UsdShade.Tokens = .fallbackStrength,
            purpose: UsdShade.Tokens = .allPurpose) -> Bool
  {
    Bind(material, strength.getToken(), purpose.getToken())
  }
}
