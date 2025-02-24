//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/editTarget.h"
#include "pxr/pxrns.h"

#include "Sdf/primSpec.h"
#include "Sdf/propertySpec.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdEditTarget()
{
  class_<UsdEditTarget>("EditTarget")
      .def(init<SdfLayerHandle, optional<PcpNodeRef>>((arg("layer"), arg("node"))))
      .def("ForLocalDirectVariant",
           &UsdEditTarget::ForLocalDirectVariant,
           (arg("layer"), arg("varSelPath")))
      .staticmethod("ForLocalDirectVariant")
      .def(self == self)
      .def(self != self)
      .def("IsNull", &UsdEditTarget::IsNull)
      .def("IsValid", &UsdEditTarget::IsValid)
      .def("GetLayer",
           static_cast<SdfLayerHandle (*)(UsdEditTarget const &)>(
               [](UsdEditTarget const &et) { return et.GetLayer(); }))
      .def(
          "GetMapFunction", &UsdEditTarget::GetMapFunction, return_value_policy<return_by_value>())
      .def("MapToSpecPath", &UsdEditTarget::MapToSpecPath, arg("scenePath"))
      .def("GetPrimSpecForScenePath", &UsdEditTarget::GetPrimSpecForScenePath, arg("scenePath"))
      .def("GetPropertySpecForScenePath",
           &UsdEditTarget::GetPropertySpecForScenePath,
           arg("scenePath"))
      .def("GetSpecForScenePath", &UsdEditTarget::GetPrimSpecForScenePath, arg("scenePath"))
      .def("ComposeOver", &UsdEditTarget::ComposeOver, arg("weaker"));

  // Allow passing SdLayerHandle to wrapped functions expecting UsdEditTarget.
  implicitly_convertible<SdfLayerHandle, UsdEditTarget>();
}
