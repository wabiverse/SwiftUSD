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

#include "Pcp/dependency.h"
#include "Tf/makePyConstructor.h"
#include "Tf/pyEnum.h"
#include <pxr/pxrns.h>

#include <boost/python.hpp>

using namespace boost::python;
using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static string _DependencyRepr(const PcpDependency &dep) {
  return TF_PY_REPR_PREFIX + "Cache.Dependency(" + TfPyRepr(dep.indexPath) +
         ", " + TfPyRepr(dep.sitePath) + ", " + TfPyRepr(dep.mapFunc) + ")";
}

static PcpDependency *_DependencyInit(const SdfPath &indexPath,
                                      const SdfPath &sitePath,
                                      const PcpMapFunction &mapFunc) {
  return new PcpDependency{indexPath, sitePath, mapFunc};
}

} // anonymous namespace

void wrapDependency() {
  class_<PcpDependency>("Dependency", no_init)
      .def_readwrite("indexPath", &PcpDependency::indexPath)
      .def_readwrite("sitePath", &PcpDependency::sitePath)
      .def_readwrite("mapFunc", &PcpDependency::mapFunc)
      .def("__repr__", &_DependencyRepr)
      .def("__init__", make_constructor(_DependencyInit))
      .def(self == self)
      .def(self != self);

  TfPyWrapEnum<PcpDependencyType>();
}
