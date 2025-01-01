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

class FreeCamera
{
  var position: Pixar.GfVec3d
  var front: Pixar.GfVec3d
  var up: Pixar.GfVec3d
  var right: Pixar.GfVec3d
  var worldUp: Pixar.GfVec3d
  var yaw: Double
  var pitch: Double
  var speed: Double
  var sensitivity: Double
  var zoom: Double

  init(position: Pixar.GfVec3d = Pixar.GfVec3d(0, 0, 10), yaw: Double = -90.0, pitch: Double = 0.0)
  {
    self.position = position
    front = Pixar.GfVec3d(0, 0, -1)
    up = Pixar.GfVec3d(0, 1, 0)
    right = Pixar.GfVec3d(1, 0, 0)
    worldUp = up
    self.yaw = yaw
    self.pitch = pitch
    speed = 2.5
    sensitivity = 0.1
    zoom = 45.0
    updateCameraVectors()
  }

  func updateCameraVectors()
  {
    // calculate the front vector based on yaw and pitch.
    let frontX = cos(Gf.degreesToRadians(angle: yaw)) * cos(Gf.degreesToRadians(angle: pitch))
    let frontY = sin(Gf.degreesToRadians(angle: pitch))
    let frontZ = sin(Gf.degreesToRadians(angle: yaw)) * cos(Gf.degreesToRadians(angle: pitch))

    front = Pixar.GfVec3d(frontX, frontY, frontZ).getNormalized()

    // recalculate right and up vector.
    right = Gf.cross(front, worldUp).getNormalized()
    up = Gf.cross(right, front).getNormalized()
  }

  func processKeyboardInput(forward: Bool, rightward: Bool, upward: Bool)
  {
    let velocity = speed

    if forward
    {
      position += front * velocity
    }
    if rightward
    {
      position += right * velocity
    }
    if upward
    {
      position += up * velocity
    }
  }

  func processMouseMovement(offsetX: Double, offsetY: Double)
  {
    yaw += offsetX * sensitivity
    pitch -= offsetY * sensitivity

    if pitch > 89.0
    {
      pitch = 89.0
    }
    if pitch < -89.0
    {
      pitch = -89.0
    }

    updateCameraVectors()
  }

  func getViewMatrix() -> Gf.Matrix4d
  {
    // compute the z-axis of the camera (view direction).
    let zAxis = (self.position - (self.position + self.front)).getNormalized()
    
    // compute the x-axis (right vector), the cross product of the up vector and z-axis.
    let xAxis = Gf.cross(up, zAxis).getNormalized()
    
    // compute the y-axis (up vector) as the cross product of z-axis and x-axis.
    let yAxis = Gf.cross(zAxis, xAxis)
    
    // construct the rotation matrix.
    var rotation = Gf.Matrix4d(1.0)
    rotation[0] = Gf.Vec4d(xAxis[0], yAxis[0], zAxis[0], 0)
    rotation[1] = Gf.Vec4d(xAxis[1], yAxis[1], zAxis[1], 0)
    rotation[2] = Gf.Vec4d(xAxis[2], yAxis[2], zAxis[2], 0)
    rotation[3] = Gf.Vec4d(0, 0, 0, 1)

    rotation.SetTranslate(Gf.Vec3d(-self.position[0], -self.position[1], -self.position[2]))

    return rotation
  }

  func getProjectionMatrix(aspectRatio: Double) -> Gf.Matrix4d
  {
    let fov = Gf.degreesToRadians(angle: self.zoom)
    let nearClip = 0.1
    let farClip = 1000.0
    let tanHalfFov = tan(fov / 2.0)

    var matrix = Gf.Matrix4d()
    matrix[0][0] = 1.0 / (aspectRatio * tanHalfFov)
    matrix[1][1] = 1.0 / tanHalfFov
    matrix[2][2] = -(farClip + nearClip) / (farClip - nearClip)
    matrix[2][3] = -1.0
    matrix[3][2] = -(2 * farClip * nearClip) / (farClip - nearClip)

    return matrix
  }
}
