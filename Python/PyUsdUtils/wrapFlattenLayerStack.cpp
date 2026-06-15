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

#include "UsdUtils/flattenLayerStack.h"
#include "Sdf/layer.h"
#include "Tf/pyFunction.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/makePyConstructor.h"

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

static
SdfLayerRefPtr
_UsdUtilsFlattenLayerStack2(
    const UsdStagePtr &stage, 
    const std::string& tag)
{
    return UsdUtilsFlattenLayerStack(stage, tag);
}

using Py_UsdUtilsResolveAssetPathSig = std::string(const SdfLayerHandle&, const std::string&);
using Py_UsdUtilsResolveAssetPathFn = std::function<Py_UsdUtilsResolveAssetPathSig>;

static
SdfLayerRefPtr
_UsdUtilsFlattenLayerStack3(
    const UsdStagePtr &stage,
    const Py_UsdUtilsResolveAssetPathFn& resolveAssetPathFn,
    const std::string& tag)
{
    return UsdUtilsFlattenLayerStack(stage, resolveAssetPathFn, tag);
}

void wrapFlattenLayerStack()
{
    def("FlattenLayerStack",
        &_UsdUtilsFlattenLayerStack2,
        (arg("stage"), arg("tag")=std::string()),
        pxr_boost::python::return_value_policy<
        TfPyRefPtrFactory<SdfLayerHandle> >());

    TfPyFunctionFromPython<Py_UsdUtilsResolveAssetPathSig>();
    def("FlattenLayerStack",
        &_UsdUtilsFlattenLayerStack3,
        (arg("stage"), arg("resolveAssetPathFn"), arg("tag")=std::string()),
        pxr_boost::python::return_value_policy<
        TfPyRefPtrFactory<SdfLayerHandle> >());

    def("FlattenLayerStackResolveAssetPath",
        UsdUtilsFlattenLayerStackResolveAssetPath,
        (arg("sourceLayer"), arg("assetPath")));
}
