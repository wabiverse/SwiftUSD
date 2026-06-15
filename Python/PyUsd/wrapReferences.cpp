//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Usd/references.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/operators.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapUsdReferences()
{
    class_<UsdReferences>("References", no_init)
        .def("AddReference",
             (bool (UsdReferences::*)(const SdfReference &, UsdListPosition))
             &UsdReferences::AddReference,
             (arg("ref"),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddReference",
             (bool (UsdReferences::*)(const string &, const SdfPath &,
                                      const SdfLayerOffset &, UsdListPosition))
             &UsdReferences::AddReference,
             (arg("assetPath"), arg("primPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddReference",(bool (UsdReferences::*)(const string &,
                                                     const SdfLayerOffset &,
                                                     UsdListPosition))
             &UsdReferences::AddReference,
             (arg("assetPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))
        .def("AddInternalReference",
             &UsdReferences::AddInternalReference, 
             (arg("primPath"),
              arg("layerOffset")=SdfLayerOffset(),
              arg("position")=UsdListPositionBackOfPrependList))

        .def("RemoveReference", &UsdReferences::RemoveReference, arg("ref"))
        .def("ClearReferences", &UsdReferences::ClearReferences)
        .def("SetReferences", &UsdReferences::SetReferences)
        .def("GetPrim", (UsdPrim (UsdReferences::*)()) &UsdReferences::GetPrim)
        .def(!self)
        ;
}
