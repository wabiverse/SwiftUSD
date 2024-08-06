//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_GP_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_GP_SCENE_INDEX_PLUGIN_H

#include "Hd/sceneIndexPlugin.h"
#include "Hd/sceneIndexPluginRegistry.h"
#include "Tf/envSetting.h"

PXR_NAMESPACE_OPEN_SCOPE

extern TfEnvSetting<bool> HDGP_INCLUDE_DEFAULT_RESOLVER;

/// \class HdGpSceneIndexPlugin
///
/// HdGpSceneIndexPlugin provides HdSceneIndexPluginRegistry access to
/// instantiate HdGpGenerativeProceduralResolvingSceneIndex either directly
/// or automatically via RegisterSceneIndexForRenderer.
///
class HdGpSceneIndexPlugin : public HdSceneIndexPlugin {
 public:
  static const HdSceneIndexPluginRegistry::InsertionPhase GetInsertionPhase()
  {
    // XXX Until we have a better way to declare ordering/dependencies b/w
    //     scene index plugins, allow plugins to run before and after this
    //     plugin (i.e., don't use 0).
    return 2;
  }

  HdGpSceneIndexPlugin();

 protected:
  HdSceneIndexBaseRefPtr _AppendSceneIndex(const HdSceneIndexBaseRefPtr &inputScene,
                                           const HdContainerDataSourceHandle &inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
