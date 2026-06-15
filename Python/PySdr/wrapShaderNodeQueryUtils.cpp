//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Vt/value.h"
#include "Vt/dictionary.h"
#include "Sdr/shaderNodeQueryUtils.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_internal_reference.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

// Python has no equivalent notion of namespaces in C++, so
// use an empty class as a namespace standin for Python.
class _SdrShaderNodeQueryUtils{};

/// Recursive function to help construct arbitrarily nested Python dicts
/// from the return value of SdrShaderNodeQueryUtils::GroupQueryResults.
object
_GroupQueryResultsHelper(const VtValue& subgroup) {
    dict ret;
    if (subgroup.IsHolding<SdrShaderNodeConstPtrVec>()) {
        list l;
        for (auto node: subgroup.UncheckedGet<SdrShaderNodeConstPtrVec>()) {
            l.append(ptr(node));
        }
        return l;
    } else if (subgroup.IsHolding<VtDictionary>()) {
        const VtDictionary& innerDict = subgroup.UncheckedGet<VtDictionary>();
        for (auto& entry : innerDict) {
            ret[entry.first] = _GroupQueryResultsHelper(entry.second);
        }
    } else {
        TF_VERIFY(false, "Invalid VtValue subgroup (%s) from "
                  "SdrShaderNodeQueryUtils::GroupQueryResults",
                  TfStringify(subgroup).c_str());
    }
    return ret;
}

/// Without this wrapper to call `ptr(node)`, Boost Python will attempt to
/// copy interior SdrShaderNodeConstPtr by-value as a SdrShaderNode.
object
_GroupQueryResults(const SdrShaderNodeQueryResult& result) {
    VtDictionary group = SdrShaderNodeQueryUtils::GroupQueryResults(result);
    return _GroupQueryResultsHelper(VtValue(group));
}

} // anonymous namespace

void wrapShaderNodeQueryUtils()
{
    class_<_SdrShaderNodeQueryUtils>("ShaderNodeQueryUtils", no_init)
        .def("GroupQueryResults", _GroupQueryResults);
}