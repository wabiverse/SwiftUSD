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
