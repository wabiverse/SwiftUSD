//
// Copyright 2025 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkelImaging/resolvingSceneIndexPlugin.h"

#include "UsdSkelImaging/pointsResolvingSceneIndex.h"
#include "UsdSkelImaging/bindingSchema.h"
#include "UsdSkelImaging/skeletonResolvingSceneIndex.h"

#include "Hd/flattenedDataSourceProviders.h"
#include "Hd/flattenedOverlayDataSourceProvider.h"
#include "Hd/primvarsSchema.h"
#include "Hd/skinningSettings.h"

#include "Hd/retainedDataSource.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(UsdImagingSceneIndexPlugin)
{
    UsdImagingSceneIndexPlugin::Define<
        UsdSkelImagingResolvingSceneIndexPlugin>();
}

HdSceneIndexBaseRefPtr
UsdSkelImagingResolvingSceneIndexPlugin::AppendSceneIndex(
    HdSceneIndexBaseRefPtr const &inputScene)
{
    HdSceneIndexBaseRefPtr sceneIndex = inputScene;

    sceneIndex =
        UsdSkelImagingSkeletonResolvingSceneIndex::New(sceneIndex);

    sceneIndex =
        UsdSkelImagingPointsResolvingSceneIndex::New(sceneIndex);

    return sceneIndex;
}

HdContainerDataSourceHandle
UsdSkelImagingResolvingSceneIndexPlugin::FlattenedDataSourceProviders()
{
    using namespace HdMakeDataSourceContainingFlattenedDataSourceProvider;

    return HdRetainedContainerDataSource::New(
        UsdSkelImagingBindingSchema::GetSchemaToken(),
        Make<HdFlattenedOverlayDataSourceProvider>());
}

TfTokenVector
UsdSkelImagingResolvingSceneIndexPlugin::InstanceDataSourceNames()
{
    return {
        UsdSkelImagingBindingSchema::GetSchemaToken()
    };
}

TfTokenVector
UsdSkelImagingResolvingSceneIndexPlugin::ProxyPathTranslationDataSourceNames()
{
    static const TfTokenVector bindingSchemaToken{
        UsdSkelImagingBindingSchema::GetSchemaToken()
    };
    if (!HdSkinningSettings::IsSkinningDeferred()) {
        return bindingSchemaToken;
    }

    // skelBinding:animationSource is relocated and aggregated as an instance
    // primvar on the instancer when skinning is deferred so we will need to
    // translate that. We should revisit if scanning through all the primvars
    // becomes a performance bottleneck. We can then maybe add a new
    // ProxyPathTranslationPrimvarNames() method.
    static const TfTokenVector bindingPrimvarsSchemaToken{
        UsdSkelImagingBindingSchema::GetSchemaToken(),
        HdPrimvarsSchema::GetSchemaToken()
    };
    return bindingPrimvarsSchemaToken;
}

PXR_NAMESPACE_CLOSE_SCOPE
