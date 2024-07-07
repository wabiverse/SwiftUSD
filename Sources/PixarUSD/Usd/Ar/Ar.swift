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

import Ar
import ArPrototypes

public typealias ArResolver = Pixar.ArResolver & ArResolvable
public typealias ArDefaultResolver = Pixar.ArDefaultResolver & ArResolvable

/**
 * # ``Ar``
 *
 * **Asset Resolution**
 *
 * ## Overview
 *
 * **Ar** is the **asset resolution** library, and is responsible for querying, reading, and
 * writing asset data. It provides several interfaces that allow **USD** to access
 * an asset without knowing how that asset is physically stored. */
public enum Ar
{
  public typealias Resolver = ArResolver
  public typealias DefaultResolver = ArDefaultResolver
}

public extension Pixar.ArDefaultResolver
{
  private borrowing func GetCurrentContextPtrCopy() -> ArDefaultResolverContext
  {
    __GetCurrentContextPtrUnsafe().pointee
  }

  var currentContext: ArDefaultResolverContext
  {
    GetCurrentContextPtrCopy()
  }

  func _Resolve(_ path: std.string) -> Pixar.ArResolvedPath
  {
    print("woohoo!")

    if path.empty()
    {
      return Pixar.ArResolvedPath()
    }

    if !path.empty(), Pixar.TfIsRelativePath(path)
    {
      // First try to resolve relative paths against the current
      // working directory.
      var resolvedPath = Pixar.ArDefaultResolver._ResolveAnchored(Pixar.ArchGetCwd(), path)
      if !resolvedPath.empty()
      {
        return resolvedPath
      }

      // If that fails and the path is a search path, try to resolve
      // against each directory in the specified search paths.
      if !path.empty() && Pixar.TfIsRelativePath(path),
         path.find(std.string("./")) == 0 || path.find(std.string("../")) == 0
      {
        let contexts: [Pixar.ArDefaultResolverContext] = [
          currentContext,
          GetFallbackContext()
        ]

        for ctx in contexts
        {
          for searchPath in ctx.searchPath
          {
            resolvedPath = Pixar.ArDefaultResolver._ResolveAnchored(std.string(searchPath), path)
            if !resolvedPath.empty()
            {
              return resolvedPath
            }
          }
        }
      }

      return Pixar.ArResolvedPath()
    }

    return Pixar.ArDefaultResolver._ResolveAnchored(std.string(), path)
  }
}
