//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "UsdRi/renderPassAPI.h"
#include "Usd/schemaBase.h"

#include "Sdf/primSpec.h"

#include "Usd/pyConversions.h"
#include "Tf/pyAnnotatedBoolResult.h"
#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"

#include <boost/python.hpp>

#include <string>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace
{

#define WRAP_CUSTOM    \
  template <class Cls> \
  static void _CustomWrapCode(Cls &_class)

  // fwd decl.
  WRAP_CUSTOM;

  static std::string
  _Repr(const UsdRiRenderPassAPI &self)
  {
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdRi.RenderPassAPI(%s)",
        primRepr.c_str());
  }

  struct UsdRiRenderPassAPI_CanApplyResult : public TfPyAnnotatedBoolResult<std::string>
  {
    UsdRiRenderPassAPI_CanApplyResult(bool val, std::string const &msg) : TfPyAnnotatedBoolResult<std::string>(val, msg) {}
  };

  static UsdRiRenderPassAPI_CanApplyResult
  _WrapCanApply(const UsdPrim &prim)
  {
    std::string whyNot;
    bool result = UsdRiRenderPassAPI::CanApply(prim, &whyNot);
    return UsdRiRenderPassAPI_CanApplyResult(result, whyNot);
  }

} // anonymous namespace

void wrapUsdRiRenderPassAPI()
{
  typedef UsdRiRenderPassAPI This;

  UsdRiRenderPassAPI_CanApplyResult::Wrap<UsdRiRenderPassAPI_CanApplyResult>(
      "_CanApplyResult", "whyNot");

  class_<This, bases<UsdAPISchemaBase>>
      cls("RenderPassAPI");

  cls
      .def(init<UsdPrim>(arg("prim")))
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

      .def("_GetStaticTfType", (TfType const &(*)())TfType::Find<This>,
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

namespace
{

  WRAP_CUSTOM
  {
    _class
        .def("GetCameraVisibilityCollectionAPI",
             &UsdRiRenderPassAPI::GetCameraVisibilityCollectionAPI)
        .def("GetMatteCollectionAPI",
             &UsdRiRenderPassAPI::GetMatteCollectionAPI);
  }

}
