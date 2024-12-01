//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/pyResultConversions.h"
#include "Usd/inherits.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdInherits()
{
  class_<UsdInherits>("Inherits", no_init)
      .def("AddInherit",
           &UsdInherits::AddInherit,
           (arg("primPath"), arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("RemoveInherit", &UsdInherits::RemoveInherit, arg("primPath"))
      .def("ClearInherits", &UsdInherits::ClearInherits)
      .def("SetInherits", &UsdInherits::SetInherits)
      .def("GetAllDirectInherits",
           &UsdInherits::GetAllDirectInherits,
           return_value_policy<TfPySequenceToList>())
      .def("GetPrim", (UsdPrim(UsdInherits::*)()) & UsdInherits::GetPrim)
      .def(!self);
}
