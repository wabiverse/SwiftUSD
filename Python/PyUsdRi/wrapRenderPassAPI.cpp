//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdRi/renderPassAPI.h"

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

static std::string _Repr(const UsdRiRenderPassAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdRi.RenderPassAPI(%s)", primRepr.c_str());
}

struct UsdRiRenderPassAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdRiRenderPassAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdRiRenderPassAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim)
{
  std::string whyNot;
  bool result = UsdRiRenderPassAPI::CanApply(prim, &whyNot);
  return UsdRiRenderPassAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdRiRenderPassAPI()
{
  typedef UsdRiRenderPassAPI This;

  UsdRiRenderPassAPI_CanApplyResult::Wrap<UsdRiRenderPassAPI_CanApplyResult>("_CanApplyResult",
                                                                             "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("RenderPassAPI");

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

WRAP_CUSTOM
{
  _class
      .def("GetCameraVisibilityCollectionAPI",
           &UsdRiRenderPassAPI::GetCameraVisibilityCollectionAPI)
      .def("GetMatteCollectionAPI", &UsdRiRenderPassAPI::GetMatteCollectionAPI);
}

}  // namespace
