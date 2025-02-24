//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/inbetweenShape.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"
#include "Usd/pyConversions.h"

#include <boost/python.hpp>
#include <boost/python/extract.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

VtVec3fArray _GetOffsets(const UsdSkelInbetweenShape &self)
{
  VtVec3fArray points;
  self.GetOffsets(&points);
  return points;
}

VtVec3fArray _GetNormalOffsets(const UsdSkelInbetweenShape &self)
{
  VtVec3fArray points;
  self.GetNormalOffsets(&points);
  return points;
}

object _GetWeight(const UsdSkelInbetweenShape &self)
{
  float w = 0;
  return self.GetWeight(&w) ? object(w) : object();
}

bool _SetOffsets(const UsdSkelInbetweenShape &self, const object &val)
{
  const VtValue vtVal = UsdPythonToSdfType(val, SdfValueTypeNames->Vector3fArray);
  return vtVal.IsHolding<VtVec3fArray>() ? self.SetOffsets(vtVal.UncheckedGet<VtVec3fArray>()) :
                                           false;
}

bool _SetNormalOffsets(const UsdSkelInbetweenShape &self, const object &val)
{
  const VtValue vtVal = UsdPythonToSdfType(val, SdfValueTypeNames->Vector3fArray);
  return vtVal.IsHolding<VtVec3fArray>() ?
             self.SetNormalOffsets(vtVal.UncheckedGet<VtVec3fArray>()) :
             false;
}

UsdAttribute _CreateNormalOffsetsAttr(const UsdSkelInbetweenShape &self,
                                      const object &defaultValue)
{
  return self.CreateNormalOffsetsAttr(
      UsdPythonToSdfType(defaultValue, SdfValueTypeNames->Vector3fArray));
}

}  // namespace

void wrapUsdSkelInbetweenShape()
{
  using This = UsdSkelInbetweenShape;

  class_<This>("InbetweenShape")

      .def(init<UsdAttribute>(arg("attr")))
      .def(!self)
      .def(self == self)

      .def("GetWeight", &_GetWeight)
      .def("SetWeight", &This::SetWeight, arg("weight"))
      .def("HasAuthoredWeight", &This::HasAuthoredWeight)

      .def("GetOffsets", &_GetOffsets)
      .def("SetOffsets", &_SetOffsets, arg("offsets"))

      .def("GetNormalOffsetsAttr", &This::GetNormalOffsetsAttr)
      .def("CreateNormalOffsetsAttr", &_CreateNormalOffsetsAttr)

      .def("GetNormalOffsets", &_GetNormalOffsets)
      .def("SetNormalOffsets", &_SetNormalOffsets, arg("offsets"))

      .def("IsInbetween", &This::IsInbetween, arg("attr"))
      .staticmethod("IsInbetween")

      .def("GetAttr", &This::GetAttr, return_value_policy<return_by_value>())
      .def("IsDefined", &This::IsDefined);
}
