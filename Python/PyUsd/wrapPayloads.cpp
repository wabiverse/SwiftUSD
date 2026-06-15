//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/payloads.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdPayloads()
{
    class_<UsdPayloads>("Payloads", no_init)
        .def("AddPayload",
             (bool (UsdPayloads::*)(const SdfPayload &, UsdListPosition))
             &UsdPayloads::AddPayload,
             (arg("payload"),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddPayload",
             (bool (UsdPayloads::*)(const string &, const SdfPath &,
                                    const SdfLayerOffset &, UsdListPosition))
             &UsdPayloads::AddPayload,
             (arg("assetPath"), arg("primPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddPayload",(bool (UsdPayloads::*)(const string &,
                                                 const SdfLayerOffset &,
                                                 UsdListPosition))
             &UsdPayloads::AddPayload,
             (arg("assetPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddInternalPayload",
             &UsdPayloads::AddInternalPayload, 
             (arg("primPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))

        .def("RemovePayload", &UsdPayloads::RemovePayload, arg("payload"))
        .def("ClearPayloads", &UsdPayloads::ClearPayloads)
        .def("SetPayloads", &UsdPayloads::SetPayloads)
        .def("GetPrim", (UsdPrim (UsdPayloads::*)()) &UsdPayloads::GetPrim)
        .def(!self)
        ;
}
