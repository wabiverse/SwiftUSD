//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "CameraUtil/conformWindow.h"

#include "Gf/camera.h"
#include "Gf/frustum.h"
#include "Gf/matrix4d.h"
#include "Gf/range2d.h"
#include "Gf/vec2d.h"
#include "Gf/vec4d.h"

#include "Tf/enum.h"
#include "Tf/registryManager.h"

PXR_NAMESPACE_OPEN_SCOPE

// Overview of ConformWindowPolicy:
//
//                 Original window:
//
//                        w
//                 |<----------->|
//
//                 ***************  ---
//                 *   O     o   *   A
//                 * --|-- --|-- *   | h
//                 *   |     |   *   |
//                 *  / \   / \  *   V
//                 ***************  ---
//
//
//
// The result of applying the given ConformWindowPolicy when
//
//     target aspect                target aspect
//           >                            <
//    original aspect              original aspect
//
//
//                 Match Vertically:
//
//
//  ******************* ---           ********* ---
//  *     O     o     *  A            *O     O*  A
//  *   --|-- --|--   *  | h          *|-- --|*  | h
//  *     |     |     *  |            *|     |*  |
//  *    / \   / \    *  V            * \   / *  V
//  ******************* ---           ********* ---
//
//                Match Horizontally:
//                                        w
//                                 |<----------->|
//           w
//    |<----------->|              ***************
//                                 *             *
//    ***************              *   O     O   *
//    * --|-- --|-- *              * --|-- --|-- *
//    *   |     |   *              *   |     |   *
//    ***************              *  / \   / \  *
//                                 *             *
//                                 ***************
//
//                       Fit:
//
//                                       w
//                                 |<----------->|
//
//                                 ***************
//  ******************* ---        *             *
//  *     O     o     *  A         *   O     O   *
//  *   --|-- --|--   *  | h       * --|-- --|-- *
//  *     |     |     *  |         *   |     |   *
//  *    / \   / \    *  V         *  / \   / \  *
//  ******************* ---        *             *
//                                 ***************
//
//                      Crop:
//
//           w
//    |<----------->|
//                                    ********* ---
//    ***************                 *O     O*  A
//    * --|-- --|-- *                 *|-- --|*  | h
//    *   |     |   *                 *|     |*  |
//    ***************                 * \   / *  V
//                                    ********* ---

TF_REGISTRY_FUNCTION(TfEnum)
{
  TF_ADD_ENUM_NAME(CameraUtilMatchVertically, "MatchVertically");
  TF_ADD_ENUM_NAME(CameraUtilMatchHorizontally, "MatchHotizontally");
  TF_ADD_ENUM_NAME(CameraUtilFit, "Fit");
  TF_ADD_ENUM_NAME(CameraUtilCrop, "Crop");
  TF_ADD_ENUM_NAME(CameraUtilDontConform, "DontConform");
}

static double _SafeDivOne(const double a, const double b)
{
  if (b != 0.0) {
    return a / b;
  }

  return 1.0;
}

static double _SafeDiv(const double a, const double b)
{
  if (b != 0.0) {
    return a / b;
  }

  return a;
}

static CameraUtilConformWindowPolicy _ResolveConformWindowPolicy(
    const GfVec2d &size, CameraUtilConformWindowPolicy policy, double targetAspect)
{
  if ((policy == CameraUtilMatchVertically) || (policy == CameraUtilMatchHorizontally)) {
    return policy;
  }

  const double aspect = _SafeDivOne(size[0], size[1]);

  if ((policy == CameraUtilFit) ^ (aspect > targetAspect)) {
    return CameraUtilMatchVertically;
  }
  return CameraUtilMatchHorizontally;
}

static bool _DoesNotRequireAdjustment(CameraUtilConformWindowPolicy policy)
{
  return (policy == CameraUtilDontConform);
}

GfVec2d CameraUtilConformedWindow(const GfVec2d &window,
                                  CameraUtilConformWindowPolicy policy,
                                  double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return window;
  }

  const CameraUtilConformWindowPolicy resolvedPolicy = _ResolveConformWindowPolicy(
      window, policy, targetAspect);

  if (resolvedPolicy == CameraUtilMatchHorizontally) {
    return GfVec2d(window[0], _SafeDiv(window[0], targetAspect));
  }
  else {
    return GfVec2d(window[1] * targetAspect, window[1]);
  }
}

