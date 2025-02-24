//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
///
/// \file usdUtils/wrapDependencies.cpp

#include "pxr/pxrns.h"
#include <boost/python/def.hpp>
#include <boost/python/list.hpp>
#include <boost/python/tuple.hpp>

#include "Tf/makePyConstructor.h"
#include "Tf/pyFunction.h"
#include "Tf/pyResultConversions.h"

#include "Sdf/assetPath.h"
#include "UsdUtils/dependencies.h"

namespace bp = boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static bp::tuple _ExtractExternalReferences(const std::string &filePath)
{
  std::vector<std::string> subLayers, references, payloads;
  UsdUtilsExtractExternalReferences(filePath, &subLayers, &references, &payloads);
  return bp::make_tuple(subLayers, references, payloads);
}

// Helper for creating a python object holding a layer ref ptr.
bp::object _LayerRefToObj(const SdfLayerRefPtr &layer)
{
  using RefPtrFactory = Tf_MakePyConstructor::RefPtrFactory<>::apply<SdfLayerRefPtr>::type;
  return bp::object(bp::handle<>(RefPtrFactory()(layer)));
}

static bp::tuple _ComputeAllDependencies(const SdfAssetPath &assetPath,
                                         std::function<UsdUtilsProcessingFunc> processingFunc)
{
  std::vector<SdfLayerRefPtr> layers;
  std::vector<std::string> assets, unresolvedPaths;

  UsdUtilsComputeAllDependencies(assetPath, &layers, &assets, &unresolvedPaths, processingFunc);
  bp::list layersList;
  for (auto &l : layers) {
    layersList.append(_LayerRefToObj(l));
  }
  return bp::make_tuple(layersList, assets, unresolvedPaths);
}

}  // anonymous namespace

void wrapDependencies()
{
  bp::def("ExtractExternalReferences", _ExtractExternalReferences, bp::arg("filePath"));

  bp::def("CreateNewUsdzPackage",
          UsdUtilsCreateNewUsdzPackage,
          (bp::arg("assetPath"),
           bp::arg("usdzFilePath"),
           bp::arg("firstLayerName") = std::string(),
           bp::arg("editLayersInPlace") = false));

  bp::def("CreateNewARKitUsdzPackage",
          UsdUtilsCreateNewARKitUsdzPackage,
          (bp::arg("assetPath"),
           bp::arg("usdzFilePath"),
           bp::arg("firstLayerName") = std::string(),
           bp::arg("editLayersInPlace") = false));

  bp::def("ComputeAllDependencies",
          _ComputeAllDependencies,
          (bp::arg("assetPath"), bp::arg("processingFunc") = bp::object()));

  using Py_UsdUtilsModifyAssetPathFn = std::string(const std::string &);
  TfPyFunctionFromPython<Py_UsdUtilsModifyAssetPathFn>();
  bp::def("ModifyAssetPaths",
          &UsdUtilsModifyAssetPaths,
          (bp::arg("layer"), bp::arg("modifyFn"), bp::arg("keepEmptyPathsInArrays") = false));
}
