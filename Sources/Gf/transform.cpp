//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Gf/transform.h"
#include "Gf/matrix4d.h"
#include "pxr/pxrns.h"

#include "Tf/type.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

// CODE_COVERAGE_OFF_GCOV_BUG
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<GfTransform>();
}
// CODE_COVERAGE_ON_GCOV_BUG

GfTransform &GfTransform::Set(const GfVec3d &scale,
                              const GfRotation &pivotOrientation,
                              const GfRotation &rotation,
                              const GfVec3d &pivotPosition,
                              const GfVec3d &translation)
{
  _scale = scale;
  _pivotOrientation = pivotOrientation;
  _rotation = rotation;
  _pivotPosition = pivotPosition;
  _translation = translation;

  return *this;
}

GfTransform &GfTransform::SetMatrix(const GfMatrix4d &m)
{
  // Factor the matrix into the components, while trying to leave
  // the pivotPosition field unchanged.

  // Create a matrix, [mNoPivot], given by:
  //          [pivotPositionInverse][mNoPivot][pivotPosition] = [m]
  //
  // So, [mNoPivot] = [pivotPosition][m][pivotPositionInverse]
  GfMatrix4d mPivotPos, mPivotPosInv;
  mPivotPos.SetTranslate(_pivotPosition);
  mPivotPosInv.SetTranslate(-_pivotPosition);
  GfMatrix4d mNoPivot = mPivotPos * m * mPivotPosInv;

  // Factor mNoPivot into the other components
  GfMatrix4d shearRotMat, rotMat, projMat;

  // Factor returns false if the given matrix is singular,
  // but produces a result anyway.  We use that result regardless,
  // because singular matrices (such as zero scales) are still
  // valid for constructing Transforms.
  mNoPivot.Factor(&shearRotMat, &_scale, &rotMat, &_translation, &projMat);

  _rotation = rotMat.ExtractRotation();

  // Don't set the scale orientation if the scale is unity
  if (_scale != GfVec3d(1.0, 1.0, 1.0))
    _pivotOrientation = shearRotMat.GetTranspose().ExtractRotation();
  else
    _pivotOrientation.SetIdentity();

  return *this;
}

GfTransform &GfTransform::SetIdentity()
{
  _scale.Set(1.0, 1.0, 1.0);
  _pivotOrientation.SetIdentity();
  _rotation.SetIdentity();
  _pivotPosition = GfVec3d(0);
  _translation = GfVec3d(0);

  return *this;
}

GfMatrix4d GfTransform::GetMatrix() const
{
  bool doPivot = (_pivotPosition != GfVec3d(0));
  bool doScale = (_scale != GfVec3d(1.0, 1.0, 1.0));
  bool doScaleOrient = (_pivotOrientation.GetAngle() != 0.0);
  bool doRotation = (_rotation.GetAngle() != 0.0);
  bool doTranslation = (_translation != GfVec3d(0));
  bool anySet = false;
  GfMatrix4d mtx;

  //
  // When multiplying matrices A*B, the effects of A are more local
  // than the effects of B (A's operation takes place before
  // B's). So we use post-multiplication of matrices (with the '*='
  // operator), in the order we want the operations to be applied.
  //

#define _GF_ACCUM(mtxOp) \
  { \
    if (anySet) { \
      GfMatrix4d tmp; \
      tmp.mtxOp; \
      mtx *= tmp; \
    } \
    else { \
      mtx.mtxOp; \
      anySet = true; \
    } \
  }

  if (doPivot)
    _GF_ACCUM(SetTranslate(-_pivotPosition));

  if (doScale) {
    if (doScaleOrient)
      _GF_ACCUM(SetRotate(_pivotOrientation.GetInverse()));

    _GF_ACCUM(SetScale(_scale));

    if (doScaleOrient)
      _GF_ACCUM(SetRotate(_pivotOrientation));
  }

  if (doRotation)
    _GF_ACCUM(SetRotate(_rotation));

  if (doPivot)
    _GF_ACCUM(SetTranslate(_pivotPosition));

  if (doTranslation)
    _GF_ACCUM(SetTranslate(_translation));

#undef _GF_ACCUM

  if (!anySet)
    mtx.SetIdentity();

  return mtx;
}

bool GfTransform::operator==(const GfTransform &xf) const
{
  return (GetScale() == xf.GetScale() && GetPivotOrientation() == xf.GetPivotOrientation() &&
          GetRotation() == xf.GetRotation() && GetPivotPosition() == xf.GetPivotPosition() &&
          GetTranslation() == xf.GetTranslation());
}

GfTransform &GfTransform::operator*=(const GfTransform &xf)
{
  return SetMatrix(GetMatrix() * xf.GetMatrix());
}

std::ostream &operator<<(std::ostream &out, const GfTransform &xf)
{
  const GfVec3d &t = xf.GetTranslation();

  const GfRotation &rotation = xf.GetRotation();
  const GfVec3d &rax = rotation.GetAxis();
  double rang = rotation.GetAngle();

  const GfVec3d &s = xf.GetScale();

  const GfVec3d &c = xf.GetPivotPosition();

  const GfRotation &pivotOrientation = xf.GetPivotOrientation();
  const GfVec3d &pax = pivotOrientation.GetAxis();
  double pang = pivotOrientation.GetAngle();

  // This class doesn't use the same precision helper that everyone
  // else uses (see Gf_OstreamHelperP) for some reason.

  // note:  we currently specify the same orientation for both scale and
  // rotation, but the format allows for different orientations.
  return out << "( "
             << "(" << s[0] << ", " << s[1] << ", " << s[2] << ", 0), "
             << "(" << pax[0] << ", " << pax[1] << ", " << pax[2] << ", " << pang << "), "
             << "(" << rax[0] << ", " << rax[1] << ", " << rax[2] << ", " << rang << "), "

             << "(" << c[0] << ", " << c[1] << ", " << c[2] << ", 0), "
             << "(" << t[0] << ", " << t[1] << ", " << t[2] << ", 0) "
             << ")";
}

PXR_NAMESPACE_CLOSE_SCOPE
