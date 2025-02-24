//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdUtils/introspection.h"
#include "pxr/pxrns.h"

#include "Kind/registry.h"

#include "Usd/modelAPI.h"
#include "Usd/prim.h"
#include "Usd/primRange.h"

#include "Tf/stringUtils.h"
#include "Tf/token.h"

#include <set>
#include <string>
#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

using std::string;

TF_DEFINE_PUBLIC_TOKENS(UsdUtilsUsdStageStatsKeys, USDUTILS_USDSTAGE_STATS);

UsdStageRefPtr UsdUtilsComputeUsdStageStats(const std::string &rootLayerPath, VtDictionary *stats)
{
  double startMem = 0.0, endMem = 0.0;
  if (TfMallocTag::IsInitialized()) {
    startMem = TfMallocTag::GetTotalBytes() / (1024.0 * 1024.0);
  }

  UsdStageRefPtr stage = UsdStage::Open(rootLayerPath, UsdStage::InitialLoadSet::LoadAll);
  if (!stage)
    return nullptr;

  if (TfMallocTag::IsInitialized()) {
    endMem = TfMallocTag::GetTotalBytes() / (1024.0 * 1024.0);
    (*stats)[UsdUtilsUsdStageStatsKeys->approxMemoryInMb] = endMem - startMem;
  }

  UsdUtilsComputeUsdStageStats(stage, stats);

  return stage;
}

static void _UpdateCountsHelper(
    const UsdPrim &prim,
    std::set<string> *seenAssetNames,
    size_t *totalPrimCount,
    size_t *subTotalPrimCount,
    size_t *modelCount,
    size_t *instancedModelCount,
    size_t *assetCount,
    size_t *activePrimCount,
    size_t *inactivePrimCount,
    size_t *pureOverCount,
    size_t *instanceCount,
    std::unordered_map<TfToken, size_t, TfToken::HashFunctor> *primCountsByType)
{
  if (!prim)
    return;

  ++(*totalPrimCount);
  ++(*subTotalPrimCount);

  if (prim.IsModel()) {
    TfToken kind;
    // Only count if it is a component model.
    if (UsdModelAPI(prim).GetKind(&kind) && KindRegistry::IsA(kind, KindTokens->component)) {

      ++(*modelCount);
      if (prim.IsInstance()) {
        ++(*instancedModelCount);
      }

      string assetName;
      if (UsdModelAPI(prim).GetAssetName(&assetName)) {
        if (seenAssetNames->insert(assetName).second) {
          ++(*assetCount);
        }
      }
    }
  }

  (*instanceCount) += prim.IsInstance();
  (*activePrimCount) += prim.IsActive();
  (*inactivePrimCount) += !prim.IsActive();
  (*pureOverCount) += !prim.HasDefiningSpecifier();

  TfToken typeName = prim.GetTypeName().IsEmpty() ? UsdUtilsUsdStageStatsKeys->untyped :
                                                    prim.GetTypeName();
  if (primCountsByType->find(typeName) == primCountsByType->end()) {
    (*primCountsByType)[typeName] = 0;
  }
  ++((*primCountsByType)[typeName]);
}

