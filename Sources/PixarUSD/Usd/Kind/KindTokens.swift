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

import Kind

private extension Pixar.Kind
{
  /**
   * Private struct to hold the static
   * data for the Pixar.Kind library. */
  struct StaticData
  {
    static let shared = StaticData()
    private init()
    {}

    let tokens = Pixar.KindTokens_StaticTokenType()
  }
}

public extension Pixar.Kind
{
  /**
   * # Pixar.Kind.Tokens
   *
   * ### Overview
   *
   * Public, client facing api to access
   * the static Pixar.Kind tokens. */
  enum Tokens: CaseIterable
  {
    case model
    case component
    case group
    case assembly
    case subcomponent

    public func getToken() -> Pixar.Tf.Token
    {
      switch self
      {
        case .model: StaticData.shared.tokens.model
        case .component: StaticData.shared.tokens.component
        case .group: StaticData.shared.tokens.group
        case .assembly: StaticData.shared.tokens.assembly
        case .subcomponent: StaticData.shared.tokens.subcomponent
      }
    }
  }
}
