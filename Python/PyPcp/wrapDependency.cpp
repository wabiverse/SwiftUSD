//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Pcp/dependency.h"
#include "Tf/makePyConstructor.h"
#include "Tf/pyEnum.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

using namespace boost::python;
using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static string _DependencyRepr(const PcpDependency &dep)
{
  return TF_PY_REPR_PREFIX + "Cache.Dependency(" + TfPyRepr(dep.indexPath) + ", " +
         TfPyRepr(dep.sitePath) + ", " + TfPyRepr(dep.mapFunc) + ")";
}

static PcpDependency *_DependencyInit(const SdfPath &indexPath,
                                      const SdfPath &sitePath,
                                      const PcpMapFunction &mapFunc)
{
  return new PcpDependency{indexPath, sitePath, mapFunc};
}

}  // anonymous namespace

void wrapDependency()
{
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
