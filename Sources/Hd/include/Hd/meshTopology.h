//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_MESH_TOPOLOGY_H
#define PXR_IMAGING_HD_MESH_TOPOLOGY_H

#include "Hd/api.h"
#include "Hd/geomSubset.h"
#include "Hd/topology.h"
#include "Hd/version.h"
#include "pxr/pxrns.h"

#include "PxOsd/meshTopology.h"

#include "Vt/array.h"
#include "Vt/value.h"

#include "Tf/token.h"

#include <memory>

PXR_NAMESPACE_OPEN_SCOPE

using HdMeshTopologySharedPtr = std::shared_ptr<class HdMeshTopology>;

/// \class HdMeshTopology
///
/// Topology data for meshes.
///
/// HdMeshTopology holds the raw input topology data for a mesh and is capable
/// of computing derivative topological data (such as indices or subdivision
/// stencil tables and patch tables).
///
class HdMeshTopology : public HdTopology {
 public:
  HD_API
  HdMeshTopology();
  HD_API
  HdMeshTopology(const HdMeshTopology &, int refineLevel = 0);
  HD_API
  HdMeshTopology(const PxOsdMeshTopology &, int refineLevel = 0);
  HD_API
  HdMeshTopology(const TfToken &scheme,
                 const TfToken &orientation,
                 const VtIntArray &faceVertexCounts,
                 const VtIntArray &faceVertexIndices,
                 int refineLevel = 0);
  HD_API
  HdMeshTopology(const TfToken &scheme,
                 const TfToken &orientation,
                 const VtIntArray &faceVertexCounts,
                 const VtIntArray &faceVertexIndices,
                 const VtIntArray &holeIndices,
                 int refineLevel = 0);
  HD_API
  virtual ~HdMeshTopology();

  HD_API
  HdMeshTopology &operator=(const HdMeshTopology &copy);

  /// Returns whether adaptive subdivision is enabled or not.
  HD_API
  static bool IsEnabledAdaptive();

  PxOsdMeshTopology const &GetPxOsdMeshTopology() const
  {
    return _topology;
  }

  /// Returns the num faces
  HD_API
  int GetNumFaces() const;

  /// Returns the num facevarying primvars
  HD_API
  int GetNumFaceVaryings() const;

  /// Returns the num points of the topology vert indices array
  HD_API
  int GetNumPoints() const;

  /// Returns the num points by looking vert indices array
  HD_API
  static int ComputeNumPoints(VtIntArray const &verts);

  /// Returns the subdivision scheme
  TfToken const GetScheme() const
  {
    return _topology.GetScheme();
  }

  /// Returns the refinement level
  int GetRefineLevel() const
  {
    return _refineLevel;
  }

  /// Returns face vertex counts.
  VtIntArray const &GetFaceVertexCounts() const
  {
    return _topology.GetFaceVertexCounts();
  }

  /// Returns face vertex indics.
  VtIntArray const &GetFaceVertexIndices() const
  {
    return _topology.GetFaceVertexIndices();
  }

  /// Returns orientation.
  TfToken const &GetOrientation() const
  {
    return _topology.GetOrientation();
  }

  /// Returns the hash value of this topology to be used for instancing.
  HD_API
  virtual ID ComputeHash() const;

  /// Equality check between two mesh topologies.
  HD_API
  bool operator==(HdMeshTopology const &other) const;

  ///
  /// \name Hole
  /// @{

  /// Sets hole face indices. faceIndices needs to be sorted in
  /// ascending order.
  void SetHoleIndices(VtIntArray const &holeIndices)
  {
    _topology = _topology.WithHoleIndices(holeIndices);
  }

  /// Returns the hole face indices.
  VtIntArray const &GetHoleIndices() const
  {
    return _topology.GetHoleIndices();
  }

  /// @}

  ///
  /// \name Subdivision
  /// @{

  /// Sets subdivision tags.
  void SetSubdivTags(PxOsdSubdivTags const &subdivTags)
  {
    _topology = _topology.WithSubdivTags(subdivTags);
  }

  /// Returns subdivision tags
  PxOsdSubdivTags const &GetSubdivTags() const
  {
    return _topology.GetSubdivTags();
  }

  /// @}

  ///
  /// \name Geometry subsets
  /// @{

  /// Sets geometry subsets
  HD_API
  void SetGeomSubsets(HdGeomSubsets const &geomSubsets)
  {
    _geomSubsets = geomSubsets;
  }

  /// Returns geometry subsets
  HD_API
  HdGeomSubsets const &GetGeomSubsets() const
  {
    return _geomSubsets;
  }

  /// @}

  ///
  /// \name Topological invisibility
  /// @{
  ///
  HD_API
  void SetInvisiblePoints(VtIntArray const &invisiblePoints)
  {
    _invisiblePoints = invisiblePoints;
  }

  HD_API
  VtIntArray const &GetInvisiblePoints() const
  {
    return _invisiblePoints;
  }

  HD_API
  void SetInvisibleFaces(VtIntArray const &invisibleFaces)
  {
    _invisibleFaces = invisibleFaces;
  }

  HD_API
  VtIntArray const &GetInvisibleFaces() const
  {
    return _invisibleFaces;
  }
  /// @}

 protected:
  PxOsdMeshTopology _topology;
  HdGeomSubsets _geomSubsets;
  VtIntArray _invisiblePoints;
  VtIntArray _invisibleFaces;
  int _refineLevel;
  int _numPoints;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_MESH_TOPOLOGY_H
