//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.

#ifndef PXR_IMAGING_HD_ST_DEPENDENCY_FORWARDING_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_ST_DEPENDENCY_FORWARDING_SCENE_INDEX_PLUGIN_H

#include "Hd/sceneIndexPlugin.h"
#include "HdSt/api.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdSt_DependencyForwardingSceneIndexPlugin
///
/// Plugin adds a dependency forwarding scene index to the Storm render
/// delegate to resolve any dependencies introduced by other scene indices.
///
class HdSt_DependencyForwardingSceneIndexPlugin : public HdSceneIndexPlugin {
 public:
  HdSt_DependencyForwardingSceneIndexPlugin();

 protected:
  HdSceneIndexBaseRefPtr _AppendSceneIndex(const HdSceneIndexBaseRefPtr &inputScene,
                                           const HdContainerDataSourceHandle &inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_DEPENDENCY_FORWARDING_SCENE_INDEX_PLUGIN_H
