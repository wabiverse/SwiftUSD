//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/references.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdReferences()
{
  class_<UsdReferences>("References", no_init)
      .def("AddReference",
           (bool(UsdReferences::*)(const SdfReference &, UsdListPosition)) &
               UsdReferences::AddReference,
           (arg("ref"), arg("position") = UsdListPositionBackOfPrependList))
      .def("AddReference",
           (bool(UsdReferences::*)(
               const string &, const SdfPath &, const SdfLayerOffset &, UsdListPosition)) &
               UsdReferences::AddReference,
           (arg("assetPath"),
            arg("primPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPositionBackOfPrependList))
      .def("AddReference",
           (bool(UsdReferences::*)(const string &, const SdfLayerOffset &, UsdListPosition)) &
               UsdReferences::AddReference,
           (arg("assetPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPositionBackOfPrependList))
      .def("AddInternalReference",
           &UsdReferences::AddInternalReference,
           (arg("primPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPositionBackOfPrependList))

      .def("RemoveReference", &UsdReferences::RemoveReference, arg("ref"))
      .def("ClearReferences", &UsdReferences::ClearReferences)
      .def("SetReferences", &UsdReferences::SetReferences)
      .def("GetPrim", (UsdPrim(UsdReferences::*)()) & UsdReferences::GetPrim)
      .def(!self);
}
