//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/capsule_1.h"

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

static UsdAttribute _CreateHeightAttr(UsdGeomCapsule_1 &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateHeightAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double),
                               writeSparsely);
}

static UsdAttribute _CreateRadiusTopAttr(UsdGeomCapsule_1 &self,
                                         object defaultVal,
                                         bool writeSparsely)
{
  return self.CreateRadiusTopAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double),
                                  writeSparsely);
}

static UsdAttribute _CreateRadiusBottomAttr(UsdGeomCapsule_1 &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateRadiusBottomAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Double),
                                     writeSparsely);
}

static UsdAttribute _CreateAxisAttr(UsdGeomCapsule_1 &self, object defaultVal, bool writeSparsely)
{
  return self.CreateAxisAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                             writeSparsely);
}

static UsdAttribute _CreateExtentAttr(UsdGeomCapsule_1 &self,
                                      object defaultVal,
                                      bool writeSparsely)
{
  return self.CreateExtentAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float3Array),
                               writeSparsely);
}

static std::string _Repr(const UsdGeomCapsule_1 &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.Capsule_1(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdGeomCapsule_1()
{
  typedef UsdGeomCapsule_1 This;

  class_<This, bases<UsdGeomGprim>> cls("Capsule_1");

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

      .def("GetHeightAttr", &This::GetHeightAttr)
      .def("CreateHeightAttr",
           &_CreateHeightAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetRadiusTopAttr", &This::GetRadiusTopAttr)
      .def("CreateRadiusTopAttr",
           &_CreateRadiusTopAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetRadiusBottomAttr", &This::GetRadiusBottomAttr)
      .def("CreateRadiusBottomAttr",
           &_CreateRadiusBottomAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetAxisAttr", &This::GetAxisAttr)
      .def("CreateAxisAttr",
           &_CreateAxisAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetExtentAttr", &This::GetExtentAttr)
      .def("CreateExtentAttr",
           &_CreateExtentAttr,
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

}  // namespace
