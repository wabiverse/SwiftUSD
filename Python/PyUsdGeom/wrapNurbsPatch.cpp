//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/nurbsPatch.h"

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

static UsdAttribute _CreateUVertexCountAttr(UsdGeomNurbsPatch &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateUVertexCountAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int),
                                     writeSparsely);
}

static UsdAttribute _CreateVVertexCountAttr(UsdGeomNurbsPatch &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateVVertexCountAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int),
                                     writeSparsely);
}

static UsdAttribute _CreateUOrderAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateUOrderAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int),
                               writeSparsely);
}

static UsdAttribute _CreateVOrderAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateVOrderAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int),
                               writeSparsely);
}

static UsdAttribute _CreateUKnotsAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateUKnotsAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->DoubleArray),
                               writeSparsely);
}

static UsdAttribute _CreateVKnotsAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateVKnotsAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->DoubleArray),
                               writeSparsely);
}

static UsdAttribute _CreateUFormAttr(UsdGeomNurbsPatch &self,
                                     object defaultVal,
                                     bool writeSparsely)
{
  return self.CreateUFormAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                              writeSparsely);
}

static UsdAttribute _CreateVFormAttr(UsdGeomNurbsPatch &self,
                                     object defaultVal,
                                     bool writeSparsely)
{
  return self.CreateVFormAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                              writeSparsely);
}

static UsdAttribute _CreateURangeAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateURangeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double2),
                               writeSparsely);
}

static UsdAttribute _CreateVRangeAttr(UsdGeomNurbsPatch &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateVRangeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double2),
                               writeSparsely);
}

static UsdAttribute _CreatePointWeightsAttr(UsdGeomNurbsPatch &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreatePointWeightsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->DoubleArray), writeSparsely);
}

static UsdAttribute _CreateTrimCurveCountsAttr(UsdGeomNurbsPatch &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateTrimCurveCountsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateTrimCurveOrdersAttr(UsdGeomNurbsPatch &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateTrimCurveOrdersAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateTrimCurveVertexCountsAttr(UsdGeomNurbsPatch &self,
                                                     object defaultVal,
                                                     bool writeSparsely)
{
  return self.CreateTrimCurveVertexCountsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateTrimCurveKnotsAttr(UsdGeomNurbsPatch &self,
                                              object defaultVal,
                                              bool writeSparsely)
{
  return self.CreateTrimCurveKnotsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->DoubleArray), writeSparsely);
}

static UsdAttribute _CreateTrimCurveRangesAttr(UsdGeomNurbsPatch &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateTrimCurveRangesAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double2Array), writeSparsely);
}

static UsdAttribute _CreateTrimCurvePointsAttr(UsdGeomNurbsPatch &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateTrimCurvePointsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double3Array), writeSparsely);
}

static std::string _Repr(const UsdGeomNurbsPatch &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.NurbsPatch(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomNurbsPatch()
{
  typedef UsdGeomNurbsPatch This;

  class_<This, bases<UsdGeomPointBased>> cls("NurbsPatch");

  cls.def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

      .def("Define", &This::Define, (arg("stage"), arg("path")))
      .staticmethod("Define")

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

      .def("GetUVertexCountAttr", &This::GetUVertexCountAttr)
      .def("CreateUVertexCountAttr",
           &_CreateUVertexCountAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVVertexCountAttr", &This::GetVVertexCountAttr)
      .def("CreateVVertexCountAttr",
           &_CreateVVertexCountAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetUOrderAttr", &This::GetUOrderAttr)
      .def("CreateUOrderAttr",
           &_CreateUOrderAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVOrderAttr", &This::GetVOrderAttr)
      .def("CreateVOrderAttr",
           &_CreateVOrderAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetUKnotsAttr", &This::GetUKnotsAttr)
      .def("CreateUKnotsAttr",
           &_CreateUKnotsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVKnotsAttr", &This::GetVKnotsAttr)
      .def("CreateVKnotsAttr",
           &_CreateVKnotsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetUFormAttr", &This::GetUFormAttr)
      .def("CreateUFormAttr",
           &_CreateUFormAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVFormAttr", &This::GetVFormAttr)
      .def("CreateVFormAttr",
           &_CreateVFormAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetURangeAttr", &This::GetURangeAttr)
      .def("CreateURangeAttr",
           &_CreateURangeAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetVRangeAttr", &This::GetVRangeAttr)
      .def("CreateVRangeAttr",
           &_CreateVRangeAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetPointWeightsAttr", &This::GetPointWeightsAttr)
      .def("CreatePointWeightsAttr",
           &_CreatePointWeightsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurveCountsAttr", &This::GetTrimCurveCountsAttr)
      .def("CreateTrimCurveCountsAttr",
           &_CreateTrimCurveCountsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurveOrdersAttr", &This::GetTrimCurveOrdersAttr)
      .def("CreateTrimCurveOrdersAttr",
           &_CreateTrimCurveOrdersAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurveVertexCountsAttr", &This::GetTrimCurveVertexCountsAttr)
      .def("CreateTrimCurveVertexCountsAttr",
           &_CreateTrimCurveVertexCountsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurveKnotsAttr", &This::GetTrimCurveKnotsAttr)
      .def("CreateTrimCurveKnotsAttr",
           &_CreateTrimCurveKnotsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurveRangesAttr", &This::GetTrimCurveRangesAttr)
      .def("CreateTrimCurveRangesAttr",
           &_CreateTrimCurveRangesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTrimCurvePointsAttr", &This::GetTrimCurvePointsAttr)
      .def("CreateTrimCurvePointsAttr",
           &_CreateTrimCurvePointsAttr,
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

WRAP_CUSTOM {}

}  // anonymous namespace
