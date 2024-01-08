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

import Foundation
import Usd

public protocol Prim
{
  var path: Pixar.Sdf.Path { get }

  var name: Pixar.TfToken { get }

  var children: [any Prim] { get }
}

public struct UsdPrim
{
  public var path: Pixar.Sdf.Path
  public var type: PrimType

  public init(_ path: String, type: PrimType = .token(Pixar.TfToken()))
  {
    self.path = Pixar.Sdf.Path("/\(path)")
    self.type = type
  }
}

public extension UsdPrim
{
  enum PrimType
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
    case distantLight
    case diskLight
    case rectLight
    case sphereLight
    case cylinderLight
    case geometryLight
    case domeLight
    case portalLight
    case xform
    case xformable
    case xformCommonAPI
    case lightAPI
    case meshLightAPI
    case volumeLightAPI
    case motionAPI
    case primvarsAPI
    case geomModelAPI
    case visibilityAPI
    case token(Pixar.TfToken)
    case group([UsdPrim])
  }
}
