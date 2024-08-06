//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include <boost/python/def.hpp>

#include "Gf/gamma.h"
#include "Gf/vec3d.h"
#include "Gf/vec3f.h"
#include "Gf/vec4d.h"
#include "Gf/vec4f.h"
#include "pxr/pxrns.h"

#include "Tf/wrapTypeHelpers.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapGamma()
{
  def("ApplyGamma", (GfVec3f(*)(GfVec3f const &, double))GfApplyGamma);
  def("ApplyGamma", (GfVec3d(*)(GfVec3d const &, double))GfApplyGamma);
  def("ApplyGamma", (GfVec3h(*)(GfVec3h const &, double))GfApplyGamma);
  def("ApplyGamma", (GfVec4f(*)(GfVec4f const &, double))GfApplyGamma);
  def("ApplyGamma", (GfVec4d(*)(GfVec4d const &, double))GfApplyGamma);
  def("ApplyGamma", (GfVec4h(*)(GfVec4h const &, double))GfApplyGamma);
  def("GetDisplayGamma", GfGetDisplayGamma);
  def("ConvertDisplayToLinear", (GfVec3f(*)(GfVec3f const &))GfConvertDisplayToLinear);
  def("ConvertDisplayToLinear", (GfVec3d(*)(GfVec3d const &))GfConvertDisplayToLinear);
  def("ConvertDisplayToLinear", (GfVec3h(*)(GfVec3h const &))GfConvertDisplayToLinear);
  def("ConvertDisplayToLinear", (GfVec4f(*)(GfVec4f const &))GfConvertDisplayToLinear);
  def("ConvertDisplayToLinear", (GfVec4d(*)(GfVec4d const &))GfConvertDisplayToLinear);
  def("ConvertDisplayToLinear", (GfVec4h(*)(GfVec4h const &))GfConvertDisplayToLinear);
  def("ConvertLinearToDisplay", (GfVec3f(*)(GfVec3f const &))GfConvertLinearToDisplay);
  def("ConvertLinearToDisplay", (GfVec3d(*)(GfVec3d const &))GfConvertLinearToDisplay);
  def("ConvertLinearToDisplay", (GfVec3h(*)(GfVec3h const &))GfConvertLinearToDisplay);
  def("ConvertLinearToDisplay", (GfVec4f(*)(GfVec4f const &))GfConvertLinearToDisplay);
  def("ConvertLinearToDisplay", (GfVec4d(*)(GfVec4d const &))GfConvertLinearToDisplay);
  def("ConvertLinearToDisplay", (GfVec4h(*)(GfVec4h const &))GfConvertLinearToDisplay);
}
