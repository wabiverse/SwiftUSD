//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_SKEL_SKEL_DEFINITION_H
#define PXR_USD_USD_SKEL_SKEL_DEFINITION_H

/// \file usdSkel/definition.h

#include "UsdSkel/api.h"
#include "pxr/pxrns.h"

#include "Gf/matrix4d.h"
#include "Gf/matrix4f.h"

#include "Tf/declarePtrs.h"
#include "Tf/hashmap.h"
#include "Tf/refBase.h"
#include "Tf/weakBase.h"

#include "UsdSkel/skeleton.h"
#include "UsdSkel/topology.h"

#include <atomic>
#include <mutex>

PXR_NAMESPACE_OPEN_SCOPE

TF_DECLARE_WEAK_AND_REF_PTRS(UsdSkel_SkelDefinition);

/// \class UsdSkel_SkelDefinition
///
/// Structure storing the core definition of a Skeleton.
/// A definition is a simple cache of the *validated* structure
/// of a skeleton, including its topology, bind pose and rest pose.
/// Skeleton definitions are meant to shared across instances.
class UsdSkel_SkelDefinition : public TfRefBase, public TfWeakBase {
 public:
  virtual ~UsdSkel_SkelDefinition() {}

  /// Create a definition from a skeleton.
  /// Returns an empty pointer if \p skel or its structure is invalid.
  static UsdSkel_SkelDefinitionRefPtr New(const UsdSkelSkeleton &skel);

  explicit operator bool() const
  {
    return static_cast<bool>(_skel);
  }

  const UsdSkelSkeleton &GetSkeleton() const
  {
    return _skel;
  }

  const VtTokenArray &GetJointOrder() const
  {
    return _jointOrder;
  }

  const UsdSkelTopology &GetTopology() const
  {
    return _topology;
  }

  /// Returns rest pose joint transforms in joint-local space.
  template<typename Matrix4> bool GetJointLocalRestTransforms(VtArray<Matrix4> *xforms);

  /// Returns rest pose joint transforms in skel space.
  template<typename Matrix4> bool GetJointSkelRestTransforms(VtArray<Matrix4> *xforms);

  /// Returns bind pose joint transforms in world space.
  template<typename Matrix4> bool GetJointWorldBindTransforms(VtArray<Matrix4> *xforms);

  /// Returns the inverse of the world-space joint bind transforms.
  template<typename Matrix4> bool GetJointWorldInverseBindTransforms(VtArray<Matrix4> *xforms);

  /// Returns the inverse of the local-space rest transforms.
  template<typename Matrix4> bool GetJointLocalInverseRestTransforms(VtArray<Matrix4> *xforms);

  /// See UsdSkel_SkeletonQuery::HasBindPose()
  bool HasBindPose();

  /// See UsdSkel_SkeletonQuery::HasRestPose()
  bool HasRestPose();

 private:
  UsdSkel_SkelDefinition();

  bool _Init(const UsdSkelSkeleton &skel);

  template<int ComputeFlag, typename Matrix4>
  bool _GetJointSkelRestTransforms(VtArray<Matrix4> *xforms);

  template<int ComputeFlag, typename Matrix4>
  bool _GetJointWorldInverseBindTransforms(VtArray<Matrix4> *xforms);

  template<int ComputeFlag, typename Matrix4>
  bool _GetJointLocalInverseRestTransforms(VtArray<Matrix4> *xforms);

  template<int ComputeFlag, typename Matrix4> bool _ComputeJointSkelRestTransforms();

  template<int ComputeFlag, typename Matrix4> bool _ComputeJointWorldInverseBindTransforms();

  template<int ComputeFlag, typename Matrix4> bool _ComputeJointLocalInverseRestTransforms();

  /// Helper for managing a set of cached transforms
  /// with both float and double precision.
  struct _XformHolder {
    template<typename Matrix4> VtArray<Matrix4> &Get();

    template<typename Matrix4> const VtArray<Matrix4> &Get() const;

    VtMatrix4dArray xforms4d;
    VtMatrix4fArray xforms4f;
  };

 private:
  UsdSkelSkeleton _skel;
  VtTokenArray _jointOrder;
  UsdSkelTopology _topology;
  VtMatrix4dArray _jointLocalRestXforms;
  VtMatrix4dArray _jointWorldBindXforms;
  // Properties computed (and cached) on-demand.
  // Different forms of transforms are cached because different
  // consumption tasks generally require different transforms.
  // They are cached on the definition in order to provide cache
  // sharing across instanced skeletons.
  _XformHolder _jointSkelRestXforms;
  _XformHolder _jointWorldInverseBindXforms;
  _XformHolder _jointLocalInverseRestXforms;

  std::atomic<int> _flags;
  std::mutex _mutex;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_USD_SKEL_SKEL_DEFINITION_H
