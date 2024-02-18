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
#include "UsdVol/fieldAsset.h"
#include "Usd/schemaBase.h"

#include "Sdf/primSpec.h"

#include "Usd/pyConversions.h"
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

  static UsdAttribute
  _CreateFilePathAttr(UsdVolFieldAsset &self,
                      object defaultVal, bool writeSparsely)
  {
    return self.CreateFilePathAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Asset), writeSparsely);
  }

  static UsdAttribute
  _CreateFieldNameAttr(UsdVolFieldAsset &self,
                       object defaultVal, bool writeSparsely)
  {
    return self.CreateFieldNameAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
  }

  static UsdAttribute
  _CreateFieldIndexAttr(UsdVolFieldAsset &self,
                        object defaultVal, bool writeSparsely)
  {
    return self.CreateFieldIndexAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Int), writeSparsely);
  }

  static UsdAttribute
  _CreateFieldDataTypeAttr(UsdVolFieldAsset &self,
                           object defaultVal, bool writeSparsely)
  {
    return self.CreateFieldDataTypeAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
  }

  static UsdAttribute
  _CreateVectorDataRoleHintAttr(UsdVolFieldAsset &self,
                                object defaultVal, bool writeSparsely)
  {
    return self.CreateVectorDataRoleHintAttr(
        UsdPythonToSdfType(defaultVal, SdfValueTypeNames->Token), writeSparsely);
  }

  static std::string
  _Repr(const UsdVolFieldAsset &self)
  {
    std::string primRepr = TfPyRepr(self.GetPrim());
    return TfStringPrintf(
        "UsdVol.FieldAsset(%s)",
        primRepr.c_str());
  }

} // anonymous namespace

void wrapUsdVolFieldAsset()
{
  typedef UsdVolFieldAsset This;

  class_<This, bases<UsdVolFieldBase>>
      cls("FieldAsset");

  cls
      .def(init<UsdPrim>(arg("prim")))
      .def(init<UsdSchemaBase const &>(arg("schemaObj")))
      .def(TfTypePythonClass())

      .def("Get", &This::Get, (arg("stage"), arg("path")))
      .staticmethod("Get")

      .def("GetSchemaAttributeNames",
           &This::GetSchemaAttributeNames,
           arg("includeInherited") = true,
           return_value_policy<TfPySequenceToList>())
      .staticmethod("GetSchemaAttributeNames")

      .def("_GetStaticTfType", (TfType const &(*)())TfType::Find<This>,
           return_value_policy<return_by_value>())
      .staticmethod("_GetStaticTfType")

      .def(!self)

      .def("GetFilePathAttr",
           &This::GetFilePathAttr)
      .def("CreateFilePathAttr",
           &_CreateFilePathAttr,
           (arg("defaultValue") = object(),
            arg("writeSparsely") = false))

      .def("GetFieldNameAttr",
           &This::GetFieldNameAttr)
      .def("CreateFieldNameAttr",
           &_CreateFieldNameAttr,
           (arg("defaultValue") = object(),
            arg("writeSparsely") = false))

      .def("GetFieldIndexAttr",
           &This::GetFieldIndexAttr)
      .def("CreateFieldIndexAttr",
           &_CreateFieldIndexAttr,
           (arg("defaultValue") = object(),
            arg("writeSparsely") = false))

      .def("GetFieldDataTypeAttr",
           &This::GetFieldDataTypeAttr)
      .def("CreateFieldDataTypeAttr",
           &_CreateFieldDataTypeAttr,
           (arg("defaultValue") = object(),
            arg("writeSparsely") = false))

      .def("GetVectorDataRoleHintAttr",
           &This::GetVectorDataRoleHintAttr)
      .def("CreateVectorDataRoleHintAttr",
           &_CreateVectorDataRoleHintAttr,
           (arg("defaultValue") = object(),
            arg("writeSparsely") = false))

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
  }

}