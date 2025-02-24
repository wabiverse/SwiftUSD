//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/mesh.h"

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

static UsdAttribute _CreateFaceVertexIndicesAttr(UsdGeomMesh &self,
                                                 object defaultVal,
                                                 bool writeSparsely)
{
  return self.CreateFaceVertexIndicesAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateFaceVertexCountsAttr(UsdGeomMesh &self,
                                                object defaultVal,
                                                bool writeSparsely)
{
  return self.CreateFaceVertexCountsAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray), writeSparsely);
}

static UsdAttribute _CreateSubdivisionSchemeAttr(UsdGeomMesh &self,
                                                 object defaultVal,
                                                 bool writeSparsely)
{
  return self.CreateSubdivisionSchemeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                          writeSparsely);
}

static UsdAttribute _CreateInterpolateBoundaryAttr(UsdGeomMesh &self,
                                                   object defaultVal,
                                                   bool writeSparsely)
{
  return self.CreateInterpolateBoundaryAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
}

static UsdAttribute _CreateFaceVaryingLinearInterpolationAttr(UsdGeomMesh &self,
                                                              object defaultVal,
                                                              bool writeSparsely)
{
  return self.CreateFaceVaryingLinearInterpolationAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
}

static UsdAttribute _CreateTriangleSubdivisionRuleAttr(UsdGeomMesh &self,
                                                       object defaultVal,
                                                       bool writeSparsely)
{
  return self.CreateTriangleSubdivisionRuleAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
}

static UsdAttribute _CreateHoleIndicesAttr(UsdGeomMesh &self,
                                           object defaultVal,
                                           bool writeSparsely)
{
  return self.CreateHoleIndicesAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray),
                                    writeSparsely);
}

static UsdAttribute _CreateCornerIndicesAttr(UsdGeomMesh &self,
                                             object defaultVal,
                                             bool writeSparsely)
{
  return self.CreateCornerIndicesAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray),
                                      writeSparsely);
}

static UsdAttribute _CreateCornerSharpnessesAttr(UsdGeomMesh &self,
                                                 object defaultVal,
                                                 bool writeSparsely)
{
  return self.CreateCornerSharpnessesAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->FloatArray), writeSparsely);
}

static UsdAttribute _CreateCreaseIndicesAttr(UsdGeomMesh &self,
                                             object defaultVal,
                                             bool writeSparsely)
{
  return self.CreateCreaseIndicesAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray),
                                      writeSparsely);
}

static UsdAttribute _CreateCreaseLengthsAttr(UsdGeomMesh &self,
                                             object defaultVal,
                                             bool writeSparsely)
{
  return self.CreateCreaseLengthsAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->IntArray),
                                      writeSparsely);
}

static UsdAttribute _CreateCreaseSharpnessesAttr(UsdGeomMesh &self,
                                                 object defaultVal,
                                                 bool writeSparsely)
{
  return self.CreateCreaseSharpnessesAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->FloatArray), writeSparsely);
}

static std::string _Repr(const UsdGeomMesh &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.Mesh(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomMesh()
{
  typedef UsdGeomMesh This;

  class_<This, bases<UsdGeomPointBased>> cls("Mesh");

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

      .def("GetFaceVertexIndicesAttr", &This::GetFaceVertexIndicesAttr)
      .def("CreateFaceVertexIndicesAttr",
           &_CreateFaceVertexIndicesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetFaceVertexCountsAttr", &This::GetFaceVertexCountsAttr)
      .def("CreateFaceVertexCountsAttr",
           &_CreateFaceVertexCountsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetSubdivisionSchemeAttr", &This::GetSubdivisionSchemeAttr)
      .def("CreateSubdivisionSchemeAttr",
           &_CreateSubdivisionSchemeAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetInterpolateBoundaryAttr", &This::GetInterpolateBoundaryAttr)
      .def("CreateInterpolateBoundaryAttr",
           &_CreateInterpolateBoundaryAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetFaceVaryingLinearInterpolationAttr", &This::GetFaceVaryingLinearInterpolationAttr)
      .def("CreateFaceVaryingLinearInterpolationAttr",
           &_CreateFaceVaryingLinearInterpolationAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetTriangleSubdivisionRuleAttr", &This::GetTriangleSubdivisionRuleAttr)
      .def("CreateTriangleSubdivisionRuleAttr",
           &_CreateTriangleSubdivisionRuleAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetHoleIndicesAttr", &This::GetHoleIndicesAttr)
      .def("CreateHoleIndicesAttr",
           &_CreateHoleIndicesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCornerIndicesAttr", &This::GetCornerIndicesAttr)
      .def("CreateCornerIndicesAttr",
           &_CreateCornerIndicesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCornerSharpnessesAttr", &This::GetCornerSharpnessesAttr)
      .def("CreateCornerSharpnessesAttr",
           &_CreateCornerSharpnessesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCreaseIndicesAttr", &This::GetCreaseIndicesAttr)
      .def("CreateCreaseIndicesAttr",
           &_CreateCreaseIndicesAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCreaseLengthsAttr", &This::GetCreaseLengthsAttr)
      .def("CreateCreaseLengthsAttr",
           &_CreateCreaseLengthsAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCreaseSharpnessesAttr", &This::GetCreaseSharpnessesAttr)
      .def("CreateCreaseSharpnessesAttr",
           &_CreateCreaseSharpnessesAttr,
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

tuple _ValidateTopology(const VtIntArray &faceVertexIndices,
                        const VtIntArray &faceVertexCounts,
                        size_t numPoints)
{
  std::string reason;
  bool valid = UsdGeomMesh::ValidateTopology(
      faceVertexIndices, faceVertexCounts, numPoints, &reason);
  return boost::python::make_tuple(valid, reason);
}

WRAP_CUSTOM
{
  typedef UsdGeomMesh This;

  _class
      .def("ValidateTopology",
           &_ValidateTopology,
           (arg("faceVertexIndices"), arg("faceVertexCounts"), arg("numPoints")))
      .def("GetFaceCount", &UsdGeomMesh::GetFaceCount, arg("timeCode") = UsdTimeCode::Default())
      .staticmethod("ValidateTopology");

  _class.attr("SHARPNESS_INFINITE") = UsdGeomMesh::SHARPNESS_INFINITE;
  ;
}

}  // anonymous namespace
