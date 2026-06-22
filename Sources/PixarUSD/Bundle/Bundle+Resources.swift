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

import Foundation

public extension Bundle
{
  /**
   * Resolves plugin resource paths for both bundled and unbundled app contexts,
   * handling both '.bundle' and '.resources' extensions, and the Contents/Resources
   * nesting inside app bundles. */
  static func pxrBundle(_ name: String) -> Bundle?
  {
    let pxrRoot = Bundle.main.resourcePath ?? ""
    let base = ["\(pxrRoot)/\(name).bundle", "\(pxrRoot)/\(name).resources"]
      .first { FileManager.default.fileExists(atPath: $0) }
    guard let base else { return nil }

    return Bundle(path: "\(base)/Contents/Resources") ?? Bundle(path: base)
  }

  /**
   * Where ``Ar`` application bundle resources are located. */
  static let ar = pxrBundle("SwiftUSD_Ar")

  /**
   * Where ``Sdf`` application bundle resources are located. */
  static let sdf = pxrBundle("SwiftUSD_Sdf")

  /**
   * Where ``Usd`` application bundle resources are located. */
  static let usd = pxrBundle("SwiftUSD_Usd")

  /**
   * Where ``Ndr`` application bundle resources are located. */
  static let ndr = pxrBundle("SwiftUSD_Ndr")

  /**
   * Where ``UsdGeom`` application bundle resources are located. */
  static let usdGeom = pxrBundle("SwiftUSD_UsdGeom")

  /**
   * Where ``UsdShade`` application bundle resources are located. */
  static let usdShade = pxrBundle("SwiftUSD_UsdShade")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let usdShaders = pxrBundle("SwiftUSD_UsdShaders")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let usdLux = pxrBundle("SwiftUSD_UsdLux")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let usdHydra = pxrBundle("SwiftUSD_UsdHydra")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let sdrOsl = pxrBundle("SwiftUSD_SdrOsl")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let usdAbc = pxrBundle("SwiftUSD_UsdAbc")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let usdDraco = pxrBundle("SwiftUSD_UsdDraco")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let usdMedia = pxrBundle("SwiftUSD_UsdMedia")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let usdMtlx = pxrBundle("SwiftUSD_UsdMtlx")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let usdPhysics = pxrBundle("SwiftUSD_UsdPhysics")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let usdProc = pxrBundle("SwiftUSD_UsdProc")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let usdRender = pxrBundle("SwiftUSD_UsdRender")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let usdRi = pxrBundle("SwiftUSD_UsdRi")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let usdSkel = pxrBundle("SwiftUSD_UsdSkel")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let usdUI = pxrBundle("SwiftUSD_UsdUI")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let usdVol = pxrBundle("SwiftUSD_UsdVol")

  /**
   * Where ``Hd`` application bundle resources are located. */
  static let hd = pxrBundle("SwiftUSD_Hd")

  /**
   * Where ``HgiMetal`` application bundle resources are located. */
  static let hgiMetal = pxrBundle("SwiftUSD_HgiMetal")

  /**
   * Where ``HgiVulkan`` application bundle resources are located. */
  static let hgiVulkan = pxrBundle("SwiftUSD_HgiVulkan")

  /**
   * Where ``HgiGL`` application bundle resources are located. */
  static let hgiGL = pxrBundle("SwiftUSD_HgiGL")

  /**
   * Where ``HdSt`` application bundle resources are located. */
  static let hdSt = pxrBundle("SwiftUSD_HdSt")

  /**
   * Where ``HdStorm`` application bundle resources are located. */
  static let hdStorm = pxrBundle("SwiftUSD_HdStorm")

  /**
   * Where ``Hdx`` application bundle resources are located. */
  static let hdx = pxrBundle("SwiftUSD_Hdx")

  /**
   * Where ``Hio`` application bundle resources are located. */
  static let hio = pxrBundle("SwiftUSD_Hio")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let glf = pxrBundle("SwiftUSD_Glf")

  /**
   * Where ``UsdImaging`` application bundle resources are located. */
  static let usdImaging = pxrBundle("SwiftUSD_UsdImaging")

  /**
   * Where ``UsdImagingGL`` application bundle resources are located. */
  static let usdImagingGL = pxrBundle("SwiftUSD_UsdImagingGL")

