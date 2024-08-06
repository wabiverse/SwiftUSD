//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_CLIP_SET_DEFINITION_H
#define PXR_USD_USD_CLIP_SET_DEFINITION_H

#include "pxr/pxrns.h"

#include "Gf/vec2d.h"
#include "Sdf/assetPath.h"
#include "Sdf/path.h"
#include "Tf/declarePtrs.h"
#include "Tf/hash.h"
#include "Vt/array.h"

#include <optional>
#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class PcpPrimIndex;
TF_DECLARE_WEAK_PTRS(PcpLayerStack);

/// \class Usd_ClipSetDefinition
///
/// Collection of metadata from scene description and other information that
/// uniquely defines a clip set.
class Usd_ClipSetDefinition {
 public:
  Usd_ClipSetDefinition()
      : interpolateMissingClipValues(false), indexOfLayerWhereAssetPathsFound(0)
  {
  }

  bool operator==(const Usd_ClipSetDefinition &rhs) const
  {
    return (clipAssetPaths == rhs.clipAssetPaths &&
            clipManifestAssetPath == rhs.clipManifestAssetPath &&
            clipPrimPath == rhs.clipPrimPath && clipActive == rhs.clipActive &&
            clipTimes == rhs.clipTimes &&
            interpolateMissingClipValues == rhs.interpolateMissingClipValues &&
            sourceLayerStack == rhs.sourceLayerStack && sourcePrimPath == rhs.sourcePrimPath &&
            indexOfLayerWhereAssetPathsFound == rhs.indexOfLayerWhereAssetPathsFound);
  }

  bool operator!=(const Usd_ClipSetDefinition &rhs) const
  {
    return !(*this == rhs);
  }

  size_t GetHash() const
  {
    size_t hash = TfHash::Combine(
        indexOfLayerWhereAssetPathsFound, sourceLayerStack, sourcePrimPath);

    if (clipAssetPaths) {
      hash = TfHash::Combine(hash, *clipAssetPaths);
    }
    if (clipManifestAssetPath) {
      hash = TfHash::Combine(hash, *clipManifestAssetPath);
    }
    if (clipPrimPath) {
      hash = TfHash::Combine(hash, *clipPrimPath);
    }
    if (clipActive) {
      hash = TfHash::Combine(hash, *clipActive);
    }
    if (clipTimes) {
      hash = TfHash::Combine(hash, *clipTimes);
    }
    if (interpolateMissingClipValues) {
      hash = TfHash::Combine(hash, *interpolateMissingClipValues);
    }
    return hash;
  }

  template<typename HashState>
  friend void TfHashAppend(HashState &h, const Usd_ClipSetDefinition &definition)
  {
    h.Append(definition.GetHash());
  }

  std::optional<VtArray<SdfAssetPath>> clipAssetPaths;
  std::optional<SdfAssetPath> clipManifestAssetPath;
  std::optional<std::string> clipPrimPath;
  std::optional<VtVec2dArray> clipActive;
  std::optional<VtVec2dArray> clipTimes;
  std::optional<bool> interpolateMissingClipValues;

  PcpLayerStackPtr sourceLayerStack;
  SdfPath sourcePrimPath;
  size_t indexOfLayerWhereAssetPathsFound;
};

/// Computes clip set definitions for the given \p primIndex and returns
/// them in \p clipSetDefinitions. The clip sets in this vector are sorted in
/// strength order. If \p clipSetNames is provided it will contain the name
/// for each clip set in the corresponding position in \p clipSetDefinitions.
void Usd_ComputeClipSetDefinitionsForPrimIndex(
    const PcpPrimIndex &primIndex,
    std::vector<Usd_ClipSetDefinition> *clipSetDefinitions,
    std::vector<std::string> *clipSetNames = nullptr);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
