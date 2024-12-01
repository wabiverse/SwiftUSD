//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/payloads.h"
#include "pxr/pxrns.h"

#include <boost/python/class.hpp>
#include <boost/python/operators.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdPayloads()
{
  class_<UsdPayloads>("Payloads", no_init)
      .def("AddPayload",
           (bool(UsdPayloads::*)(const SdfPayload &, UsdListPosition)) & UsdPayloads::AddPayload,
           (arg("payload"), arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("AddPayload",
           (bool(UsdPayloads::*)(
               const string &, const SdfPath &, const SdfLayerOffset &, UsdListPosition)) &
               UsdPayloads::AddPayload,
           (arg("assetPath"),
            arg("primPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("AddPayload",
           (bool(UsdPayloads::*)(const string &, const SdfLayerOffset &, UsdListPosition)) &
               UsdPayloads::AddPayload,
           (arg("assetPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))
      .def("AddInternalPayload",
           &UsdPayloads::AddInternalPayload,
           (arg("primPath"),
            arg("layerOffset") = SdfLayerOffset(),
            arg("position") = UsdListPosition::UsdListPositionBackOfPrependList))

      .def("RemovePayload", &UsdPayloads::RemovePayload, arg("payload"))
      .def("ClearPayloads", &UsdPayloads::ClearPayloads)
      .def("SetPayloads", &UsdPayloads::SetPayloads)
      .def("GetPrim", (UsdPrim(UsdPayloads::*)()) & UsdPayloads::GetPrim)
      .def(!self);
}
