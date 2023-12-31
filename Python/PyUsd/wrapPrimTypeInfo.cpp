//
// Copyright 2020 Pixar
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
#include "Usd/primTypeInfo.h"
#include "Usd/pyConversions.h"
#include <pxr/pxrns.h>

#include "Tf/pyResultConversions.h"
#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdPrimTypeInfo() {
  typedef UsdPrimTypeInfo This;
  class_<This, boost::noncopyable>("PrimTypeInfo", no_init)
      .def("GetTypeName", &This::GetTypeName,
           return_value_policy<return_by_value>())
      .def("GetAppliedAPISchemas", &This::GetAppliedAPISchemas,
           return_value_policy<TfPySequenceToList>())
      .def("GetSchemaType", &This::GetSchemaType,
           return_value_policy<return_by_value>())
      .def("GetSchemaTypeName", &This::GetSchemaTypeName,
           return_value_policy<return_by_value>())
      .def("GetPrimDefinition", &This::GetPrimDefinition,
           return_internal_reference<>())
      .def(self == self)
      .def(self != self)

      .def("GetEmptyPrimType", &This::GetEmptyPrimType,
           return_internal_reference<>())
      .staticmethod("GetEmptyPrimType");
}