size_t UsdUtilsComputeUsdStageStats(const UsdStageWeakPtr &stage, VtDictionary *stats)
{
  size_t usedLayerCount = stage->GetUsedLayers().size() - (size_t)(bool)(stage->GetSessionLayer());

  (*stats)[UsdUtilsUsdStageStatsKeys->usedLayerCount] = usedLayerCount;

  size_t totalPrimCount = 0, modelCount = 0, instancedModelCount = 0, assetCount = 0,
         prototypeCount = 0, totalInstanceCount = 0;

  size_t primaryPrimCount = 0, primaryActivePrimCount = 0, primaryInactivePrimCount = 0,
         primaryPureOverCount = 0, primaryInstanceCount = 0;

  typedef std::unordered_map<TfToken, size_t, TfToken::HashFunctor> PrimTypeAndCountMap;
  PrimTypeAndCountMap primCountsByType;

  std::set<string> seenAssetNames;
  for (UsdPrim prim : stage->TraverseAll()) {
    _UpdateCountsHelper(prim,
                        &seenAssetNames,
                        &totalPrimCount,
                        &primaryPrimCount,
                        &modelCount,
                        &instancedModelCount,
                        &assetCount,
                        &primaryActivePrimCount,
                        &primaryInactivePrimCount,
                        &primaryPureOverCount,
                        &primaryInstanceCount,
                        &primCountsByType);
  }
  totalInstanceCount = primaryInstanceCount;

  std::vector<UsdPrim> prototypes = stage->GetPrototypes();
  prototypeCount = prototypes.size();
  if (prototypeCount > 0) {
    size_t prototypesPrimCount = 0, prototypesActivePrimCount = 0, prototypesInactivePrimCount = 0,
           prototypesPureOverCount = 0, prototypesInstanceCount = 0;

    PrimTypeAndCountMap prototypesPrimCountsByType;

    for (const UsdPrim &prototypePrim : prototypes) {
      for (UsdPrim prim : UsdPrimRange(prototypePrim)) {
        _UpdateCountsHelper(prim,
                            &seenAssetNames,
                            &totalPrimCount,
                            &prototypesPrimCount,
                            &modelCount,
                            &instancedModelCount,
                            &assetCount,
                            &prototypesActivePrimCount,
                            &prototypesInactivePrimCount,
                            &prototypesPureOverCount,
                            &prototypesInstanceCount,
                            &prototypesPrimCountsByType);
      }
    }

    totalInstanceCount += prototypesInstanceCount;

    VtDictionary prototypesDict;

    VtDictionary primCounts;
    primCounts[UsdUtilsUsdStageStatsKeys->totalPrimCount] = prototypesPrimCount;
    primCounts[UsdUtilsUsdStageStatsKeys->activePrimCount] = prototypesActivePrimCount;
    primCounts[UsdUtilsUsdStageStatsKeys->inactivePrimCount] = prototypesInactivePrimCount;
    primCounts[UsdUtilsUsdStageStatsKeys->pureOverCount] = prototypesPureOverCount;
    primCounts[UsdUtilsUsdStageStatsKeys->instanceCount] = prototypesInstanceCount;

    prototypesDict[UsdUtilsUsdStageStatsKeys->primCounts] = primCounts;

    VtDictionary primCountsByTypeDict;
    for (const auto &typeNameAndCount : prototypesPrimCountsByType) {
      primCountsByTypeDict[typeNameAndCount.first] = typeNameAndCount.second;
    }
    prototypesDict[UsdUtilsUsdStageStatsKeys->primCountsByType] = primCountsByTypeDict;

    (*stats)[UsdUtilsUsdStageStatsKeys->prototypes] = prototypesDict;
  }

  (*stats)[UsdUtilsUsdStageStatsKeys->totalPrimCount] = totalPrimCount;
  (*stats)[UsdUtilsUsdStageStatsKeys->modelCount] = modelCount;
  (*stats)[UsdUtilsUsdStageStatsKeys->instancedModelCount] = instancedModelCount;
  (*stats)[UsdUtilsUsdStageStatsKeys->assetCount] = assetCount;
  (*stats)[UsdUtilsUsdStageStatsKeys->prototypeCount] = prototypeCount;
  (*stats)[UsdUtilsUsdStageStatsKeys->totalInstanceCount] = totalInstanceCount;

  // VtDictionary does not support initialization using an initializer list.
  VtDictionary primaryDict;

  VtDictionary primCounts;
  primCounts[UsdUtilsUsdStageStatsKeys->totalPrimCount] = primaryPrimCount;
  primCounts[UsdUtilsUsdStageStatsKeys->activePrimCount] = primaryActivePrimCount;
  primCounts[UsdUtilsUsdStageStatsKeys->inactivePrimCount] = primaryInactivePrimCount;
  primCounts[UsdUtilsUsdStageStatsKeys->pureOverCount] = primaryPureOverCount;
  primCounts[UsdUtilsUsdStageStatsKeys->instanceCount] = primaryInstanceCount;

  primaryDict[UsdUtilsUsdStageStatsKeys->primCounts] = primCounts;

  VtDictionary primCountsByTypeDict;
  for (const auto &typeNameAndCount : primCountsByType) {
    primCountsByTypeDict[typeNameAndCount.first] = typeNameAndCount.second;
  }
  primaryDict[UsdUtilsUsdStageStatsKeys->primCountsByType] = primCountsByTypeDict;

  (*stats)[UsdUtilsUsdStageStatsKeys->primary] = primaryDict;

  return totalPrimCount;
}

PXR_NAMESPACE_CLOSE_SCOPE