  /**
   * Where ``Tf`` python bundle resources are located. */
  static let pyTf = pxrBundle("SwiftUSD_PyTf")

  /**
   * Where ``Plug`` python bundle resources are located. */
  static let pyPlug = pxrBundle("SwiftUSD_PyPlug")

  /**
   * Where ``Trace`` python bundle resources are located. */
  static let pyTrace = pxrBundle("SwiftUSD_PyTrace")

  /**
   * Where ``Work`` python bundle resources are located. */
  static let pyWork = pxrBundle("SwiftUSD_PyWork")

  /**
   * Where ``Gf`` python bundle resources are located. */
  static let pyGf = pxrBundle("SwiftUSD_PyGf")

  /**
   * Where ``Vt`` python bundle resources are located. */
  static let pyVt = pxrBundle("SwiftUSD_PyVt")

  /**
   * Where ``Ar`` python bundle resources are located. */
  static let pyAr = pxrBundle("SwiftUSD_PyAr")

  /**
   * Where ``Kind`` python bundle resources are located. */
  static let pyKind = pxrBundle("SwiftUSD_PyKind")

  /**
   * Where ``Sdf`` python bundle resources are located. */
  static let pySdf = pxrBundle("SwiftUSD_PySdf")

  /**
   * Where ``Pcp`` python bundle resources are located. */
  static let pyPcp = pxrBundle("SwiftUSD_PyPcp")

  /**
   * Where ``Usd`` python bundle resources are located. */
  static let pyUsd = pxrBundle("SwiftUSD_PyUsd")

  /**
   * Where ``Ndr`` python bundle resources are located. */
  static let pyNdr = pxrBundle("SwiftUSD_PyNdr")

  /**
   * Where ``Sdr`` python bundle resources are located. */
  static let pySdr = pxrBundle("SwiftUSD_PySdr")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let pySdrOsl = pxrBundle("SwiftUSD_PySdrOsl")

  /**
   * Where ``UsdGeom`` python bundle resources are located. */
  static let pyUsdGeom = pxrBundle("SwiftUSD_PyUsdGeom")

  /**
   * Where ``UsdShade`` python bundle resources are located. */
  static let pyUsdShade = pxrBundle("SwiftUSD_PyUsdShade")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let pyUsdShaders = pxrBundle("SwiftUSD_PyUsdShaders")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let pyUsdLux = pxrBundle("SwiftUSD_PyUsdLux")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let pyUsdAbc = pxrBundle("SwiftUSD_PyUsdAbc")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let pyUsdDraco = pxrBundle("SwiftUSD_PyUsdDraco")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let pyUsdMedia = pxrBundle("SwiftUSD_PyUsdMedia")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let pyUsdMtlx = pxrBundle("SwiftUSD_PyUsdMtlx")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let pyUsdPhysics = pxrBundle("SwiftUSD_PyUsdPhysics")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let pyUsdProc = pxrBundle("SwiftUSD_PyUsdProc")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let pyUsdRender = pxrBundle("SwiftUSD_PyUsdRender")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let pyUsdRi = pxrBundle("SwiftUSD_PyUsdRi")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let pyUsdSkel = pxrBundle("SwiftUSD_PyUsdSkel")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let pyUsdUI = pxrBundle("SwiftUSD_PyUsdUI")

  /**
   * Where ``UsdUtils`` application bundle resources are located. */
  static let pyUsdUtils = pxrBundle("SwiftUSD_PyUsdUtils")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let pyUsdVol = pxrBundle("SwiftUSD_PyUsdVol")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let pyUsdHydra = pxrBundle("SwiftUSD_PyUsdHydra")

  /**
   * Where ``CameraUtil`` application bundle resources are located. */
  static let pyCameraUtil = pxrBundle("SwiftUSD_PyCameraUtil")

  /**
   * Where ``PxOsd`` application bundle resources are located. */
  static let pyPxOsd = pxrBundle("SwiftUSD_PyPxOsd")

  /**
   * Where ``Garch`` application bundle resources are located. */
  static let pyGarch = pxrBundle("SwiftUSD_PyGarch")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let pyGlf = pxrBundle("SwiftUSD_PyGlf")

  /**
   * Where ``GeomUtil`` application bundle resources are located. */
  static let pyGeomUtil = pxrBundle("SwiftUSD_PyGeomUtil")
}
