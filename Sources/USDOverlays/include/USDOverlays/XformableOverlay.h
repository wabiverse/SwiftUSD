/* ----------------------------------------------------------------
 * :: :  O  P  E  N  U  S  D  :                                  ::
 * ----------------------------------------------------------------
 * Licensed under the terms set forth in the LICENSE.txt file, this
 * file is available at https://openusd.org/license.
 *
 *                   Copyright (C) 2016 Pixar. All Rights Reserved.
 *                              Copyright (C) 2024 Wabi Foundation.
 * ----------------------------------------------------------------
 *  . x x x . o o o . x x x . : : : .    o  x  o    . : : : .
 * ---------------------------------------------------------------- */

#ifndef SWIFTUSD_SWIFTOVERLAY_XFORMABLE_OVERLAY_H
#define SWIFTUSD_SWIFTOVERLAY_XFORMABLE_OVERLAY_H

#include "Usd/prim.h"
#include "UsdGeom/camera.h"
#include "UsdGeom/capsule.h"
#include "UsdGeom/cone.h"
#include "UsdGeom/cube.h"
#include "UsdGeom/curves.h"
#include "UsdGeom/cylinder.h"
#include "UsdGeom/mesh.h"
#include "UsdGeom/plane.h"
#include "UsdGeom/sphere.h"
#include "UsdGeom/xform.h"
#include "UsdGeom/xformable.h"
#include "UsdGeom/xformOp.h"
#include "UsdLux/cylinderLight.h"
#include "UsdLux/diskLight.h"
#include "UsdLux/distantLight.h"
#include "UsdLux/domeLight.h"
#include "UsdLux/geometryLight.h"
#include "UsdLux/portalLight.h"
#include "UsdLux/rectLight.h"
#include "UsdLux/sphereLight.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

/// On Linux with Swift 6.1+, `self` triggers a ClangImporter bug where the member
/// is reported as an "ambiguous use" with two identical `__ObjC` candidates pointing
/// at the same declaration.
///
/// To avoid Swift ever performing inherited-member lookup for these methods,
/// every `Add*Op` call is made from C++, inside this overlay.
namespace Overlay
{
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addXformOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Type opType, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);

  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addTranslateOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);

  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addScaleOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);

  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateXOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);

  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateYOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);

  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomXformable &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCamera &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCapsule &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCone &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCube &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCurves &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomCylinder &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomMesh &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomPlane &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomSphere &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdGeomXform &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxCylinderLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxDiskLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxDistantLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxDomeLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxGeometryLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxPortalLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxRectLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
  Pixar::UsdGeomXformOp addRotateZOp(const Pixar::UsdLuxSphereLight &schema, Pixar::UsdGeomXformOp::Precision precision, const Pixar::TfToken &opSuffix, bool isInverseOp);
}  // namespace Overlay

#endif  // SWIFTUSD_SWIFTOVERLAY_XFORMABLE_OVERLAY_H
