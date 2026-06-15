//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include "Arch/pragmas.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include "Usd/flattenUtils.h"
#include "Sdf/layer.h"
#include "Tf/pyFunction.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/makePyConstructor.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static
SdfLayerRefPtr
_UsdFlattenLayerStack2(
    const PcpLayerStackRefPtr &layerStack,
    const std::string& tag)
{
    return UsdFlattenLayerStack(layerStack, tag);
}

using Py_UsdFlattenResolveAssetPathSig = 
    std::string(const SdfLayerHandle&, const std::string&);
using Py_UsdFlattenResolveAssetPathFn = 
    std::function<Py_UsdFlattenResolveAssetPathSig>;

static
SdfLayerRefPtr
_UsdFlattenLayerStack3(
    const PcpLayerStackRefPtr &layerStack,
    const Py_UsdFlattenResolveAssetPathFn& resolveAssetPathFn,
    const std::string& tag)
{
    return UsdFlattenLayerStack(layerStack, resolveAssetPathFn, tag);
}

void wrapUsdFlattenUtils()
{
    def("FlattenLayerStack",
        &_UsdFlattenLayerStack2,
        (arg("layerStack"), arg("tag")=std::string()),
        pxr_boost::python::return_value_policy<
        TfPyRefPtrFactory<SdfLayerHandle> >());

    TfPyFunctionFromPython<Py_UsdFlattenResolveAssetPathSig>();
    def("FlattenLayerStack",
        &_UsdFlattenLayerStack3,
        (arg("layerStack"), arg("resolveAssetPathFn"), arg("tag")=std::string()),
        pxr_boost::python::return_value_policy<
        TfPyRefPtrFactory<SdfLayerHandle> >());

    def("FlattenLayerStackResolveAssetPath",
        UsdFlattenLayerStackResolveAssetPath,
        (arg("sourceLayer"), arg("assetPath")));

    using Context = UsdFlattenResolveAssetPathContext;
    class_<Context>
        ("FlattenResolveAssetPathContext", no_init)
        .add_property("sourceLayer", 
            +[](const Context& c) { return c.sourceLayer; })
        .add_property("assetPath", 
            +[](const Context& c) { return c.assetPath; })
        .add_property("expressionVariables", 
            +[](const Context& c) { return c.expressionVariables; })
        ;

    using Py_UsdFlattenResolveAssetPathAdvancedSig =
        std::string(const UsdFlattenResolveAssetPathContext&);

    TfPyFunctionFromPython<Py_UsdFlattenResolveAssetPathAdvancedSig>();

    // This function requires a different name to distinguish itself
    // from the other FlattenLayerStack function that also takes a
    // callback because TfPyFunctionFromFunction doesn't let us
    // distinguish between the two different callback types.
    def("FlattenLayerStackAdvanced",
        (SdfLayerRefPtr(*)(
            const PcpLayerStackRefPtr&,
            const UsdFlattenResolveAssetPathAdvancedFn&,
            const std::string&))&UsdFlattenLayerStack,
        (arg("layerStack"), arg("resolveAssetPathFn"), 
            arg("tag")=std::string()),
        return_value_policy<TfPyRefPtrFactory<SdfLayerHandle>>());

    def("FlattenLayerStackResolveAssetPathAdvanced",
        &UsdFlattenLayerStackResolveAssetPathAdvanced,
        (arg("context")));
}
