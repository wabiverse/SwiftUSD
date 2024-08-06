//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
///
/// \file camera/wrapConformWindow.h

#include "CameraUtil/conformWindow.h"

#include "Gf/camera.h"
#include "Gf/frustum.h"
#include "Gf/range2d.h"
#include "Gf/vec2d.h"
#include "Gf/vec4d.h"

#include "Tf/pyEnum.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapConformWindow()
{
  typedef GfRange2d (*Signature1)(const GfRange2d &, CameraUtilConformWindowPolicy, double);

  typedef GfVec2d (*Signature2)(const GfVec2d &, CameraUtilConformWindowPolicy, double);

  typedef GfVec4d (*Signature3)(const GfVec4d &, CameraUtilConformWindowPolicy, double);

  typedef GfMatrix4d (*Signature4)(const GfMatrix4d &, CameraUtilConformWindowPolicy, double);

  typedef void (*Signature5)(GfCamera *, CameraUtilConformWindowPolicy, double);

  typedef void (*Signature6)(GfFrustum *, CameraUtilConformWindowPolicy, double);

  def("ConformedWindow",
      (Signature1)&CameraUtilConformedWindow,
      (arg("window"), arg("policy"), arg("targetAspect")));
  def("ConformedWindow",
      (Signature2)&CameraUtilConformedWindow,
      (arg("window"), arg("policy"), arg("targetAspect")));
  def("ConformedWindow",
      (Signature3)&CameraUtilConformedWindow,
      (arg("window"), arg("policy"), arg("targetAspect")));
  def("ConformedWindow",
      (Signature4)&CameraUtilConformedWindow,
      (arg("window"), arg("policy"), arg("targetAspect")));

  def("ConformWindow",
      (Signature5)&CameraUtilConformWindow,
      (arg("camera"), arg("policy"), arg("targetAspect")));

  def("ConformWindow",
      (Signature6)&CameraUtilConformWindow,
      (arg("frustum"), arg("policy"), arg("targetAspect")));

  TfPyWrapEnum<CameraUtilConformWindowPolicy>();
}
