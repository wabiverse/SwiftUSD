//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Tf/pySignatureExt.h" // wrap lvalue-ref-qualified mem fns.
#include "UsdSemantics/labelsQuery.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/copy_const_reference.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/noncopyable.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {    

std::string _Repr(const UsdSemanticsLabelsQuery& query) {
     auto timeRepr = std::visit(
          [](auto&& queryTime) -> std::string { return TfPyRepr(queryTime); },
          query.GetTime());
     return TfStringPrintf(
          "%sLabelsQuery('%s', %s)",
          TF_PY_REPR_PREFIX.c_str(),
          query.GetTaxonomy().GetText(),
          timeRepr.c_str()
     );
}

}

void wrapUsdSemanticsLabelsQuery()
{
    using This = UsdSemanticsLabelsQuery;
    class_<This, noncopyable>("LabelsQuery", no_init)
        .def(init<const TfToken&, UsdTimeCode>(
             (arg("taxonomy"), arg("timeCode"))))
        .def(init<const TfToken&, const GfInterval&>(
             (arg("taxonomy"), arg("timeInterval"))))
        .def("__repr__", &::_Repr)
        .def("ComputeUniqueDirectLabels", &This::ComputeUniqueDirectLabels)
        .def("ComputeUniqueInheritedLabels",
             &This::ComputeUniqueInheritedLabels)
        .def("HasDirectLabel", &This::HasDirectLabel)
        .def("HasInheritedLabel", &This::HasInheritedLabel)
        .def("GetTaxonomy", 
               static_cast<const TfToken&(UsdSemanticsLabelsQuery::*)() const &>
                    (&UsdSemanticsLabelsQuery::GetTaxonomy),
                         return_value_policy<return_by_value>());
}
