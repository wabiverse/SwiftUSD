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

import Foundation
import SwiftCompilerPlugin
import SwiftSyntax
import SwiftSyntaxBuilder
import SwiftSyntaxMacros

public struct PixarXformableMacro: MemberMacro
{
  public static func expansion(of _: SwiftSyntax.AttributeSyntax,
                               providingMembersOf _: some SwiftSyntax.DeclGroupSyntax,
                               conformingTo _: [SwiftSyntax.TypeSyntax],
                               in _: some SwiftSyntaxMacros.MacroExpansionContext) throws -> [SwiftSyntax.DeclSyntax]
  {
    let decl: DeclSyntax = """
      public func addXformOp(type: UsdGeomXformOp.`Type`,
                             precision: UsdGeomXformOp.Precision = .double,
                             suffix: Tf.Token = Tf.Token(),
                             invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addXformOp(self, type, precision, suffix, invert)
        #else
          AddXformOp(type, precision, suffix, invert)
        #endif
      }

      public func addTranslateOp(precision: UsdGeomXformOp.Precision = .double,
                                 suffix: Tf.Token = Tf.Token(),
                                 invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addTranslateOp(self, precision, suffix, invert)
        #else
          AddTranslateOp(precision, suffix, invert)
        #endif
      }

      public func addScaleOp(precision: UsdGeomXformOp.Precision = .float,
                             suffix: Tf.Token = Tf.Token(),
                             invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addScaleOp(self, precision, suffix, invert)
        #else
          AddScaleOp(precision, suffix, invert)
        #endif
      }

      public func addRotateXOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addRotateXOp(self, precision, suffix, invert)
        #else
          AddRotateXOp(precision, suffix, invert)
        #endif
      }

      public func addRotateYOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addRotateYOp(self, precision, suffix, invert)
        #else
          AddRotateYOp(precision, suffix, invert)
        #endif
      }

      public func addRotateZOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        #if canImport(UsdGeom)
          Overlay.addRotateZOp(self, precision, suffix, invert)
        #else
          AddRotateZOp(precision, suffix, invert)
        #endif
      }
      """

    return [decl]
  }
}
