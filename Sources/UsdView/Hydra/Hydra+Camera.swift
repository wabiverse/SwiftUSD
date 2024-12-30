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
import PixarUSD

public extension Hydra
{
  class Camera
  {
    private let isZUp: Bool
    public var params = Params()

    public struct Params
    {
      public var rotation = Pixar.GfVec3d(0.0)
      public var focus = Pixar.GfVec3d(0.0)
      public var distance = 50.0
      public var focalLength = 0.0
      public var projection = Pixar.GfCamera.Projection(0)
      public var leftBottomNear = Pixar.GfVec3d()
      public var rightTopFar = Pixar.GfVec3d()
      public var scaleViewport = 1.0
    }

    public var position = Pixar.GfVec3d()
    public var standardFocalLength = Double()
    public var scaleBias = Double()

    public init(isZUp: Bool)
    {
      self.isZUp = isZUp
      params.rotation = Pixar.GfVec3d(0.0)
      params.focus = Pixar.GfVec3d(0.0)
      params.distance = 50.0
      params.scaleViewport = 1.0
    }

    public func getTransform() -> GfMatrix4d
    {
      let gfRotation = getRotation()
      var cameraTransform = GfMatrix4d(1.0)

      var gfMatrix = GfMatrix4d()

      cameraTransform =
        gfMatrix.SetTranslate(Pixar.GfVec3d(0.0, 0.0, params.distance)).pointee *
        gfMatrix.SetRotate(gfRotation).pointee *
        gfMatrix.SetTranslate(params.focus).pointee

      return cameraTransform
    }

    public func getRotation() -> Pixar.GfRotation
    {
      var gfRotation = Pixar.GfRotation(Pixar.GfVec3d.ZAxis(), params.rotation[2]) *
        Pixar.GfRotation(Pixar.GfVec3d.XAxis(), params.rotation[0]) *
        Pixar.GfRotation(Pixar.GfVec3d.YAxis(), params.rotation[1])

      if isZUp
      {
        gfRotation = gfRotation * Pixar.GfRotation(Pixar.GfVec3d.XAxis(), 90.0)
      }

      return gfRotation
    }

    public func getShaderParams() -> Params
    {
      return params
    }
  }
}