GfRange2d CameraUtilConformedWindow(const GfRange2d &window,
                                    CameraUtilConformWindowPolicy policy,
                                    double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return window;
  }

  const GfVec2d &size = window.GetSize();
  const GfVec2d center = (window.GetMin() + window.GetMax()) / 2.0;

  const CameraUtilConformWindowPolicy resolvedPolicy = _ResolveConformWindowPolicy(
      size, policy, targetAspect);

  if (resolvedPolicy == CameraUtilMatchHorizontally) {
    const double height = _SafeDiv(size[0], targetAspect);

    return GfRange2d(GfVec2d(window.GetMin()[0], center[1] - height / 2.0),
                     GfVec2d(window.GetMax()[0], center[1] + height / 2.0));
  }
  else {
    const double width = size[1] * targetAspect;

    return GfRange2d(GfVec2d(center[0] - width / 2.0, window.GetMin()[1]),
                     GfVec2d(center[0] + width / 2.0, window.GetMax()[1]));
  }
}

GfVec4d CameraUtilConformedWindow(const GfVec4d &window,
                                  CameraUtilConformWindowPolicy policy,
                                  double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return window;
  }

  const GfRange2d original(GfVec2d(window[0], window[2]), GfVec2d(window[1], window[3]));

  const GfRange2d conformed = CameraUtilConformedWindow(original, policy, targetAspect);

  return GfVec4d(
      conformed.GetMin()[0], conformed.GetMax()[0], conformed.GetMin()[1], conformed.GetMax()[1]);
}

static double _Sign(const double x)
{
  if (x < 0.0) {
    return -1.0;
  }

  return 1.0;
}

GfMatrix4d CameraUtilConformedWindow(const GfMatrix4d &projectionMatrix,
                                     CameraUtilConformWindowPolicy policy,
                                     double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return projectionMatrix;
  }

  GfMatrix4d result(projectionMatrix);

  // The aspect ratio of the frustum corresponding to the given
  // projectionMatrix (assume is square pixels) is given by the ratio of
  // the two top diaognal entries.
  // Note: usually the aspect ratio is given by width / height, so one might
  // expect to see the first diagonal entry divided by the second entry.
  // However, since these parameters are used in the persepctive division,
  // they behave the other way around.
  // Also note that we take the absolute value here and use _Sign later
  // to restore the signs to support mirroring.

  const GfVec2d window(fabs(projectionMatrix[1][1]), fabs(projectionMatrix[0][0]));

  // This tells us whether we need to adjust the parameters affecting the
  // vertical or horizontal aspects of the projectionMatrix.
  const CameraUtilConformWindowPolicy resolvedPolicy = _ResolveConformWindowPolicy(
      window, policy, targetAspect);

  if (resolvedPolicy == CameraUtilMatchHorizontally) {
    // Adjust vertical size
    result[1][1] = _Sign(projectionMatrix[1][1]) * window[1] * targetAspect;

    // Now handle the case that the frustum is asymetric, e.g., the angle
    // on the left is different from the angle on the right.
    // First compute the factor by which we scaled vertically...
    const double scaleFactor = _SafeDiv(result[1][1], projectionMatrix[1][1]);

    // ...and then apply it to the offsets making the frustum asymetric.
    // This one is important for perspective:
    result[2][1] *= scaleFactor;
    // This one is important for orthographic:
    result[3][1] *= scaleFactor;
  }
  else {
    // As above, but horizontally.
    result[0][0] = _Sign(projectionMatrix[0][0]) * _SafeDiv(window[0], targetAspect);

    const double scaleFactor = _SafeDiv(result[0][0], projectionMatrix[0][0]);

    result[2][0] *= scaleFactor;
    result[3][0] *= scaleFactor;
  }

  return result;
}

void CameraUtilConformWindow(GfCamera *camera,
                             CameraUtilConformWindowPolicy policy,
                             double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return;
  }

  const GfVec2d original(camera->GetHorizontalAperture(), camera->GetVerticalAperture());
  const GfVec2d conformed = CameraUtilConformedWindow(original, policy, targetAspect);

  camera->SetHorizontalAperture(conformed[0]);
  camera->SetVerticalAperture(conformed[1]);
}

void CameraUtilConformWindow(GfFrustum *frustum,
                             CameraUtilConformWindowPolicy policy,
                             double targetAspect)
{
  if (_DoesNotRequireAdjustment(policy)) {
    return;
  }

  GfRange2d screenWindowFitted = CameraUtilConformedWindow(
      frustum->GetWindow(), policy, targetAspect);
  frustum->SetWindow(screenWindowFitted);
}

PXR_NAMESPACE_CLOSE_SCOPE
