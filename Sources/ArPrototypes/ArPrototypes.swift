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

import ArTypes
import CxxStdlib
import Foundation

/* ----
 cxx implementation.
 ---- */

public protocol ArResolvable
{
  func CreateIdentifier(_ assetPath: std.string, _ anchorAssetPath: Pixar.ArResolvedPath) -> std.string

  func CreateIdentifierForNewAsset(_ assetPath: std.string, _ anchorAssetPath: Pixar.ArResolvedPath) -> std.string

  func Resolve(_ assetPath: std.string) -> Pixar.ArResolvedPath

  func ResolveForNewAsset(_ assetPath: std.string) -> Pixar.ArResolvedPath

  /* ----
   virtual functions.
                 ---- */

  func _CreateIdentifier(_ assetPath: std.string, _ anchorAssetPath: Pixar.ArResolvedPath) -> std.string

  func _CreateIdentifierForNewAsset(_ assetPath: std.string, _ anchorAssetPath: Pixar.ArResolvedPath) -> std.string

  func _Resolve(_ path: std.string) -> Pixar.ArResolvedPath
}

public extension ArResolvable
{
  func createIdentifier(_ path: std.string, anchorPath: Pixar.ArResolvedPath = .init()) -> std.string
  {
    CreateIdentifier(path, anchorPath)
  }

  func createIdentifierForNewAsset(_ path: std.string, anchorPath: Pixar.ArResolvedPath = .init()) -> std.string
  {
    CreateIdentifierForNewAsset(path, anchorPath)
  }

  func resolve(path: String) -> Pixar.ArResolvedPath
  {
    Resolve(std.string(path))
  }

  func resolveForNewAsset(path: String) -> Pixar.ArResolvedPath
  {
    ResolveForNewAsset(std.string(path))
  }

  /* ----
   virtual functions.
                 ---- */

  func _createIdentifier(_ path: std.string, _ anchorPath: Pixar.ArResolvedPath) -> std.string
  {
    _CreateIdentifier(path, anchorPath)
  }

  func _createIdentifierForNewAsset(_ path: std.string, _ anchorPath: Pixar.ArResolvedPath) -> std.string
  {
    _CreateIdentifierForNewAsset(path, anchorPath)
  }

  func CreateIdentifier(_: std.string, _: Pixar.ArResolvedPath) -> std.string
  {
    .init()
  }

  func CreateIdentifierForNewAsset(_: std.string, _: Pixar.ArResolvedPath) -> std.string
  {
    .init()
  }

  func Resolve(_: std.string) -> Pixar.ArResolvedPath
  {
    .init()
  }

  func ResolveForNewAsset(_: std.string) -> Pixar.ArResolvedPath
  {
    .init()
  }

  func _CreateIdentifier(_: std.string, _: Pixar.ArResolvedPath) -> std.string
  {
    .init()
  }

  func _CreateIdentifierForNewAsset(_: std.string, _: Pixar.ArResolvedPath) -> std.string
  {
    .init()
  }

  func _Resolve(_: std.string) -> Pixar.ArResolvedPath
  {
    .init()
  }
}
