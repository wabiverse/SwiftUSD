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

import Ndr

/**
 * # ``Ndr``
 *
 * **Node Definition Registry**
 *
 * ## Overview
 *
 * **Ndr** provides a framework in which you can, agnostic to the node's domain
 * (shading, lighting, compositing, etc), register nodes with **Ndr**, and they
 * subsequently ask for information about those nodes. The information **Ndr**
 * provides about these nodes will be fairly generic, given that **Ndr** must
 * not cater to any specific type of node. However, specialized registries can
 * derive from **Ndr**, and it is there that domain-specific logic can be
 * implemented. Additionally, node parsing and "discovery" are done via
 * plugins, again to keep **Ndr** generic and extendable. */
public enum Ndr
{}
