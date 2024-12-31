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

import Gf

/* note: the typealiases are documented the same way twice,
 * keep it like this so that sourcekit shows documentation
 * regardless of which typealias a user might use in their
 * code. */

/**
 * # GfFrustum
 *
 * Basic type for a view frustum.
 *
 * This class represents a viewing frustum in three dimensional eye space. It
 * may represent either a parallel (orthographic) or perspective projection.
 * One can think of the frustum as being defined by 6 boundary planes.
 *
 * The frustum is specified using these parameters:
 *  - The **position** of the viewpoint.
 *  - The **rotation** applied to the default view frame, which is
 *    looking along the -z axis with the +y axis as the "up"
 *    direction.
 *  - The 2D **window** on the reference plane that defines the left,
 *    right, top, and bottom planes of the viewing frustum, as
 *    described below.
 *  - The distances to the **near** and **far** planes.
 *  - The **projection type**
 *  - The view distance.
 *
 * The window and near/far parameters combine to define the view frustum as
 * follows. Transform the -z axis and the +y axis by the frustum rotation to
 * get the world-space **view direction** and **up direction**. Now consider
 * the **reference plane** that is perpendicular to the view direction, a
 * distance of referencePlaneDepth from the viewpoint, and whose y axis
 * corresponds to the up direction. The window rectangle is specified in a 2D
 * coordinate system embedded in this plane. The origin of the coordinate system
 * is the point at which the view direction vector intersects the plane. Therefore,
 * the point (0,1) in this plane is found by moving 1 unit along the up direction
 * vector in this plane. The vector from the viewpoint to the resulting point will
 * form a 45-degree angle with the view direction.
 *
 * The view distance is only useful for interactive applications. It can be
 * used to compute a look at point which is useful when rotating around an
 * object of interest.
 */
public typealias GfFrustum = Pixar.GfFrustum

public extension Gf
{
  /**
   * # GfFrustum
   *
   * Basic type for a view frustum.
   *
   * This class represents a viewing frustum in three dimensional eye space. It
   * may represent either a parallel (orthographic) or perspective projection.
   * One can think of the frustum as being defined by 6 boundary planes.
   *
   * The frustum is specified using these parameters:
   *  - The **position** of the viewpoint.
   *  - The **rotation** applied to the default view frame, which is
   *    looking along the -z axis with the +y axis as the "up"
   *    direction.
   *  - The 2D **window** on the reference plane that defines the left,
   *    right, top, and bottom planes of the viewing frustum, as
   *    described below.
   *  - The distances to the **near** and **far** planes.
   *  - The **projection type**
   *  - The view distance.
   *
   * The window and near/far parameters combine to define the view frustum as
   * follows. Transform the -z axis and the +y axis by the frustum rotation to
   * get the world-space **view direction** and **up direction**. Now consider
   * the **reference plane** that is perpendicular to the view direction, a
   * distance of referencePlaneDepth from the viewpoint, and whose y axis
   * corresponds to the up direction. The window rectangle is specified in a 2D
   * coordinate system embedded in this plane. The origin of the coordinate system
   * is the point at which the view direction vector intersects the plane. Therefore,
   * the point (0,1) in this plane is found by moving 1 unit along the up direction
   * vector in this plane. The vector from the viewpoint to the resulting point will
   * form a 45-degree angle with the view direction.
   *
   * The view distance is only useful for interactive applications. It can be
   * used to compute a look at point which is useful when rotating around an
   * object of interest.
   */
  typealias Frustum = GfFrustum
}

public extension Gf.Frustum
{
  /// This constructor creates an instance with
  /// the given viewing parameters.
  init(position: Gf.Vec3d,
       rotation: Pixar.GfRotation,
       window: Pixar.GfRange2d,
       nearFar: Pixar.GfRange1d,
       projection type: ProjectionType,
       viewDistance: Double = 5.0)
  {
    self = Gf.Frustum(
      position,
      rotation,
      window,
      nearFar,
      type,
      viewDistance
    )
  }

