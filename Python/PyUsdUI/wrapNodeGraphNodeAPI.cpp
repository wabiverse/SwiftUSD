//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdUI/nodeGraphNodeAPI.h"

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

static UsdAttribute _CreatePosAttr(UsdUINodeGraphNodeAPI &self,
                                   object defaultVal,
                                   bool writeSparsely)
{
  return self.CreatePosAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float2),
                            writeSparsely);
}

static UsdAttribute _CreateStackingOrderAttr(UsdUINodeGraphNodeAPI &self,
                                             object defaultVal,
                                             bool writeSparsely)
{
  return self.CreateStackingOrderAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int),
                                      writeSparsely);
}

static UsdAttribute _CreateDisplayColorAttr(UsdUINodeGraphNodeAPI &self,
                                            object defaultVal,
                                            bool writeSparsely)
{
  return self.CreateDisplayColorAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Color3f),
                                     writeSparsely);
}

static UsdAttribute _CreateIconAttr(UsdUINodeGraphNodeAPI &self,
                                    object defaultVal,
                                    bool writeSparsely)
{
  return self.CreateIconAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Asset),
                             writeSparsely);
}

static UsdAttribute _CreateExpansionStateAttr(UsdUINodeGraphNodeAPI &self,
                                              object defaultVal,
                                              bool writeSparsely)
{
  return self.CreateExpansionStateAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                       writeSparsely);
}

static UsdAttribute _CreateSizeAttr(UsdUINodeGraphNodeAPI &self,
                                    object defaultVal,
                                    bool writeSparsely)
{
  return self.CreateSizeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Float2),
                             writeSparsely);
}

static std::string _Repr(const UsdUINodeGraphNodeAPI &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdUI.NodeGraphNodeAPI(%s)", primRepr.c_str());
}

struct UsdUINodeGraphNodeAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string> {
  UsdUINodeGraphNodeAPI_CanApplyResult(bool val, std::string const &msg)
      : TfPyAnnotatedBoolResult<std::string>(val, msg)
  {
  }
};

static UsdUINodeGraphNodeAPI_CanApplyResult _WrapCanApply(const UsdPrim &prim)
{
  std::string whyNot;
  bool result = UsdUINodeGraphNodeAPI::CanApply(prim, &whyNot);
  return UsdUINodeGraphNodeAPI_CanApplyResult(result, whyNot);
}

}  // anonymous namespace

void wrapUsdUINodeGraphNodeAPI()
{
  typedef UsdUINodeGraphNodeAPI This;

  UsdUINodeGraphNodeAPI_CanApplyResult::Wrap<UsdUINodeGraphNodeAPI_CanApplyResult>(
      "_CanApplyResult", "whyNot");

  class_<This, bases<UsdAPISchemaBase>> cls("NodeGraphNodeAPI");

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

      .def("GetPosAttr", &This::GetPosAttr)
      .def("CreatePosAttr",
           &_CreatePosAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetStackingOrderAttr", &This::GetStackingOrderAttr)
      .def("CreateStackingOrderAttr",
           &_CreateStackingOrderAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetDisplayColorAttr", &This::GetDisplayColorAttr)
      .def("CreateDisplayColorAttr",
           &_CreateDisplayColorAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetIconAttr", &This::GetIconAttr)
      .def("CreateIconAttr",
           &_CreateIconAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetExpansionStateAttr", &This::GetExpansionStateAttr)
      .def("CreateExpansionStateAttr",
           &_CreateExpansionStateAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetSizeAttr", &This::GetSizeAttr)
      .def("CreateSizeAttr",
           &_CreateSizeAttr,
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
