//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/sceneIndices.h"

#include "UsdImaging/drawModeSceneIndex.h"
#include "UsdImaging/extentResolvingSceneIndex.h"
#include "UsdImaging/flattenedDataSourceProviders.h"
#include "UsdImaging/materialBindingsResolvingSceneIndex.h"
#include "UsdImaging/niPrototypePropagatingSceneIndex.h"
#include "UsdImaging/piPrototypePropagatingSceneIndex.h"
#include "UsdImaging/renderSettingsFlatteningSceneIndex.h"
#include "UsdImaging/selectionSceneIndex.h"
#include "UsdImaging/stageSceneIndex.h"
#include "UsdImaging/unloadedDrawModeSceneIndex.h"

#include "UsdImaging/collectionMaterialBindingsSchema.h"
#include "UsdImaging/directMaterialBindingsSchema.h"
#include "UsdImaging/geomModelSchema.h"

#include "Hd/flatteningSceneIndex.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/purposeSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneIndexUtil.h"
#include "Hd/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

static HdContainerDataSourceHandle _AdditionalStageSceneIndexInputArgs(
    const bool displayUnloadedPrimsWithBounds)
{
  if (!displayUnloadedPrimsWithBounds) {
    return nullptr;
  }
  static HdContainerDataSourceHandle const ds = HdRetainedContainerDataSource::New(
      UsdImagingStageSceneIndexTokens->includeUnloadedPrims,
      HdRetainedTypedSampledDataSource<bool>::New(true));
  return ds;
}

// Use extentsHint (of models) for purpose geometry
static HdContainerDataSourceHandle _ExtentResolvingSceneIndexInputArgs()
{
  HdDataSourceBaseHandle const purposeDataSources[] = {
      HdRetainedTypedSampledDataSource<TfToken>::New(HdTokens->geometry)};

  return HdRetainedContainerDataSource::New(
      UsdImagingExtentResolvingSceneIndexTokens->purposes,
      HdRetainedSmallVectorDataSource::New(TfArraySize(purposeDataSources), purposeDataSources));
}

static std::string _GetStageName(UsdStageRefPtr const &stage)
{
  if (!stage) {
    return {};
  }
  SdfLayerHandle const rootLayer = stage->GetRootLayer();
  if (!rootLayer) {
    return {};
  }
  return rootLayer->GetIdentifier();
}

UsdImagingSceneIndices UsdImagingCreateSceneIndices(
    const UsdImagingCreateSceneIndicesInfo &createInfo)
{
  TRACE_FUNCTION();

  UsdImagingSceneIndices result;

  HdSceneIndexBaseRefPtr sceneIndex;

  sceneIndex = result.stageSceneIndex = UsdImagingStageSceneIndex::New(
      HdOverlayContainerDataSource::OverlayedContainerDataSources(
          _AdditionalStageSceneIndexInputArgs(createInfo.displayUnloadedPrimsWithBounds),
          createInfo.stageSceneIndexInputArgs));

  result.stageSceneIndex->SetStage(createInfo.stage);

  if (createInfo.overridesSceneIndexCallback) {
    sceneIndex = createInfo.overridesSceneIndexCallback(sceneIndex);
  }

  if (createInfo.displayUnloadedPrimsWithBounds) {
    sceneIndex = UsdImagingUnloadedDrawModeSceneIndex::New(sceneIndex);
  }

  sceneIndex = UsdImagingExtentResolvingSceneIndex::New(sceneIndex,
                                                        _ExtentResolvingSceneIndexInputArgs());

  {
    TRACE_FUNCTION_SCOPE("UsdImagingPiPrototypePropagatingSceneIndex");

    sceneIndex = UsdImagingPiPrototypePropagatingSceneIndex::New(sceneIndex);
  }

  {
    TRACE_FUNCTION_SCOPE("UsdImagingNiPrototypePropagatingSceneIndex");

    // UsdImagingNiPrototypePropagatingSceneIndex

    // Names of data sources that need to have the same values
    // across native instances for the instances be aggregated
    // together.
    static const TfTokenVector instanceDataSourceNames = {
        UsdImagingDirectMaterialBindingsSchema::GetSchemaToken(),
        UsdImagingCollectionMaterialBindingsSchema::GetSchemaToken(),
        HdPurposeSchema::GetSchemaToken(),
        // We include model to aggregate scene indices
        // by draw mode.
        UsdImagingGeomModelSchema::GetSchemaToken()};

    using SceneIndexAppendCallback =
        UsdImagingNiPrototypePropagatingSceneIndex::SceneIndexAppendCallback;

    // The draw mode scene index needs to be inserted multiple times
    // during prototype propagation because:
    // - A native instance can be grouped under a prim with non-trivial
    //   draw mode. In this case, the draw mode scene index needs to
    //   filter out the native instance before instance aggregation.
    // - A native instance itself can have a non-trivial draw mode.
    //   In this case, we want to aggregate the native instances
    //   with the same draw mode, so we need to run instance aggregation
    //   first.
    // - Advanced scenarios such as native instances in USD prototypes
    //   and the composition semantics of draw mode: the draw mode is
    //   inherited but apply draw mode is not and the draw mode is
    //   only applied when it is non-trivial and apply draw mode is true.
    //
    // Thus, we give the prototype propagating scene index a callback.
    //
    SceneIndexAppendCallback callback;
    if (createInfo.addDrawModeSceneIndex) {
      callback = [](HdSceneIndexBaseRefPtr const &inputSceneIndex) {
        return UsdImagingDrawModeSceneIndex::New(inputSceneIndex, /* inputArgs = */ nullptr);
      };
    }

    sceneIndex = UsdImagingNiPrototypePropagatingSceneIndex::New(
        sceneIndex, instanceDataSourceNames, callback);
  }

  sceneIndex = UsdImagingMaterialBindingsResolvingSceneIndex::New(sceneIndex,
                                                                  /* inputArgs = */ nullptr);

  sceneIndex = result.selectionSceneIndex = UsdImagingSelectionSceneIndex::New(sceneIndex);

  sceneIndex = UsdImagingRenderSettingsFlatteningSceneIndex::New(sceneIndex);

  if (TfGetEnvSetting<bool>(HD_USE_ENCAPSULATING_SCENE_INDICES)) {
    sceneIndex = HdMakeEncapsulatingSceneIndex({}, sceneIndex);
    sceneIndex->SetDisplayName("UsdImaging " + _GetStageName(createInfo.stage));
  }

  result.finalSceneIndex = sceneIndex;

  return result;
}

PXR_NAMESPACE_CLOSE_SCOPE
