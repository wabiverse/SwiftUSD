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

#if WITH_METAL
  import Apple
  import CosmoGraph
  import HgiMetal

  /**
   * Represents the Metal graphics API
   * for use with ``Hgi``. */
  public enum HgiMetal: HgiRepresentable
  {
    /**
     * Represents the platform for the
     * respective graphics API, which
     * is the Metal graphics API here. */
    public typealias Platform = pxr.HgiMetal

    /**
     * Creates a new Metal graphics API object.
     *
     * - Returns: The newly created Metal graphics interface. */
    public static func createHgi() -> Platform.Ptr
    {
      pxr.HgiMetal.CreateHgi(nil)
    }

    /**
     * Creates a new Metal graphics API object.
     *
     * - Parameter device: A Metal GPU device.
     *
     * - Returns: The newly created Metal graphics interface. */
    public static func createHgi(device: inout MTL.Device?) -> Platform.Ptr
    {
      pxr.HgiMetal.CreateHgi(device)
    }

    /**
     * Creates a new Metal graphics API object.
     *
     * - Parameter device: A raw pointer to the Metal GPU device.
     *
     * - Returns: The newly created Metal graphics interface. */
    public static func createHgi(device: inout UnsafeMutableRawPointer?) -> Platform.Ptr
    {
      let opaque = OpaquePointer(device)
      let devicePtr = UnsafeMutablePointer<MTL.Device>(opaque)

      var mtlDevice: MTL.Device? = devicePtr.pointee

      return HgiMetal.createHgi(device: &mtlDevice)
    }
  }

  /** --------------------------------------------
   * Conform HgiMetal to the HgiPlatform protocol. */
  extension pxr.HgiMetal: HgiPlatform
  {
    /**
     * The shared pointer to the Metal graphics
     * API object. Swift does not yet support the
     * usage of `std.unique_ptr`. */
    public typealias Ptr = pxr.HgiMetalPtr
  }
#endif /* WITH_METAL */
