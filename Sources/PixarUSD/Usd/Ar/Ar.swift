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

import Ar
import ArPrototypes

public typealias ArResolver = ArResolvable & Pixar.ArResolver
public typealias ArDefaultResolver = ArResolvable & Pixar.ArDefaultResolver

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
