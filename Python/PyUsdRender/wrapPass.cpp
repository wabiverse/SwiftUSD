//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/schemaBase.h"
#include "UsdRender/pass.h"

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

static UsdAttribute _CreatePassTypeAttr(UsdRenderPass &self, object defaultVal, bool writeSparsely)
{
  return self.CreatePassTypeAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token),
                                 writeSparsely);
}

static UsdAttribute _CreateCommandAttr(UsdRenderPass &self, object defaultVal, bool writeSparsely)
{
  return self.CreateCommandAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->StringArray),
                                writeSparsely);
}

static UsdAttribute _CreateFileNameAttr(UsdRenderPass &self, object defaultVal, bool writeSparsely)
{
  return self.CreateFileNameAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Asset),
                                 writeSparsely);
}

static UsdAttribute _CreateDenoiseEnableAttr(UsdRenderPass &self,
                                             object defaultVal,
                                             bool writeSparsely)
{
  return self.CreateDenoiseEnableAttr(UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Bool),
                                      writeSparsely);
}

static std::string _Repr(const UsdRenderPass &self)
{
  std::string primRepr = TfPyRepr(self.GetPrim());
  return TfStringPrintf("UsdRender.Pass(%s)", primRepr.c_str());
}

}  // anonymous namespace

void wrapUsdRenderPass()
{
  typedef UsdRenderPass This;

  class_<This, bases<UsdTyped>> cls("Pass");

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

      .def("GetPassTypeAttr", &This::GetPassTypeAttr)
      .def("CreatePassTypeAttr",
           &_CreatePassTypeAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetCommandAttr", &This::GetCommandAttr)
      .def("CreateCommandAttr",
           &_CreateCommandAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetFileNameAttr", &This::GetFileNameAttr)
      .def("CreateFileNameAttr",
           &_CreateFileNameAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetDenoiseEnableAttr", &This::GetDenoiseEnableAttr)
      .def("CreateDenoiseEnableAttr",
           &_CreateDenoiseEnableAttr,
           (arg("defaultValue") = object(), arg("writeSparsely") = false))

      .def("GetRenderSourceRel", &This::GetRenderSourceRel)
      .def("CreateRenderSourceRel", &This::CreateRenderSourceRel)

      .def("GetInputPassesRel", &This::GetInputPassesRel)
      .def("CreateInputPassesRel", &This::CreateInputPassesRel)

      .def("GetDenoisePassRel", &This::GetDenoisePassRel)
      .def("CreateDenoisePassRel", &This::CreateDenoisePassRel)
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
  _class.def("GetRenderVisibilityCollectionAPI", &UsdRenderPass::GetRenderVisibilityCollectionAPI);
}

}  // namespace
