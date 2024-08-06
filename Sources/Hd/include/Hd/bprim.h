//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_BPRIM_H
#define PXR_IMAGING_HD_BPRIM_H

#include "Hd/api.h"
#include "Hd/types.h"
#include "Hd/version.h"
#include "pxr/pxrns.h"

#include "Sdf/path.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSceneDelegate;
class HdRenderParam;

/// \class HdBprim
///
/// Bprim (buffer prim) is a base class of managing a blob of data that is
/// used to communicate between the scene delegate and render.
///
/// Like other prim types (Rprim and Sprim), the Bprim communicates with the
/// scene delegate got get buffer properties (e.g. the size of the buffer) as
/// well as the contents of the buffer.
///
/// Changes to the properties and contents are change tracked and updates
/// are cached in the renderer.  The Render Delegate may choose to transform
/// the data into a renderer specific form on download.
///
/// BPrims are sync'ed first and thus, Bprims should not be
/// Dependent on the state of any other prim.
///
/// The most typical use of a Bprim would be a Texture.
class HdBprim {
 public:
  HD_API
  HdBprim(SdfPath const &id);
  HD_API
  virtual ~HdBprim();

  /// Returns the identifier by which this buffer is known. This
  /// identifier is a common associative key used by the SceneDelegate,
  /// RenderIndex, and for binding to the buffer
  SdfPath const &GetId() const
  {
    return _id;
  }

  /// Synchronizes state from the delegate to this object.
  /// @param[in, out]  dirtyBits: On input specifies which state is
  ///                             is dirty and can be pulled from the scene
  ///                             delegate.
  ///                             On output specifies which bits are still
  ///                             dirty and were not cleaned by the sync.
  ///
  virtual void Sync(HdSceneDelegate *sceneDelegate,
                    HdRenderParam *renderParam,
                    HdDirtyBits *dirtyBits) = 0;

  /// Finalizes object resources. This function might not delete resources,
  /// but it should deal with resource ownership so that the sprim is
  /// deletable.
  HD_API
  virtual void Finalize(HdRenderParam *renderParam);

  /// Returns the minimal set of dirty bits to place in the
  /// change tracker for use in the first sync of this prim.
  /// Typically this would be all dirty bits.
  virtual HdDirtyBits GetInitialDirtyBitsMask() const = 0;

 private:
  SdfPath _id;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_BPRIM_H
