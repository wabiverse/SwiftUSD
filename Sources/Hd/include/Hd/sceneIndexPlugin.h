//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_SCENE_INDEX_PLUGIN_H

#include "Hd/api.h"
#include "Hd/sceneIndex.h"
#include "Hf/pluginBase.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSceneIndexPlugin : public HfPluginBase {
 public:
  HD_API
  HdSceneIndexBaseRefPtr AppendSceneIndex(const HdSceneIndexBaseRefPtr &inputScene,
                                          const HdContainerDataSourceHandle &inputArgs);

 protected:
  /// Subclasses implement this to instantiate one or more scene indicies
  /// which take the provided scene as input. The return value should be
  /// the final scene created -- or the inputScene itself if nothing is
  /// created.
  HD_API
  virtual HdSceneIndexBaseRefPtr _AppendSceneIndex(const HdSceneIndexBaseRefPtr &inputScene,
                                                   const HdContainerDataSourceHandle &inputArgs);

  HdSceneIndexPlugin() = default;
  HD_API
  ~HdSceneIndexPlugin() override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_SCENE_INDEX_PLUGIN_H
