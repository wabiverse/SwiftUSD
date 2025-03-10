//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/curves.h"

#include "Sdf/primSpec.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"
#include "Usd/pyConversions.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

#define WRAP_CUSTOM template<class Cls> static void _CustomWrapCode(Cls &_class)

// fwd decl.
WRAP_CUSTOM;

static UsdAttribute _CreateCurveVertexCountsAttr(UsdGeomCurves &self,
                                                 object defaultVal,
                                                 bool writeSparsely)
{
  return self.CreateCurveVertexCountsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateWidthsAttr(UsdGeomCurves &self, object defaultVal, bool writeSparsely)
{
  return self.CreateWidthsAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->FloatArray),
                               writeSparsely);
}

static std::string _Repr(const UsdGeomCurves &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.Curves(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomCurves()
{
  typedef UsdGeomCurves This;

  class_<This, bases<UsdGeomPointBased>> cls("Curves");

  cls.def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

      .def("GetSchemaAttributeNames",
           &This::GetSchemaAttributeNames,
           arg("includeInherited") = true,
           return_value_policy<TfPySequenceToList>())
      .staticmethod("GetSchemaAttributeNames")

      .def("_GetStaticTfType",
           (TfType const &(*)())TfType::Find<This>,
           return_value_policy<return_by_value>())
      .staticmethod("_GetStaticTfType")

      .def(!self)

      .def("GetCurveVertexCountsAttr", &This::GetCurveVertexCountsAttr)
      .def("CreateCurveVertexCountsAttr",
           &_CreateCurveVertexCountsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetWidthsAttr", &This::GetWidthsAttr)
      .def("CreateWidthsAttr",
           &_CreateWidthsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("__repr__", ::_Repr);

  _CustomWrapCode(cls);
}

// ===================================================================== //
// Feel free to add custom code below this line, it will be preserved by
// the code generator.  The entry point for your custom code should look
// minimally like the following:
//
// WRAP_CUSTOM {
//     _class
//         .def("MyCustomMethod", ...)
//     ;
// }
//
// Of course any other ancillary or support code may be provided.
//
// Just remember to wrap code in the appropriate delimiters:
// 'namespace {', '}'.
//
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--

namespace {

static TfPyObjWrapper _ComputeExtent(object points, object widths)
{

  // Convert from python objects to VtValue
  VtVec3fArray extent;
  VtValue pointsAsVtValue = UsdPythonToSdfType(points, SdfValueTypeNames->Float3Array);
  VtValue widthsAsVtValue = UsdPythonToSdfType(widths, SdfValueTypeNames->FloatArray);

  // Check Proper conversion to VtVec3fArray
  if (!pointsAsVtValue.IsHolding<VtVec3fArray>()) {
    TF_CODING_ERROR("Improper value for 'points'");
    return object();
  }

  if (!widthsAsVtValue.IsHolding<VtFloatArray>()) {
    TF_CODING_ERROR("Improper value for 'widths'");
    return object();
  }

  // Convert from VtValue to VtVec3fArray
  VtVec3fArray pointsArray = pointsAsVtValue.UncheckedGet<VtVec3fArray>();
  VtFloatArray widthsArray = widthsAsVtValue.UncheckedGet<VtFloatArray>();

  if (UsdGeomCurves::ComputeExtent(pointsArray, widthsArray, &extent)) {
    return UsdVtValueToPython(VtValue(extent));
  }
  else {
    return object();
  }
}

WRAP_CUSTOM
{
  _class.def("GetWidthsInterpolation", &UsdGeomCurves::GetWidthsInterpolation)
      .def("SetWidthsInterpolation", &UsdGeomCurves::SetWidthsInterpolation, arg("interpolation"))

      .def("ComputeExtent", &_ComputeExtent, (arg("points"), arg("widths")))
      .def(
          "GetCurveCount", &UsdGeomCurves::GetCurveCount, arg("timeCode") = UsdTimeCode::Default())
      .staticmethod("ComputeExtent");
}

}  // anonymous namespace
