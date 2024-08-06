//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include <boost/python/def.hpp>
#include <boost/python/return_value_policy.hpp>
#include <boost/python/tuple.hpp>

#include "UsdUtils/authoring.h"

#include "Sdf/layer.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

static std::vector<UsdCollectionAPI> _WrapUsdUtilsCreateCollections(
    const boost::python::list &assignments,
    const UsdPrim &usdPrim,
    const double minInclusionRatio,
    const unsigned int maxNumExcludesBelowInclude,
    const unsigned int minIncludeExcludeCollectionSize)
{
  // Create an stl vector with the required data from the python list.
  std::vector<std::pair<TfToken, SdfPathSet>> assignmentsVec;
  size_t nPairs = len(assignments);
  assignmentsVec.resize(nPairs);

  for (size_t i = 0; i < nPairs; ++i) {
    tuple pair = extract<tuple>(assignments[i]);
    TfToken collName = extract<TfToken>(pair[0]);
    list pathList = extract<list>(pair[1]);

    SdfPathSet includedPaths;
    size_t numPaths = len(pathList);
    for (size_t pathIdx = 0; pathIdx < numPaths; ++pathIdx) {
      SdfPath includedPath = extract<SdfPath>(pathList[pathIdx]);
      includedPaths.insert(includedPath);
    }
    assignmentsVec[i] = std::make_pair(collName, includedPaths);
  }

  return UsdUtilsCreateCollections(assignmentsVec,
                                   usdPrim,
                                   minInclusionRatio,
                                   maxNumExcludesBelowInclude,
                                   minIncludeExcludeCollectionSize);
}

static object _WrapUsdUtilsComputeCollectionIncludesAndExcludes(
    const SdfPathSet &includedRootPaths,
    const UsdStageWeakPtr &usdStage,
    double minInclusionRatio,
    const unsigned int maxNumExcludesBelowInclude,
    const unsigned int minIncludeExcludeCollectionSize,
    const SdfPathVector &pathsToIgnore)
{
  // The pathsToIgnore parameter is an SdfPathVector instead of an SdfPathSet
  // because we have to convert it into a hash set anyways. This lets us
  // accept both Python sets and lists, but without creating a temporary
  // std::set.
  UsdUtilsPathHashSet pathsToIgnoreSet;
  pathsToIgnoreSet.insert(pathsToIgnore.begin(), pathsToIgnore.end());

  SdfPathVector pathsToInclude;
  SdfPathVector pathsToExclude;

  UsdUtilsComputeCollectionIncludesAndExcludes(includedRootPaths,
                                               usdStage,
                                               &pathsToInclude,
                                               &pathsToExclude,
                                               minInclusionRatio,
                                               maxNumExcludesBelowInclude,
                                               minIncludeExcludeCollectionSize,
                                               pathsToIgnoreSet);

  return boost::python::make_tuple(pathsToInclude, pathsToExclude);
}

void wrapAuthoring()
{
  def("CopyLayerMetadata",
      UsdUtilsCopyLayerMetadata,
      (arg("source"),
       arg("destination"),
       arg("skipSublayers") = false,
       arg("bakeUnauthoredFallbacks") = false));

  def("ComputeCollectionIncludesAndExcludes",
      &_WrapUsdUtilsComputeCollectionIncludesAndExcludes,
      (arg("includedRootPaths"),
       arg("usdStage"),
       arg("minInclusionRatio") = 0.75,
       arg("maxNumExcludesBelowInclude") = 5u,
       arg("minIncludeExcludeCollectionSize") = 3u,
       arg("pathsToIgnore") = SdfPathVector()));

  def("AuthorCollection",
      UsdUtilsAuthorCollection,
      (arg("collectionName"),
       arg("usdPrim"),
       arg("pathsToInclude"),
       arg("pathsToExclude") = SdfPathSet()));

  def("CreateCollections",
      _WrapUsdUtilsCreateCollections,
      boost::python::return_value_policy<TfPySequenceToList>(),
      (arg("assignments"),
       arg("usdPrim"),
       arg("minInclusionRatio") = 0.75,
       arg("maxNumExcludesBelowInclude") = 5u,
       arg("minIncludeExcludeCollectionSize") = 3u));

  def("GetDirtyLayers",
      UsdUtilsGetDirtyLayers,
      (arg("stage"), arg("includeClipLayers") = true),
      return_value_policy<TfPySequenceToList>());
}
