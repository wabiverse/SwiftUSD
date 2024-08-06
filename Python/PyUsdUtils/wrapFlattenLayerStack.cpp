//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include <boost/python/def.hpp>

#include "Sdf/layer.h"
#include "Tf/makePyConstructor.h"
#include "Tf/pyFunction.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"
#include "UsdUtils/flattenLayerStack.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static SdfLayerRefPtr _UsdUtilsFlattenLayerStack2(const UsdStagePtr &stage, const std::string &tag)
{
  return UsdUtilsFlattenLayerStack(stage, tag);
}

using Py_UsdUtilsResolveAssetPathSig = std::string(const SdfLayerHandle &, const std::string &);
using Py_UsdUtilsResolveAssetPathFn = std::function<Py_UsdUtilsResolveAssetPathSig>;

static SdfLayerRefPtr _UsdUtilsFlattenLayerStack3(
    const UsdStagePtr &stage,
    const Py_UsdUtilsResolveAssetPathFn &resolveAssetPathFn,
    const std::string &tag)
{
  return UsdUtilsFlattenLayerStack(stage, resolveAssetPathFn, tag);
}

void wrapFlattenLayerStack()
{
  def("FlattenLayerStack",
      &_UsdUtilsFlattenLayerStack2,
      (arg("stage"), arg("tag") = std::string()),
      boost::python::return_value_policy<TfPyRefPtrFactory<SdfLayerHandle>>());

  TfPyFunctionFromPython<Py_UsdUtilsResolveAssetPathSig>();
  def("FlattenLayerStack",
      &_UsdUtilsFlattenLayerStack3,
      (arg("stage"), arg("resolveAssetPathFn"), arg("tag") = std::string()),
      boost::python::return_value_policy<TfPyRefPtrFactory<SdfLayerHandle>>());

  def("FlattenLayerStackResolveAssetPath",
      UsdUtilsFlattenLayerStackResolveAssetPath,
      (arg("sourceLayer"), arg("assetPath")));
}
