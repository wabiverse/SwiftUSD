//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef PXR_USD_SDF_PAYLOAD_H
#define PXR_USD_SDF_PAYLOAD_H

/// \file sdf/payload.h

#include "Sdf/api.h"
#include "Sdf/assetPath.h"
#include "Sdf/layerOffset.h"
#include "Sdf/path.h"
#include "Tf/hash.h"
#include <pxr/pxrns.h>

#include <boost/operators.hpp>

#include <iosfwd>
#include <string>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class SdfPayload;

typedef std::vector<SdfPayload> SdfPayloadVector;

/// \class SdfPayload
///
/// Represents a payload and all its meta data.
///
/// A payload represents a prim reference to an external layer.  A payload
/// is similar to a prim reference (see SdfReference) with the major
/// difference that payloads are explicitly loaded by the user.
///
/// Unloaded payloads represent a boundary that lazy composition and
/// system behaviors will not traverse across, providing a user-visible
/// way to manage the working set of the scene.
///
class SdfPayload : boost::totally_ordered<SdfPayload> {
public:
  /// Create a payload. See SdfAssetPath for what characters are valid in \p
  /// assetPath.  If \p assetPath contains invalid characters, issue an error
  /// and set this payload's asset path to the empty asset path.
  ///
  SDF_API
  SdfPayload(const std::string &assetPath = std::string(),
             const SdfPath &primPath = SdfPath(),
             const SdfLayerOffset &layerOffset = SdfLayerOffset());

  /// Returns the asset path of the layer that the payload uses.
  const std::string &GetAssetPath() const { return _assetPath; }

  /// Sets a new asset path for the layer the payload uses.  See SdfAssetPath
  /// for what characters are valid in \p assetPath.  If \p assetPath contains
  /// invalid characters, issue an error and set this payload's asset path to
  /// the empty asset path.
  void SetAssetPath(const std::string &assetPath) {
    // Go through SdfAssetPath() to raise an error if \p assetPath contains
    // illegal characters (i.e. control characters).
    _assetPath = SdfAssetPath(assetPath).GetAssetPath();
  }

  /// Returns the scene path of the prim for the payload.
  const SdfPath &GetPrimPath() const { return _primPath; }

  /// Sets a new prim path for the prim that the payload uses.
  void SetPrimPath(const SdfPath &primPath) { _primPath = primPath; }

  /// Returns the layer offset associated with the payload.
  const SdfLayerOffset &GetLayerOffset() const { return _layerOffset; }

  /// Sets a new layer offset.
  void SetLayerOffset(const SdfLayerOffset &layerOffset) {
    _layerOffset = layerOffset;
  }

  /// Returns whether this payload equals \a rhs.
  SDF_API bool operator==(const SdfPayload &rhs) const;

  /// Returns whether this payload is less than \a rhs.
  /// The meaning of less than is arbitrary but stable.
  SDF_API bool operator<(const SdfPayload &rhs) const;

private:
  friend inline size_t hash_value(const SdfPayload &p) {
    return TfHash::Combine(p._assetPath, p._primPath, p._layerOffset);
  }

  // The asset path to the external layer.
  std::string _assetPath;

  // The root prim path to the referenced prim in the external layer.
  SdfPath _primPath;

  // The layer offset to transform time.
  SdfLayerOffset _layerOffset;
};

/// Writes the string representation of \a SdfPayload to \a out.
SDF_API
std::ostream &operator<<(std::ostream &out, const SdfPayload &payload);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
