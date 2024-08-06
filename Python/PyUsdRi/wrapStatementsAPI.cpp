//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdRi/statementsAPI.h"

#include "Sdf/primSpec.h"

#include "Tf/pyAnnotatedBoolResult.h"
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

static std::string _Repr(const UsdRiStatementsAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdRi.StatementsAPI(%s)", primRepr.c_str());
}

struct UsdRiStatementsAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdRiStatementsAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdRiStatementsAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim)
{
  std::string whyNot;
  bool result = UsdRiStatementsAPI::CanApply(prim, &whyNot);
  return UsdRiStatementsAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdRiStatementsAPI()
{
  typedef UsdRiStatementsAPI This;

  UsdRiStatementsAPI_CanApplyResult::Wrap<UsdRiStatementsAPI_CanApplyResult>("_CanApplyResult",
                                                                             "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("StatementsAPI");

  cls.def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

      .def("CanApply", &_WrapCanApply, (arg("prim")))
      .staticmethod("CanApply")

      .def("Apply", &This::Apply, (arg("prim")))
      .staticmethod("Apply")

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

static SdfPathVector _GetModelCoordinateSystems(const UsdRiStatementsAPI &self)
{
  SdfPathVector result;
  self.GetModelCoordinateSystems(&result);
  return result;
}

static SdfPathVector _GetModelScopedCoordinateSystems(const UsdRiStatementsAPI &self)
{
  SdfPathVector result;
  self.GetModelScopedCoordinateSystems(&result);
  return result;
}

WRAP_CUSTOM
{
  _class
      .def("CreateRiAttribute",
           (UsdAttribute(UsdRiStatementsAPI::*)(
               const TfToken &, const TfType &, const std::string &)) &
               UsdRiStatementsAPI::CreateRiAttribute,
           (arg("name"), arg("tfType"), arg("nameSpace") = "user"))
      .def("CreateRiAttribute",
           (UsdAttribute(UsdRiStatementsAPI::*)(
               const TfToken &, const std::string &, const std::string &)) &
               UsdRiStatementsAPI::CreateRiAttribute,
           (arg("name"), arg("riType"), arg("nameSpace") = "user"))
      .def("GetRiAttribute",
           &UsdRiStatementsAPI::GetRiAttribute,
           (arg("name"), arg("nameSpace") = "user"))
      .def("GetRiAttributes",
           &UsdRiStatementsAPI::GetRiAttributes,
           (arg("nameSpace") = ""),
           return_value_policy<TfPySequenceToList>())
      .def("GetRiAttributeName", UsdRiStatementsAPI::GetRiAttributeName, (arg("prop")))
      .staticmethod("GetRiAttributeName")
      .def("GetRiAttributeNameSpace", &UsdRiStatementsAPI::GetRiAttributeNameSpace, (arg("prop")))
      .staticmethod("GetRiAttributeNameSpace")
      .def("IsRiAttribute", &UsdRiStatementsAPI::IsRiAttribute, (arg("prop")))
      .staticmethod("IsRiAttribute")
      .def("MakeRiAttributePropertyName",
           &UsdRiStatementsAPI::MakeRiAttributePropertyName,
           (arg("attrName")))
      .staticmethod("MakeRiAttributePropertyName")
      .def("SetCoordinateSystem", &UsdRiStatementsAPI::SetCoordinateSystem, (arg("coordSysName")))
      .def("GetCoordinateSystem", &UsdRiStatementsAPI::GetCoordinateSystem)
      .def("HasCoordinateSystem", &UsdRiStatementsAPI::HasCoordinateSystem)

      .def("SetScopedCoordinateSystem",
           &UsdRiStatementsAPI::SetScopedCoordinateSystem,
           (arg("coordSysName")))
      .def("GetScopedCoordinateSystem", &UsdRiStatementsAPI::GetScopedCoordinateSystem)
      .def("HasScopedCoordinateSystem", &UsdRiStatementsAPI::HasScopedCoordinateSystem)

      .def("GetModelCoordinateSystems",
           _GetModelCoordinateSystems,
           return_value_policy<TfPySequenceToList>())
      .def("GetModelScopedCoordinateSystems",
           _GetModelScopedCoordinateSystems,
           return_value_policy<TfPySequenceToList>());
}

}  // anonymous namespace
