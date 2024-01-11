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

import CxxStdlib
import pxr

public typealias Pixar_v23 = pxrInternal_v0_23__pxrReserved__

public enum Pixar
{
  /**
   * The current version of **SwiftUSD**.
   *
   * The semantic versioning used for **SwiftUSD** tracks both the upstream
   * Pixar USD version, as well as the evolution iteration of the **SwiftUSD**
   * SwiftPM package, which is setup as follows:
   * - ``PXR_MINOR_VERSION``.``PXR_PATCH_VERSION``.``SWIFTUSD_EVOLUTION``
   */
  public static let version = "\(PXR_MINOR_VERSION).\(PXR_PATCH_VERSION).\(SWIFTUSD_EVOLUTION)"

  /**
    # ``Arch``

    ## Overview

    **Arch** is a repository for all **architecture-dependent code**.
    It's purpose is to isolate all platform dependencies into one small library,
    serving as a common area for documentation of these multi-platform issues.
   */
  public struct Arch
  {}

  /**
     # ``Js``

     ## Overview

     **Js** is the **JSON I/O** library, it contains methods for parsing and
     writing JSON data from C++, and converting between arbitrary recursive
     container structures.
   */
  public struct Js
  {}

  /**
    # ``Tf``

    ## Overview

    **Tf** is the **tools foundations** library, it contains foundation
    classes and functions for all C/C++ software development.
   */
  public struct Tf
  {}

  /**
    # ``Gf``

    ## Overview

    **Gf** is the **graphics foundations** library, it contains foundation
    classes and functions for working with the basic mathematical aspects
    of computer graphics.
   */
  public struct Gf
  {}

  /**
    # ``Trace``

    ## Overview

    **Trace** is the **performance tracking** library, it contains utility classes
    for counting, timing, measuring, and recording events.
   */
  public struct Trace
  {}

  /**
    # ``Work``

    ## Overview

    **Work** is intended to simplify the use of *multithreading* in the context of
    our software ecosystem.
   */
  public struct Work
  {}

  /**
    # ``Plug``

    ## Overview

    **Plug** is the **plugin-in framework** implementation, the ``PlugPlugin`` class
    defines the interface to plug-in modules. The ``PlugRegistry`` class defines a
    mechanism for registering and looking up plug-in modules both automatically upon
    first use and manually at runtime by client calls to ``PlugRegistry.RegisterPlugins()``.
   */
  public struct Plug
  {}

  /**
    # ``Vt``

    ## Overview

    **Vt** is the **value types** library, it provides classes that represent
    basic value types such as arrays, strings, and tokens. This library operates
    on the level of language data types and there are differences in the C++ and
    Python APIs.
   */
  public struct Vt
  {}

  /**
    # ``Ar``

    ## Overview

    **Ar** is the **asset resolution** library, and is responsible for querying, reading, and
    writing asset data. It provides several interfaces that allow **USD** to access
    an asset without knowing how that asset is physically stored.
   */
  public struct Ar
  {}

  /**
    # ``Kind``

    ## Overview

    The **Kind** library provides a runtime-extensible taxonomy known as **"Kinds"**.
    **Kinds** are just **TfToken** symbols, but the ``KindRegistry`` allows for organizing
    kinds into taxonomies of related/refined concepts, and the ``KindRegistry.GetBaseKind()``
    and ``KindRegistry.IsA()`` queries enable reasoning about the hierarchy and classifying
    objects by kind.
   */
  public struct Kind
  {}

  /**
    # ``Sdf``

    ## Overview

    **Sdf** provides the foundations for serializing scene description to a reference text format,
    or a multitude of plugin-defined formats.  It also provides the primitive abstractions for
    interacting with scene description, such as ``SdfPath``, ``SdfLayer``, ``SdfPrimSpec``.
   */
  public struct Sdf
  {}

  public struct Ndr
  {}

  public struct Sdr
  {}

  public struct Pcp
  {}

  public struct Usd
  {}

  public struct UsdGeom
  {}

  public struct UsdVol
  {}

  public struct UsdMedia
  {}

  public struct UsdShade
  {}

  public struct UsdLux
  {}

  public struct UsdRender
  {}

  public struct UsdHydra
  {}

  public struct UsdRi
  {}

  public struct UsdSkel
  {}

  public struct UsdUI
  {}

  public struct UsdUtils
  {}

  public struct UsdPhysics
  {}

  public struct UsdAbc
  {}

  public struct UsdDraco
  {}

  public struct Garch
  {}

  public struct CameraUtil
  {}

  public struct PxOsd
  {}

  public struct Glf
  {}

  public struct UsdImagingGL
  {}

  public struct UsdAppUtils
  {}

  public struct Usdview
  {}
}

/* --- xxx --- */
