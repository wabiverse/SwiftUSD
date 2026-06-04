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
        self.AddXformOp(type, precision, suffix, invert) as UsdGeomXformOp
      }

      public func addTranslateOp(precision: UsdGeomXformOp.Precision = .double,
                                 suffix: Tf.Token = Tf.Token(),
                                 invert: Bool = false) -> UsdGeomXformOp
      {
        self.AddTranslateOp(precision, suffix, invert) as UsdGeomXformOp
      }

      public func addScaleOp(precision: UsdGeomXformOp.Precision = .float,
                             suffix: Tf.Token = Tf.Token(),
                             invert: Bool = false) -> UsdGeomXformOp
      {
        self.AddScaleOp(precision, suffix, invert) as UsdGeomXformOp
      }

      public func addRotateXOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        self.AddRotateXOp(precision, suffix, invert) as UsdGeomXformOp
      }

      public func addRotateYOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        self.AddRotateYOp(precision, suffix, invert) as UsdGeomXformOp
      }

      public func addRotateZOp(precision: UsdGeomXformOp.Precision = .float,
                               suffix: Tf.Token = Tf.Token(),
                               invert: Bool = false) -> UsdGeomXformOp
      {
        self.AddRotateZOp(precision, suffix, invert) as UsdGeomXformOp
      }
      """

    return [decl]
  }
}