  /// This constructor creates an instance from
  /// a camera matrix (always of a y-Up camera,
  /// also see SetPositionAndRotationFromMatrix)
  /// and the given viewing parameters.
  init(camera matrix: Gf.Matrix4d,
       window: Pixar.GfRange2d,
       nearFar: Pixar.GfRange1d,
       projection type: ProjectionType,
       viewDistance: Double = 5.0)
  {
    self = Gf.Frustum(
      matrix,
      window,
      nearFar,
      type,
      viewDistance
    )
  }

  /// Sets the position of the frustum in world space.
  mutating func setPosition(_ position: Gf.Vec3d)
  {
    SetPosition(position)
  }

  private borrowing func getPositionCopy() -> Gf.Vec3d
  {
    __GetPositionUnsafe().pointee
  }

  /// Returns the position of the frustum in world space.
  func getPosition() -> Gf.Vec3d
  {
    getPositionCopy()
  }

  /// Sets the orientation of the frustum in world space as
  /// a rotation to apply to the default frame: looking along
  /// the -z axis with the +y axis as "up".
  mutating func setRotation(_ rotation: Pixar.GfRotation)
  {
    SetRotation(rotation)
  }

  private borrowing func getRotationCopy() -> Pixar.GfRotation
  {
    __GetRotationUnsafe().pointee
  }

  /// Returns the orientation of the frustum in world space
  /// as a rotation to apply to the -z axis.
  func getRotation() -> Pixar.GfRotation
  {
    getRotationCopy()
  }

  /// Sets the position and rotation of the frustum from a camera matrix
  /// (always from a y-Up camera). The resulting frustum's transform will
  /// always represent a right-handed and orthonormal coordinate sytem
  /// (scale, shear, and projection are removed from the given `matrix`).
  mutating func setPositionAndRotation(from matrix: Gf.Matrix4d)
  {
    SetPositionAndRotationFromMatrix(matrix)
  }

  /// Sets the window rectangle in the reference plane that
  /// defines the left, right, top, and bottom planes of the
  /// frustum.
  mutating func setWindow(_ window: Pixar.GfRange2d)
  {
    SetWindow(window)
  }

  private borrowing func getWindowCopy() -> Pixar.GfRange2d
  {
    __GetWindowUnsafe().pointee
  }

  /// Returns the window rectangle in the reference plane.
  func getWindow() -> Pixar.GfRange2d
  {
    getWindowCopy()
  }

  /// Returns the depth of the reference plane.
  static func getReferencePlaneDepth() -> Double
  {
    GetReferencePlaneDepth()
  }

  /// Sets the near/far interval.
  mutating func setNearFar(_ nearFar: Pixar.GfRange1d)
  {
    SetNearFar(nearFar)
  }

  private borrowing func getNearFarCopy() -> Pixar.GfRange1d
  {
    __GetNearFarUnsafe().pointee
  }

  /// Returns the near/far interval.
  func getNearFar() -> Pixar.GfRange1d
  {
    getNearFarCopy()
  }

  /// Sets the view distance.
  mutating func setViewDistance(_ viewDistance: Double)
  {
    SetViewDistance(viewDistance)
  }

  /// Returns the view distance.
  func getViewDistance() -> Double
  {
    GetViewDistance()
  }

  /// Sets the projection type.
  mutating func setProjectionType(_ projectionType: ProjectionType)
  {
    SetProjectionType(projectionType)
  }

  /// Returns the projection type.
  func getProjectionType() -> ProjectionType
  {
    GetProjectionType()
  }

  func computeViewMatrix() -> Gf.Matrix4d
  {
    ComputeViewMatrix()
  }

  func computeProjectionMatrix() -> Gf.Matrix4d
  {
    ComputeProjectionMatrix()
  }
}
