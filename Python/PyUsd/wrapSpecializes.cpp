//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/specializes.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdSpecializes()
{
    class_<UsdSpecializes>("Specializes", no_init)
        .def("AddSpecialize", &UsdSpecializes::AddSpecialize,
             (arg("primPath"),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("RemoveSpecialize", &UsdSpecializes::RemoveSpecialize,
             arg("primPath"))
        .def("ClearSpecializes", &UsdSpecializes::ClearSpecializes)
        .def("SetSpecializes", &UsdSpecializes::SetSpecializes)
        .def("GetPrim", 
             (UsdPrim (UsdSpecializes::*)()) &UsdSpecializes::GetPrim)
        .def(!self)
        ;
}
