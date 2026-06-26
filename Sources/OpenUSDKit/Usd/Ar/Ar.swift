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

#if canImport(Ar)
  import Ar
#else
  import OpenUSD
#endif

public typealias ArResolver = Pixar.ArResolver

#if canImport(Ar)
public typealias ArDefaultResolver = Pixar.ArDefaultResolver
#endif

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
  
  #if canImport(Ar)
  public typealias DefaultResolver = ArDefaultResolver
  #endif
}

#if !canImport(Ar)
extension Pixar
{
  public typealias ArResolver = Overlay.ArResolverWrapper
}
#endif

