//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.

#ifndef PXR_IMAGING_HD_ST_DEPENDENCY_SCENE_INDEX_PLUGIN_H
#define PXR_IMAGING_HD_ST_DEPENDENCY_SCENE_INDEX_PLUGIN_H

#include "Hd/sceneIndexPlugin.h"
#include "HdSt/api.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdSt_DependencySceneIndexPlugin
///
/// Plugin adds a scene index that declares Storm-specific dependencies to
/// trigger the necessary invalidation.
///
/// Currently, the lone usage is for volume prims.
///
/// Specfically, the declaration allows the volumeFieldBinding data source
/// locator of a volume prim to be invalidated if any of the targeted volume
/// fields changes.
/// That is, if, e.g., the filePath of a volume field changes, then the volume
/// using that volume field will be dirtied so that HdStVolume will update
/// which 3d textures it will use.
///
class HdSt_DependencySceneIndexPlugin : public HdSceneIndexPlugin {
 public:
  HdSt_DependencySceneIndexPlugin();

 protected:
  HdSceneIndexBaseRefPtr _AppendSceneIndex(const HdSceneIndexBaseRefPtr &inputScene,
                                           const HdContainerDataSourceHandle &inputArgs) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_DEPENDENCY_SCENE_INDEX_PLUGIN_H
