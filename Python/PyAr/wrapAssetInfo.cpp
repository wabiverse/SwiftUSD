//
// Copyright 2022 Pixar
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
#include <pxr/pxrns.h>

#include "Ar/assetInfo.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static VtValue _GetResolverInfo(const ArAssetInfo &info) {
  return info.resolverInfo;
}

static void _SetResolverInfo(ArAssetInfo &info, const VtValue &resolverInfo) {
  info.resolverInfo = resolverInfo;
}

static size_t _GetHash(const ArAssetInfo &info) { return hash_value(info); }

void wrapAssetInfo() {
  using This = ArAssetInfo;

  class_<This>("AssetInfo")
      .def(init<>())

      .def(self == self)
      .def(self != self)

      .def("__hash__", &_GetHash)

      .def_readwrite("version", &This::version)
      .def_readwrite("assetName", &This::assetName)

      // Using .def_readwrite for resolverInfo gives this error on access:
      // "No python class registered for C++ class VtValue"
      //
      // Using .add_property works as expected.
      .add_property("resolverInfo", &_GetResolverInfo, &_SetResolverInfo);
}
