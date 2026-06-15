//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_ST_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_PLUGIN_H

#include "Hd/dataSource.h"
#include "Hd/sceneIndexObserver.h"
#include "Hd/sceneIndexPlugin.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSt_VelocityMotionResolvingSceneIndexPlugin : public HdSceneIndexPlugin
{
public:
    HdSt_VelocityMotionResolvingSceneIndexPlugin();

protected:
    HdSceneIndexBaseRefPtr _AppendSceneIndex(
        const HdSceneIndexBaseRefPtr &inputScene,
        const HdContainerDataSourceHandle &inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_HD_ST_VELOCITY_MOTION_RESOLVING_SCENE_INDEX_PLUGIN_H
