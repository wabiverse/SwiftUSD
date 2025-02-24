//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/gprim.h"

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

static UsdAttribute _CreateDisplayColorAttr(UsdGeomGprim &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateDisplayColorAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Color3fArray), writeSparsely);
}

static UsdAttribute _CreateDisplayOpacityAttr(UsdGeomGprim &self,
                                              object defaultVal,
                                              bool writeSparsely)
{
  return self.CreateDisplayOpacityAttr(
      UsdPythonToSdfType(defaultVal, SdfValueTypeNames->FloatArray), writeSparsely);
}

static UsdAttribute _CreateDoubleSidedAttr(UsdGeomGprim &self,
                                           object defaultVal,
                                           bool writeSparsely)
{
  return self.CreateDoubleSidedAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool),
                                    writeSparsely);
}

static UsdAttribute _CreateOrientationAttr(UsdGeomGprim &self,
                                           object defaultVal,
                                           bool writeSparsely)
{
  return self.CreateOrientationAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                    writeSparsely);
}

static std::string _Repr(const UsdGeomGprim &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.Gprim(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomGprim()
{
  typedef UsdGeomGprim This;

  class_<This, bases<UsdGeomBoundable>> cls("Gprim");

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

      .def("GetDisplayColorAttr", &This::GetDisplayColorAttr)
      .def("CreateDisplayColorAttr",
           &_CreateDisplayColorAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetDisplayOpacityAttr", &This::GetDisplayOpacityAttr)
      .def("CreateDisplayOpacityAttr",
           &_CreateDisplayOpacityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetDoubleSidedAttr", &This::GetDoubleSidedAttr)
      .def("CreateDoubleSidedAttr",
           &_CreateDoubleSidedAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetOrientationAttr", &This::GetOrientationAttr)
      .def("CreateOrientationAttr",
           &_CreateOrientationAttr,
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

WRAP_CUSTOM
{
  _class.def("GetDisplayColorPrimvar", &UsdGeomGprim::GetDisplayColorPrimvar)
      .def("CreateDisplayColorPrimvar",
           &UsdGeomGprim::CreateDisplayColorPrimvar,
           (arg("interpolation") = TfToken(), arg("elementSize") = -1))
      .def("GetDisplayOpacityPrimvar", &UsdGeomGprim::GetDisplayOpacityPrimvar)
      .def("CreateDisplayOpacityPrimvar",
           &UsdGeomGprim::CreateDisplayOpacityPrimvar,
           (arg("interpolation") = TfToken(), arg("elementSize") = -1));
}

}  // anonymous namespace
