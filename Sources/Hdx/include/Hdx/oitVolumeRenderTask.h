//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDX_OIT_VOLUME_RENDER_TASK_H
#define PXR_IMAGING_HDX_OIT_VOLUME_RENDER_TASK_H

#include "Hdx/api.h"
#include "Hdx/renderTask.h"
#include "Hdx/version.h"
#include "pxr/pxrns.h"

#include "HdSt/renderPassState.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdxOitVolumeRenderTask
///
/// A task for rendering transparent geometry into OIT buffers.
/// Its companion task, OITResolveTask, will blend the buffers to screen.
///
class HdxOitVolumeRenderTask : public HdxRenderTask {
 public:
  HDX_API
  HdxOitVolumeRenderTask(HdSceneDelegate *delegate, SdfPath const &id);

  HDX_API
  ~HdxOitVolumeRenderTask() override;

  /// Prepare the tasks resources
  HDX_API
  void Prepare(HdTaskContext *ctx, HdRenderIndex *renderIndex) override;

  /// Execute render pass task
  HDX_API
  void Execute(HdTaskContext *ctx) override;

 protected:
  /// Sync the render pass resources
  HDX_API
  void _Sync(HdSceneDelegate *delegate, HdTaskContext *ctx, HdDirtyBits *dirtyBits) override;

 private:
  HdxOitVolumeRenderTask() = delete;
  HdxOitVolumeRenderTask(const HdxOitVolumeRenderTask &) = delete;
  HdxOitVolumeRenderTask &operator=(const HdxOitVolumeRenderTask &) = delete;

  HdStRenderPassShaderSharedPtr _oitVolumeRenderPassShader;
  const bool _isOitEnabled;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HDX_OIT_VOLUME_RENDER_TASK_H
