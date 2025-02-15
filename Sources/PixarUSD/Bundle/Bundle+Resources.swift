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
  static let pxrRoot = Bundle.main.resourcePath ?? ""

  #if os(macOS) || os(visionOS) || os(iOS) || os(tvOS) || os(watchOS)
    static let ext = ".bundle"
  #else
    static let ext = ".resources"
  #endif

  /**
   * Where ``Ar`` application bundle resources are located. */
  static let ar = Bundle(path: "\(pxrRoot)/SwiftUSD_Ar\(ext)")

  /**
   * Where ``Sdf`` application bundle resources are located. */
  static let sdf = Bundle(path: "\(pxrRoot)/SwiftUSD_Sdf\(ext)")

  /**
   * Where ``Usd`` application bundle resources are located. */
  static let usd = Bundle(path: "\(pxrRoot)/SwiftUSD_Usd\(ext)")

  /**
   * Where ``Ndr`` application bundle resources are located. */
  static let ndr = Bundle(path: "\(pxrRoot)/SwiftUSD_Ndr\(ext)")

  /**
   * Where ``UsdGeom`` application bundle resources are located. */
  static let usdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdGeom\(ext)")

  /**
   * Where ``UsdShade`` application bundle resources are located. */
  static let usdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShade\(ext)")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let usdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdShaders\(ext)")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let usdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdLux\(ext)")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let usdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdHydra\(ext)")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let sdrOsl = Bundle(path: "\(pxrRoot)/SwiftUSD_SdrOsl\(ext)")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let usdAbc = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdAbc\(ext)")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let usdDraco = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdDraco\(ext)")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let usdMedia = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdMedia\(ext)")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let usdMtlx = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdMtlx\(ext)")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let usdPhysics = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdPhysics\(ext)")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let usdProc = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdProc\(ext)")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let usdRender = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdRender\(ext)")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let usdRi = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdRi\(ext)")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let usdSkel = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdSkel\(ext)")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let usdUI = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdUI\(ext)")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let usdVol = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdVol\(ext)")

  /**
   * Where ``Hd`` application bundle resources are located. */
  static let hd = Bundle(path: "\(pxrRoot)/SwiftUSD_Hd\(ext)")

  /**
   * Where ``HgiMetal`` application bundle resources are located. */
  static let hgiMetal = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiMetal\(ext)")

  /**
   * Where ``HgiVulkan`` application bundle resources are located. */
  static let hgiVulkan = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiVulkan\(ext)")

  /**
   * Where ``HgiGL`` application bundle resources are located. */
  static let hgiGL = Bundle(path: "\(pxrRoot)/SwiftUSD_HgiGL\(ext)")

  /**
   * Where ``HdSt`` application bundle resources are located. */
  static let hdSt = Bundle(path: "\(pxrRoot)/SwiftUSD_HdSt\(ext)")

  /**
   * Where ``HdStorm`` application bundle resources are located. */
  static let hdStorm = Bundle(path: "\(pxrRoot)/SwiftUSD_HdStorm\(ext)")

  /**
   * Where ``Hdx`` application bundle resources are located. */
  static let hdx = Bundle(path: "\(pxrRoot)/SwiftUSD_Hdx\(ext)")

  /**
   * Where ``Hio`` application bundle resources are located. */
  static let hio = Bundle(path: "\(pxrRoot)/SwiftUSD_Hio\(ext)")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let glf = Bundle(path: "\(pxrRoot)/SwiftUSD_Glf\(ext)")

  /**
   * Where ``UsdImaging`` application bundle resources are located. */
  static let usdImaging = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdImaging\(ext)")

  /**
   * Where ``UsdImagingGL`` application bundle resources are located. */
  static let usdImagingGL = Bundle(path: "\(pxrRoot)/SwiftUSD_UsdImagingGL\(ext)")

  /**
   * Where ``Tf`` python bundle resources are located. */
  static let pyTf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTf\(ext)")

  /**
   * Where ``Plug`` python bundle resources are located. */
  static let pyPlug = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPlug\(ext)")

  /**
   * Where ``Trace`` python bundle resources are located. */
  static let pyTrace = Bundle(path: "\(pxrRoot)/SwiftUSD_PyTrace\(ext)")

  /**
   * Where ``Work`` python bundle resources are located. */
  static let pyWork = Bundle(path: "\(pxrRoot)/SwiftUSD_PyWork\(ext)")

  /**
   * Where ``Gf`` python bundle resources are located. */
  static let pyGf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGf\(ext)")

  /**
   * Where ``Vt`` python bundle resources are located. */
  static let pyVt = Bundle(path: "\(pxrRoot)/SwiftUSD_PyVt\(ext)")

  /**
   * Where ``Ar`` python bundle resources are located. */
  static let pyAr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyAr\(ext)")

  /**
   * Where ``Kind`` python bundle resources are located. */
  static let pyKind = Bundle(path: "\(pxrRoot)/SwiftUSD_PyKind\(ext)")

  /**
   * Where ``Sdf`` python bundle resources are located. */
  static let pySdf = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdf\(ext)")

  /**
   * Where ``Pcp`` python bundle resources are located. */
  static let pyPcp = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPcp\(ext)")

  /**
   * Where ``Usd`` python bundle resources are located. */
  static let pyUsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsd\(ext)")

  /**
   * Where ``Ndr`` python bundle resources are located. */
  static let pyNdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PyNdr\(ext)")

  /**
   * Where ``Sdr`` python bundle resources are located. */
  static let pySdr = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdr\(ext)")

  /**
   * Where ``SdrOsl`` application bundle resources are located. */
  static let pySdrOsl = Bundle(path: "\(pxrRoot)/SwiftUSD_PySdrOsl\(ext)")

  /**
   * Where ``UsdGeom`` python bundle resources are located. */
  static let pyUsdGeom = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdGeom\(ext)")

  /**
   * Where ``UsdShade`` python bundle resources are located. */
  static let pyUsdShade = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShade\(ext)")

  /**
   * Where ``UsdShaders`` application bundle resources are located. */
  static let pyUsdShaders = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdShaders\(ext)")

  /**
   * Where ``UsdLux`` application bundle resources are located. */
  static let pyUsdLux = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdLux\(ext)")

  /**
   * Where ``UsdAbc`` application bundle resources are located. */
  static let pyUsdAbc = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdAbc\(ext)")

  /**
   * Where ``UsdDraco`` application bundle resources are located. */
  static let pyUsdDraco = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdDraco\(ext)")

  /**
   * Where ``UsdMedia`` application bundle resources are located. */
  static let pyUsdMedia = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdMedia\(ext)")

  /**
   * Where ``UsdMtlx`` application bundle resources are located. */
  static let pyUsdMtlx = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdMtlx\(ext)")

  /**
   * Where ``UsdPhysics`` application bundle resources are located. */
  static let pyUsdPhysics = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdPhysics\(ext)")

  /**
   * Where ``UsdProc`` application bundle resources are located. */
  static let pyUsdProc = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdProc\(ext)")

  /**
   * Where ``UsdRender`` application bundle resources are located. */
  static let pyUsdRender = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdRender\(ext)")

  /**
   * Where ``UsdRi`` application bundle resources are located. */
  static let pyUsdRi = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdRi\(ext)")

  /**
   * Where ``UsdSkel`` application bundle resources are located. */
  static let pyUsdSkel = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdSkel\(ext)")

  /**
   * Where ``UsdUI`` application bundle resources are located. */
  static let pyUsdUI = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdUI\(ext)")

  /**
   * Where ``UsdUtils`` application bundle resources are located. */
  static let pyUsdUtils = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdUtils\(ext)")

  /**
   * Where ``UsdVol`` application bundle resources are located. */
  static let pyUsdVol = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdVol\(ext)")

  /**
   * Where ``UsdHydra`` application bundle resources are located. */
  static let pyUsdHydra = Bundle(path: "\(pxrRoot)/SwiftUSD_PyUsdHydra\(ext)")

  /**
   * Where ``CameraUtil`` application bundle resources are located. */
  static let pyCameraUtil = Bundle(path: "\(pxrRoot)/SwiftUSD_PyCameraUtil\(ext)")

  /**
   * Where ``PxOsd`` application bundle resources are located. */
  static let pyPxOsd = Bundle(path: "\(pxrRoot)/SwiftUSD_PyPxOsd\(ext)")

  /**
   * Where ``Garch`` application bundle resources are located. */
  static let pyGarch = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGarch\(ext)")

  /**
   * Where ``Glf`` application bundle resources are located. */
  static let pyGlf = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGlf\(ext)")

  /**
   * Where ``GeomUtil`` application bundle resources are located. */
  static let pyGeomUtil = Bundle(path: "\(pxrRoot)/SwiftUSD_PyGeomUtil\(ext)")
}
