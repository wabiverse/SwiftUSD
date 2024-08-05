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

import Kind

/**
 * # ``Kind``
 *
 * **Extensible Categorization**
 *
 * ## Overview
 *
 * The **Kind** library provides a runtime-extensible taxonomy known as **"Kinds"**.
 * **Kinds** are just **TfToken** symbols, but the ``Kind/KindRegistry`` allows for organizing
 * kinds into taxonomies of related/refined concepts, and the ``Kind/KindRegistry.GetBaseKind()``
 * and ``Kind/KindRegistry.is(a:)`` queries enable reasoning about the hierarchy and classifying
 * objects by kind. */
public enum Kind
{}
