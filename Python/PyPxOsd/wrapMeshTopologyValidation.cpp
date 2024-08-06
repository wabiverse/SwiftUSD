//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "PxOsd/meshTopology.h"
#include "PxOsd/meshTopologyValidation.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyEnum.h"
#include "Tf/pyUtils.h"

#include <boost/python/class.hpp>
#include <boost/python/copy_const_reference.hpp>
#include <boost/python/iterator.hpp>
#include <boost/python/operators.hpp>

#include <sstream>
#include <vector>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static std::string _InvalidationRepr(PxOsdMeshTopologyValidation::Invalidation const &invalidation)
{
  return TfStringPrintf("PxOsd.MeshTopologyValidation.Invalidation('%s', '%s')",
                        TfPyRepr(invalidation.code).c_str(),
                        invalidation.message.c_str());
}

static std::string _ValidationRepr(PxOsdMeshTopologyValidation const &validation)
{
  std::ostringstream repr(std::ostringstream::ate);
  if (validation) {
    repr << "PxOsd.MeshTopologyValidation()";
  }
  else {
    repr << "PxOsd.MeshTopologyValidation<";
    for (auto const &element : validation) {
      repr << TfPyRepr(element.code) << ", " << element.message << "), ";
    }
    repr << ">";
  }
  return repr.str();
}

static PxOsdMeshTopologyValidation::Invalidation _InvalidationInit(
    PxOsdMeshTopologyValidation::Code code, std::string const &message)
{
  return {code, message};
}

void wrapMeshTopologyValidation()
{
  using This = PxOsdMeshTopologyValidation;

  class_<This> cls("MeshTopologyValidation", init<>());
  cls.def(!self);
  {
    scope obj = cls;
    TfPyWrapEnum<This::Code, true>();
    class_<This::Invalidation>("Invalidation", no_init)
        .def("__init__", &::_InvalidationInit)
        .def_readwrite("code", &This::Invalidation::code)
        .def_readwrite("message", &This::Invalidation::message)
        .def("__repr__", &::_InvalidationRepr);
  }
  cls.def("__repr__", &::_ValidationRepr);
  cls.def("__iter__", iterator<This>());
}
