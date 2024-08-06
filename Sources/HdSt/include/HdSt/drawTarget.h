//
// Copyright 2017 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_ST_DRAW_TARGET_H
#define PXR_IMAGING_HD_ST_DRAW_TARGET_H

#include "Hd/rprimCollection.h"
#include "Hd/sprim.h"
#include "HdSt/api.h"
#include "HdSt/drawTargetRenderPassState.h"
#include "pxr/pxrns.h"

#include "Gf/vec2i.h"
#include "Sdf/path.h"
#include "Tf/staticTokens.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

#define HDST_DRAW_TARGET_TOKENS \
  (camera)(collection)(drawTargetSet)(enable)(resolution)(aovBindings)(depthPriority)

TF_DECLARE_PUBLIC_TOKENS(HdStDrawTargetTokens, HDST_API, HDST_DRAW_TARGET_TOKENS);

class HdCamera;
class HdRenderIndex;
using HdStDrawTargetPtrVector = std::vector<class HdStDrawTarget *>;

/// \class HdStDrawTarget
///
/// Represents an render to texture render pass.
///
/// \note This is a temporary API to aid transition to Storm, and is subject
/// to major changes.
///
class HdStDrawTarget : public HdSprim {
 public:
  HDST_API
  HdStDrawTarget(SdfPath const &id);
  HDST_API
  ~HdStDrawTarget() override;

  /// Dirty bits for the HdStDrawTarget object
  ///
  /// When GetUseStormTextureSystem() is true, "Legacy" dirty
  /// bits are ignored.
  ///
  enum DirtyBits : HdDirtyBits {
    Clean = 0,
    DirtyDTEnable = 1 << 0,
    DirtyDTCamera = 1 << 1,
    DirtyDTResolution = 1 << 2,
    DirtyDTAovBindings = 1 << 4,
    DirtyDTDepthPriority = 1 << 6,
    DirtyDTCollection = 1 << 7,
    AllDirty = (DirtyDTEnable | DirtyDTCamera | DirtyDTResolution | DirtyDTAovBindings |
                DirtyDTDepthPriority | DirtyDTCollection)
  };

  /// Synchronizes state from the delegate to this object.
  HDST_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  /// Returns the minimal set of dirty bits to place in the
  /// change tracker for use in the first sync of this prim.
  /// Typically this would be all dirty bits.
  HDST_API
  HdDirtyBits GetInitialDirtyBitsMask() const override;

  // ---------------------------------------------------------------------- //
  /// \name Draw Target API
  // ---------------------------------------------------------------------- //
  bool IsEnabled() const
  {
    return _enabled;
  }
  const HdStDrawTargetRenderPassState *GetDrawTargetRenderPassState() const
  {
    return &_drawTargetRenderPassState;
  }

  /// Returns collection of rprims the draw target draws.
  HDST_API
  HdRprimCollection const &GetCollection() const
  {
    return _collection;
  }

  /// returns all HdStDrawTargets in the render index
  HDST_API
  static void GetDrawTargets(HdRenderIndex *renderIndex, HdStDrawTargetPtrVector *drawTargets);

  /// Resolution.
  ///
  /// Set during sync.
  ///
  const GfVec2i &GetResolution() const
  {
    return _resolution;
  }

 private:
  bool _enabled;
  GfVec2i _resolution;
  HdRprimCollection _collection;

  HdStDrawTargetRenderPassState _drawTargetRenderPassState;

  // No copy
  HdStDrawTarget() = delete;
  HdStDrawTarget(const HdStDrawTarget &) = delete;
  HdStDrawTarget &operator=(const HdStDrawTarget &) = delete;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_ST_DRAW_TARGET_H
