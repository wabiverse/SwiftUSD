//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_RPRIM_SHARED_DATA_H
#define PXR_IMAGING_HD_RPRIM_SHARED_DATA_H

#include "Hd/api.h"
#include "Hd/bufferArrayRange.h"
#include "Hd/tokens.h"
#include "Hd/version.h"
#include "pxr/pxrns.h"

#include "Sdf/path.h"

#include "Gf/bbox3d.h"
#include "Vt/array.h"
#include "Vt/types.h"

PXR_NAMESPACE_OPEN_SCOPE

using TopologyToPrimvarVector = std::vector<std::pair<VtIntArray, std::vector<TfToken>>>;

// HdRprimSharedData is an assortment of data being shared across HdReprs,
// owned by HdRprim. HdDrawItem holds a const pointer to HdRprimSharedData.
//
// HdRprim
//   |
//   +--HdRepr(s)
//   |    |
//   |    +--HdDrawItem(s)-----.
//   |                         |
//   +--HdRprimSharedData  <---'
//

struct HdRprimSharedData {
  HdRprimSharedData(int barContainerSize)
      : barContainer(barContainerSize), bounds(), instancerLevels(0), visible(true), rprimID()
  {
  }

  HdRprimSharedData(int barContainerSize, bool visible)
      : barContainer(barContainerSize), bounds(), instancerLevels(0), visible(visible), rprimID()
  {
  }

  // BufferArrayRange array
  HdBufferArrayRangeContainer barContainer;

  // Used for CPU frustum culling.
  GfBBox3d bounds;

  // The number of levels of instancing applied to this rprim.
  int instancerLevels;

  // Used for authored/delegate visibility.
  bool visible;

  // The owning Rprim's identifier.
  SdfPath rprimID;

  // Data structure containing the face-varying topologies of an rprim (mesh
  // only) and each of the topology's associated face-varying primvar names.
  // Used in drawing to determine which primvar uses which face-varying
  // channel.
  TopologyToPrimvarVector fvarTopologyToPrimvarVector;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_RPRIM_SHARED_DATA_H
