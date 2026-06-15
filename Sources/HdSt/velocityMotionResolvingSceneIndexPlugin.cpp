//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "HdSt/velocityMotionResolvingSceneIndexPlugin.h"

#include "Hd/dataSource.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneIndexObserver.h"
#include "Hd/sceneIndexPlugin.h"
#include "Hd/sceneIndexPluginRegistry.h"
#include "Hdsi/velocityMotionResolvingSceneIndex.h"

#include "Tf/registryManager.h"
#include "Tf/staticTokens.h"
#include "Tf/type.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,
    (fps)
    ((sceneIndexPluginName, "HdSt_VelocityMotionResolvingSceneIndexPlugin")));

static const char* const _pluginDisplayName = "GL";

TF_REGISTRY_FUNCTION(TfType)
{
    HdSceneIndexPluginRegistry::Define<HdSt_VelocityMotionResolvingSceneIndexPlugin>();
}

TF_REGISTRY_FUNCTION(HdSceneIndexPlugin)
{
    // This one should go after implicit surface conversion
    static const HdSceneIndexPluginRegistry::InsertionPhase insertionPhase = 0;
    
    HdSceneIndexPluginRegistry::GetInstance().RegisterSceneIndexForRenderer(
        _pluginDisplayName,
        _tokens->sceneIndexPluginName,
        /* inputArgs = */ nullptr, 
        insertionPhase,
        HdSceneIndexPluginRegistry::InsertionOrderAtEnd);
}

HdSt_VelocityMotionResolvingSceneIndexPlugin::
HdSt_VelocityMotionResolvingSceneIndexPlugin() = default;

HdSceneIndexBaseRefPtr
HdSt_VelocityMotionResolvingSceneIndexPlugin::_AppendSceneIndex(
    const HdSceneIndexBaseRefPtr& inputScene,
    const HdContainerDataSourceHandle& inputArgs)
{
    // Define inputArgs here instead of in the TF_REGISTRY_FUNCTION block.
    // In the future, we may consider renaming the inputArgs parameter to
    // something like "sceneIndexGraphCreateArgs" to allow the app and renderer
    // plugin to provide arguments for scene indices instantiated via the
    // scene index plugin system.
    const HdContainerDataSourceHandle localInputArgs = 
        HdRetainedContainerDataSource::New(
            _tokens->fps,
            // TODO: Get real framerate!
            HdRetainedTypedSampledDataSource<float>::New(24.0));

    return HdsiVelocityMotionResolvingSceneIndex::New(
        inputScene, localInputArgs);
}

PXR_NAMESPACE_CLOSE_SCOPE
