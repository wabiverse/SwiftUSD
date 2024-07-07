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

import ArTypes
import CxxStdlib
import Foundation

public typealias ArResolvedPath = Pixar.ArResolvedPath

/* ----
 cxx implementation.
 ---- */

public protocol ArResolvable
{
  init()

  func CreateIdentifier(_ assetPath: std.string, _ anchorAssetPath: ArResolvedPath) -> std.string

  func CreateIdentifierForNewAsset(_ assetPath: std.string, _ anchorAssetPath: ArResolvedPath) -> std.string

  func Resolve(_ assetPath: std.string) -> ArResolvedPath

  func ResolveForNewAsset(_ assetPath: std.string) -> ArResolvedPath

  /* ----
   virtual functions.
                 ---- */

  func _CreateIdentifier(_ assetPath: std.string, _ anchorAssetPath: ArResolvedPath) -> std.string

  func _CreateIdentifierForNewAsset(_ assetPath: std.string, _ anchorAssetPath: ArResolvedPath) -> std.string

  func _Resolve(_ assetPath: std.string) -> ArResolvedPath
}

public extension ArResolvable
{
  private init()
  {
    self.init()
  }

  func createIdentifier(_ path: std.string, anchorPath: ArResolvedPath = .init()) -> std.string
  {
    CreateIdentifier(path, anchorPath)
  }

  func createIdentifierForNewAsset(_ path: std.string, anchorPath: ArResolvedPath = .init()) -> std.string
  {
    CreateIdentifierForNewAsset(path, anchorPath)
  }

  func resolve(path: String) -> ArResolvedPath
  {
    Resolve(std.string(path))
  }

  func resolveForNewAsset(path: String) -> ArResolvedPath
  {
    ResolveForNewAsset(std.string(path))
  }

  /* ----
   virtual functions.
                 ---- */

  func _createIdentifier(_ path: std.string, _ anchorPath: ArResolvedPath) -> std.string
  {
    _CreateIdentifier(path, anchorPath)
  }

  func _createIdentifierForNewAsset(_ path: std.string, _ anchorPath: ArResolvedPath) -> std.string
  {
    _CreateIdentifierForNewAsset(path, anchorPath)
  }

  func _resolve(path: String) -> ArResolvedPath
  {
    _Resolve(std.string(path))
  }

  func CreateIdentifier(_: std.string, _: ArPrototypes.ArResolvedPath) -> std.string
  {
    .init()
  }

  func CreateIdentifierForNewAsset(_: std.string, _: ArPrototypes.ArResolvedPath) -> std.string
  {
    .init()
  }

  func Resolve(_: std.string) -> ArPrototypes.ArResolvedPath
  {
    .init()
  }

  func ResolveForNewAsset(_: std.string) -> ArPrototypes.ArResolvedPath
  {
    .init()
  }

  func _CreateIdentifier(_: std.string, _: ArPrototypes.ArResolvedPath) -> std.string
  {
    .init()
  }

  func _CreateIdentifierForNewAsset(_: std.string, _: ArPrototypes.ArResolvedPath) -> std.string
  {
    .init()
  }

  func _Resolve(_: std.string) -> ArResolvedPath
  {
    .init()
  }
}
