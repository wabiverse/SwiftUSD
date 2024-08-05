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

import Ptex
import pxr

public var PIXAR_MAJOR_VERSION: Int32
{
  PXR_MAJOR_VERSION
}

public var PIXAR_MINOR_VERSION: Int32
{
  PXR_MINOR_VERSION
}

public var PIXAR_PATCH_VERSION: Int32
{
  PXR_PATCH_VERSION
}

public var PIXAR_VERSION: Int32
{
  PXR_VERSION
}

public var PIXAR_USE_NAMESPACES: Int32
{
  PXR_USE_NAMESPACES
}

public var RUSTUSD_EVOLUTION: Int32
{
  SWIFTUSD_EVOLUTION
}

public var PIXAR_PYTHON_SUPPORT_ENABLED: Int32
{
  PXR_PYTHON_SUPPORT_ENABLED
}

public var PIXAR_PREFER_SAFETY_OVER_SPEED: Int32
{
  PXR_PREFER_SAFETY_OVER_SPEED
}

func Ptex_MeshType(value: UInt32) -> UInt32
{
  print("In swift... calling Ptex.MeshType(rawValue: \(value)).")

  var swiftString = "unknown"

  let meshType = Ptex.v2_4.MeshType(rawValue: value)
  defer { print("The mesh type is: \(swiftString).") }
  switch meshType
  {
    case Ptex.v2_4.mt_triangle:
      swiftString = "triangle"
    case Ptex.v2_4.mt_quad:
      swiftString = "quad"
    default:
      swiftString = "unknown"
  }

  return meshType.rawValue
}
