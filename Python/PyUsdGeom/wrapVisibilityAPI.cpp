//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdGeom/visibilityAPI.h"

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

static UsdAttribute _CreateGuideVisibilityAttr(UsdGeomVisibilityAPI &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateGuideVisibilityAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                        writeSparsely);
}

static UsdAttribute _CreateProxyVisibilityAttr(UsdGeomVisibilityAPI &self,
                                               object defaultVal,
                                               bool writeSparsely)
{
  return self.CreateProxyVisibilityAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                        writeSparsely);
}

static UsdAttribute _CreateRenderVisibilityAttr(UsdGeomVisibilityAPI &self,
                                                object defaultVal,
                                                bool writeSparsely)
{
  return self.CreateRenderVisibilityAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                         writeSparsely);
}

static std::string _Repr(const UsdGeomVisibilityAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdGeom.VisibilityAPI(%s)", primRepr.c_str());
}

struct UsdGeomVisibilityAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdGeomVisibilityAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdGeomVisibilityAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim)
{
  std::string whyNot;
  bool result = UsdGeomVisibilityAPI::CanApply(prim, &whyNot);
  return UsdGeomVisibilityAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdGeomVisibilityAPI()
{
  typedef UsdGeomVisibilityAPI This;

  UsdGeomVisibilityAPI_CanApplyResult::Wrap<UsdGeomVisibilityAPI_CanApplyResult>("_CanApplyResult",
                                                                                 "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("VisibilityAPI");

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

      .def("GetGuideVisibilityAttr", &This::GetGuideVisibilityAttr)
      .def("CreateGuideVisibilityAttr",
           &_CreateGuideVisibilityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetProxyVisibilityAttr", &This::GetProxyVisibilityAttr)
      .def("CreateProxyVisibilityAttr",
           &_CreateProxyVisibilityAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetRenderVisibilityAttr", &This::GetRenderVisibilityAttr)
      .def("CreateRenderVisibilityAttr",
           &_CreateRenderVisibilityAttr,
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
  _class.def("GetPurposeVisibilityAttr",
             &UsdGeomVisibilityAPI::GetPurposeVisibilityAttr,
             (arg("purpose")));
}

}  // namespace
