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
#include "Tf/pyEnum.h"
#include "Usd/common.h"
#include "Usd/object.h"
#include "Usd/stage.h"
#include "Usd/stageCache.h"
#include <pxr/pxrns.h>

#include <boost/python/def.hpp>
#include <boost/python/enum.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdCommon() {
  def("Describe", (std::string(*)(const UsdObject &))UsdDescribe);
  def("Describe", (std::string(*)(const UsdStageWeakPtr &))UsdDescribe);
  def("Describe", (std::string(*)(const UsdStageCache &))UsdDescribe);

  TfPyWrapEnum<UsdListPosition>();
  TfPyWrapEnum<UsdLoadPolicy>();
  enum_<UsdSchemaKind>("SchemaKind")
      .value("Invalid", UsdSchemaKind::Invalid)
      .value("AbstractBase", UsdSchemaKind::AbstractBase)
      .value("AbstractTyped", UsdSchemaKind::AbstractTyped)
      .value("ConcreteTyped", UsdSchemaKind::ConcreteTyped)
      .value("NonAppliedAPI", UsdSchemaKind::NonAppliedAPI)
      .value("SingleApplyAPI", UsdSchemaKind::SingleApplyAPI)
      .value("MultipleApplyAPI", UsdSchemaKind::MultipleApplyAPI);
}
