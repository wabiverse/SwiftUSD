//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdPhysics/distanceJoint.h"

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

static UsdAttribute _CreateMinDistanceAttr(UsdPhysicsDistanceJoint &self,
                                           object defaultVal,
                                           bool writeSparsely)
{
  return self.CreateMinDistanceAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                    writeSparsely);
}

static UsdAttribute _CreateMaxDistanceAttr(UsdPhysicsDistanceJoint &self,
                                           object defaultVal,
                                           bool writeSparsely)
{
  return self.CreateMaxDistanceAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float),
                                    writeSparsely);
}

static std::string _Repr(const UsdPhysicsDistanceJoint &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdPhysics.DistanceJoint(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdPhysicsDistanceJoint()
{
  typedef UsdPhysicsDistanceJoint This;

  class_<This, bases<UsdPhysicsJoint>> cls("DistanceJoint");

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

      .def("GetMinDistanceAttr", &This::GetMinDistanceAttr)
      .def("CreateMinDistanceAttr",
           &_CreateMinDistanceAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetMaxDistanceAttr", &This::GetMaxDistanceAttr)
      .def("CreateMaxDistanceAttr",
           &_CreateMaxDistanceAttr,
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
