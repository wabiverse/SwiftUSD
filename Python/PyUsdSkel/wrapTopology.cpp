//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/topology.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"
#include "Usd/pyConversions.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

tuple _Validate(const UsdSkelTopology &self)
{
  std::string reason;
  bool success = self.Validate(&reason);
  return boost::python::make_tuple(success, reason);
}

}  // namespace

void wrapUsdSkelTopology()
{
  using This = UsdSkelTopology;

  class_<This>("Topology", no_init)
      .def(init<const SdfPathVector &>())
      .def(init<const VtTokenArray &>())
      .def(init<VtIntArray>())

      .def("GetParent", &This::GetParent)

      .def("IsRoot", &This::IsRoot)

      .def("GetParentIndices", &This::GetParentIndices, return_value_policy<return_by_value>())

      .def("GetNumJoints", &This::GetNumJoints)

      .def("__len__", &This::size)

      .def("Validate", &_Validate);
}
