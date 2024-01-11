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

import UsdGeom

private extension Pixar.UsdGeom
{
  /**
   * Private struct to hold the static
   * data for the Pixar.UsdGeom library. */
  struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar_v23.UsdGeomTokensType()
  }
}

public extension Pixar.UsdGeom
{
  /**
   * # Pixar.UsdGeom.Tokens
   *
   * ### Overview
   *
   * Public, client facing api to access
   * the static Pixar.UsdGeom tokens. */
  enum Tokens: CaseIterable
  {
    case basisCurves
    case hermiteCurves
    case nurbsCurves
    case nurbsPatch
    case boundable
    case imageable
    case mesh
    case pointBased
    case pointInstancer
    case points
    case plane
    case camera
    case capsule
    case cone
    case cube
    case curves
    case cylinder
    case sphere
    case scope
    case geomSubset
    case gprim
    case xform
    case xformable
    case xformCommonAPI
    case motionAPI
    case primvarsAPI
    case geomModelAPI
    case visibilityAPI

    public var token: Pixar.Tf.Token
    {
      switch self
      {
        case .basisCurves: StaticData.shared.tokens.BasisCurves
        case .hermiteCurves: StaticData.shared.tokens.HermiteCurves
        case .nurbsCurves: StaticData.shared.tokens.NurbsCurves
        case .nurbsPatch: StaticData.shared.tokens.NurbsPatch
        case .boundable: StaticData.shared.tokens.Boundable
        case .imageable: StaticData.shared.tokens.Imageable
        case .mesh: StaticData.shared.tokens.Mesh
        case .pointBased: StaticData.shared.tokens.PointBased
        case .pointInstancer: StaticData.shared.tokens.PointInstancer
        case .points: StaticData.shared.tokens.Points
        case .plane: StaticData.shared.tokens.Plane
        case .camera: StaticData.shared.tokens.Camera
        case .capsule: StaticData.shared.tokens.Capsule
        case .cone: StaticData.shared.tokens.Cone
        case .cube: StaticData.shared.tokens.Cube
        case .curves: StaticData.shared.tokens.Curves
        case .cylinder: StaticData.shared.tokens.Cylinder
        case .sphere: StaticData.shared.tokens.Sphere
        case .scope: StaticData.shared.tokens.Scope
        case .geomSubset: StaticData.shared.tokens.GeomSubset
        case .gprim: StaticData.shared.tokens.Gprim
        case .xform: StaticData.shared.tokens.Xform
        case .xformable: StaticData.shared.tokens.Xformable
        case .xformCommonAPI: StaticData.shared.tokens.XformCommonAPI
        case .motionAPI: StaticData.shared.tokens.MotionAPI
        case .primvarsAPI: StaticData.shared.tokens.PrimvarsAPI
        case .geomModelAPI: StaticData.shared.tokens.GeomModelAPI
        case .visibilityAPI: StaticData.shared.tokens.VisibilityAPI
      }
    }
  }
}
