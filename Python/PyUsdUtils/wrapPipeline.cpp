//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "UsdUtils/pipeline.h"

#include "Sdf/booleanExpression.h"
#include "Usd/prim.h"

#include "Tf/pyResultConversions.h"
#include "Vt/dictionary.h"
#include "Vt/value.h"
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_by_value.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

// XXX: Temporary workaround for use by UpdateSchemaWithSdrNode(). Once
// SdfBooleanExpression is wrapped to Python we can do away with this.
static std::string
_BooleanExpressionRenameVariables(
    const std::string& expr,
    const VtDictionary& renames)
{
    auto transform = [&](const TfToken& name) {
        const auto it = renames.find(name);
        if (it == renames.end() || !it->second.IsHolding<std::string>()) {
            return name;
        }
        else {
            return TfToken(it->second.UncheckedGet<std::string>());
        }
    };

    const SdfBooleanExpression expression(expr);
    return expression.RenameVariables(transform).GetText();
}

void wrapPipeline()
{
    def("GetAlphaAttributeNameForColor", UsdUtilsGetAlphaAttributeNameForColor, arg("colorAttrName"));
    def("GetModelNameFromRootLayer", UsdUtilsGetModelNameFromRootLayer);
    def("GetRegisteredVariantSets", 
            UsdUtilsGetRegisteredVariantSets, 
            return_value_policy<TfPySequenceToList>());
    def("GetPrimAtPathWithForwarding", UsdUtilsGetPrimAtPathWithForwarding, 
        (arg("stage"), arg("path")));
    def("UninstancePrimAtPath", UsdUtilsUninstancePrimAtPath, 
        (arg("stage"), arg("path")));
    def("GetPrimaryUVSetName", UsdUtilsGetPrimaryUVSetName,
        return_value_policy<return_by_value>());
    def("GetPrefName", UsdUtilsGetPrefName,
        return_value_policy<return_by_value>());
    def(
        "GetMaterialsScopeName",
        UsdUtilsGetMaterialsScopeName,
        arg("forceDefault")=false);
    def(
        "GetPrimaryCameraName",
        UsdUtilsGetPrimaryCameraName,
        arg("forceDefault")=false);

    def("_BooleanExpressionRenameVariables",
        &_BooleanExpressionRenameVariables);
}
