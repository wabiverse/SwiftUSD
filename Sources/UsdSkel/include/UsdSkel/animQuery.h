//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_SKEL_ANIM_QUERY_H
#define PXR_USD_USD_SKEL_ANIM_QUERY_H

/// \file usdSkel/animQuery.h

#include "UsdSkel/api.h"
#include "pxr/pxrns.h"

#include "Tf/declarePtrs.h"
#include "Vt/types.h"

#include "Sdf/path.h"
#include "Usd/prim.h"
#include "Usd/timeCode.h"

PXR_NAMESPACE_OPEN_SCOPE

class GfMatrix4d;
class UsdAttribute;
class UsdSkelCache;

TF_DECLARE_REF_PTRS(UsdSkel_AnimQueryImpl);

/// \class UsdSkelAnimQuery
///
/// Class providing efficient queries of primitives that provide skel animation.
class UsdSkelAnimQuery {
 public:
  USDSKEL_API
  UsdSkelAnimQuery() {}

  /// Return true if this query is valid.
  bool IsValid() const
  {
    return (bool)_impl;
  }

  /// Boolean conversion operator. Equivalent to IsValid().
  explicit operator bool() const
  {
    return IsValid();
  }

  /// Equality comparison.  Return true if \a lhs and \a rhs represent the
  /// same UsdSkelAnimQuery, false otherwise.
  friend bool operator==(const UsdSkelAnimQuery &lhs, const UsdSkelAnimQuery &rhs)
  {
    return lhs.GetPrim() == rhs.GetPrim();
  }

  /// Inequality comparison. Return false if \a lhs and \a rhs represent the
  /// same UsdSkelAnimQuery, true otherwise.
  friend bool operator!=(const UsdSkelAnimQuery &lhs, const UsdSkelAnimQuery &rhs)
  {
    return !(lhs == rhs);
  }

  // hash_value overload for std/boost hash.
  friend size_t hash_value(const UsdSkelAnimQuery &query)
  {
    return hash_value(query.GetPrim());
  }

  /// Return the primitive this anim query reads from.
  USDSKEL_API
  UsdPrim GetPrim() const;

  /// Compute joint transforms in joint-local space.
  /// Transforms are returned in the order specified by the joint ordering
  /// of the animation primitive itself.
  template<typename Matrix4>
  USDSKEL_API bool ComputeJointLocalTransforms(VtArray<Matrix4> *xforms,
                                               UsdTimeCode time = UsdTimeCode::Default()) const;

  /// Compute translation,rotation,scale components of the joint transforms
  /// in joint-local space. This is provided to facilitate direct streaming
  /// of animation data in a form that can efficiently be processed for
  /// animation blending.
  USDSKEL_API
  bool ComputeJointLocalTransformComponents(VtVec3fArray *translations,
                                            VtQuatfArray *rotations,
                                            VtVec3hArray *scales,
                                            UsdTimeCode time = UsdTimeCode::Default()) const;

  USDSKEL_API
  bool ComputeBlendShapeWeights(VtFloatArray *weights,
                                UsdTimeCode time = UsdTimeCode::Default()) const;

  /// Get the time samples at which values contributing to joint transforms
  /// are set. This only computes the time samples for sampling transforms in
  /// joint-local space, and does not include time samples affecting the
  /// root transformation.
  ///
  /// \sa UsdAttribute::GetTimeSamples
  USDSKEL_API
  bool GetJointTransformTimeSamples(std::vector<double> *times) const;

  /// Get the time samples at which values contributing to joint transforms
  /// are set, over \p interval. This only computes the time samples for
  /// sampling transforms in joint-local space, and does not include time
  /// samples affecting the root transformation.
  ///
  /// \sa UsdAttribute::GetTimeSamplesInInterval
  USDSKEL_API
  bool GetJointTransformTimeSamplesInInterval(const GfInterval &interval,
                                              std::vector<double> *times) const;

  /// Get the attributes contributing to JointTransform computations
  USDSKEL_API
  bool GetJointTransformAttributes(std::vector<UsdAttribute> *attrs) const;

  /// Return true if it possible, but not certain, that joint transforms
  /// computed through this animation query change over time, false otherwise.
  ///
  /// \sa UsdAttribute::ValueMightBeTimeVayring
  USDSKEL_API
  bool JointTransformsMightBeTimeVarying() const;

  /// Get the time samples at which values contributing to blend shape weights
  /// have been set.
  ///
  /// \sa UsdAttribute::GetTimeSamples
  USDSKEL_API
  bool GetBlendShapeWeightTimeSamples(std::vector<double> *attrs) const;

  /// Get the time samples at which values contributing to blend shape weights
  /// are set, over \p interval.
  ///
  /// \sa UsdAttribute::GetTimeSamplesInInterval
  USDSKEL_API
  bool GetBlendShapeWeightTimeSamplesInInterval(const GfInterval &interval,
                                                std::vector<double> *times) const;

  /// Get the attributes contributing to blendshape weight computations.
  USDSKEL_API
  bool GetBlendShapeWeightAttributes(std::vector<UsdAttribute> *attrs) const;

  /// Return true if it possible, but not certain, that the blend shape
  /// weights computed through this animation query change over time,
  /// false otherwise.
  ///
  /// \sa UsdAttribute::ValueMightBeTimeVayring
  USDSKEL_API
  bool BlendShapeWeightsMightBeTimeVarying() const;

  /// Returns an array of tokens describing the ordering of joints in the
  /// animation.
  ///
  /// \sa UsdSkelSkeleton::GetJointOrder
  USDSKEL_API
  VtTokenArray GetJointOrder() const;

  /// Returns an array of tokens describing the ordering of blend shape
  /// channels in the animation.
  USDSKEL_API
  VtTokenArray GetBlendShapeOrder() const;

  USDSKEL_API
  std::string GetDescription() const;

 private:
  UsdSkelAnimQuery(const UsdSkel_AnimQueryImplRefPtr &impl) : _impl(impl) {}

  UsdSkel_AnimQueryImplRefPtr _impl;

  friend class UsdSkel_CacheImpl;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_USD_SKEL_ANIM_QUERY_H
