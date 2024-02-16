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

import UsdGeom

private extension UsdGeom
{
  /**
   * Private struct to hold the static
   * data for the UsdGeom library. */
  struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar.UsdGeomTokensType()
  }
}

public extension UsdGeom
{
  /**
   * # UsdGeom.Tokens
   *
   * ### Overview
   *
   * Public, client facing api to access
   * the static UsdGeom tokens. */
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

    public var token: Tf.Token
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
