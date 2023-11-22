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
 *       Copyright (C) 2023 Wabi Foundation. All Rights Reserved.
 * --------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * -------------------------------------------------------------- */

@_exported import CxxStdlib

/* ---- Pixar.Base ---- */
@_exported import Arch
// @_exported import Tf
@_exported import Js
@_exported import Gf
// @_exported import Trace
@_exported import Vt
@_exported import Work
@_exported import Plug
/* ----- Pixar.Usd ---- */
@_exported import Ar
@_exported import Kind
/* ----- Pixar.NS ----- */
@_exported import pxr
/* -------------------- */

/**
  # ``Pixar``

  ## Overview

  **Pixar** is the **top level** namespace, analogous to the **pxr** namespace
  in c++. While you can use the **Pixar** namespace directly, it is recommended
  that you use the **Pixar** namespace as a **container** for these other Pixar
  modules, such as **Pixar.Tf** and **Pixar.Gf**, as these inner Pixar modules
  contain the swift wrappers for the c++ classes and functions, providing a more
  **swifty** interface to the underlying c++ code, which is far safer and more
  convenient to use than the c++ code directly. 
 */
public extension Pixar
{
  /**
    # ``Arch``

    ## Overview

    **Arch** is a repository for all **architecture-dependent code**.
    It's purpose is to isolate all platform dependencies into one small library,
    serving as a common area for documentation of these multi-platform issues.
   */
  struct Arch
  {}

  struct Js
  {}

  struct Tf
  {}

  struct Gf
  {}

  struct Trace
  {}

  struct Work
  {}

  struct Plug
  {}

  struct Vt
  {}

  struct Ar
  {}

  struct Kind
  {}

  struct Sdf
  {}

  struct Ndr
  {}

  struct Sdr
  {}

  struct Pcp
  {}

  struct Usd
  {}

  struct UsdGeom
  {}

  struct UsdVol
  {}

  struct UsdMedia
  {}

  struct UsdShade
  {}

  struct UsdLux
  {}

  struct UsdRender
  {}

  struct UsdHydra
  {}

  struct UsdRi
  {}

  struct UsdSkel
  {}

  struct UsdUI
  {}

  struct UsdUtils
  {}

  struct UsdPhysics
  {}

  struct UsdAbc
  {}

  struct UsdDraco
  {}

  struct Garch
  {}

  struct CameraUtil
  {}

  struct PxOsd
  {}

  struct Glf
  {}

  struct UsdImagingGL
  {}

  struct UsdAppUtils
  {}

  struct Usdview
  {}
}

/* --- xxx --- */
