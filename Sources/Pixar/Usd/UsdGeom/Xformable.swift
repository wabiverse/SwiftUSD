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

import UsdGeom

public typealias UsdGeomXformable = Pixar.UsdGeomXformable

public extension Pixar.UsdGeom
{
  typealias Xformable = UsdGeomXformable
}

@attached(member, names: arbitrary, conformances: GeomXformable)
public macro Xformable() = #externalMacro(module: "PixarMacros", type: "PixarXformableMacro")

public protocol GeomXformable
{
  func addXformOp(type: UsdGeomXformOp.`Type`,
                  precision: UsdGeomXformOp.Precision,
                  suffix: Pixar.TfToken,
                  invert: Bool) -> UsdGeomXformOp

  func addTranslateOp(precision: UsdGeomXformOp.Precision,
                      suffix: Pixar.TfToken,
                      invert: Bool) -> UsdGeomXformOp

  func addScaleOp(precision: UsdGeomXformOp.Precision,
                  suffix: Pixar.TfToken,
                  invert: Bool) -> UsdGeomXformOp

  func addRotateXOp(precision: UsdGeomXformOp.Precision,
                    suffix: Pixar.TfToken,
                    invert: Bool) -> UsdGeomXformOp

  func addRotateYOp(precision: UsdGeomXformOp.Precision,
                    suffix: Pixar.TfToken,
                    invert: Bool) -> UsdGeomXformOp

  func addRotateZOp(precision: UsdGeomXformOp.Precision,
                    suffix: Pixar.TfToken,
                    invert: Bool) -> UsdGeomXformOp
}

@Xformable
extension UsdGeomXformable: GeomXformable
{}
