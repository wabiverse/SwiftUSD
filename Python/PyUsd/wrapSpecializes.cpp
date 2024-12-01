//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/specializes.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdSpecializes()
{
  class_<UsdSpecializes>("Specializes", no_init)
      .def("AddSpecialize",
           &UsdSpecializes::AddSpecialize,
           (arg("primPath"), arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("RemoveSpecialize", &UsdSpecializes::RemoveSpecialize, arg("primPath"))
      .def("ClearSpecializes", &UsdSpecializes::ClearSpecializes)
      .def("SetSpecializes", &UsdSpecializes::SetSpecializes)
      .def("GetPrim", (UsdPrim(UsdSpecializes::*)()) & UsdSpecializes::GetPrim)
      .def(!self);
}
