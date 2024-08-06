//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/animQuery.h"

#include "UsdSkel/animQuery.h"
#include "UsdSkel/animQueryImpl.h"

#include "Usd/attribute.h"
#include "Usd/prim.h"

#include "Gf/interval.h"
#include "Gf/matrix4d.h"
#include "Gf/matrix4f.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdPrim UsdSkelAnimQuery::GetPrim() const
{
  return _impl ? _impl->GetPrim() : UsdPrim();
}

template<typename Matrix4>
bool UsdSkelAnimQuery::ComputeJointLocalTransforms(VtArray<Matrix4> *xforms,
                                                   UsdTimeCode time) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->ComputeJointLocalTransforms(xforms, time);
  }
  return false;
}

template USDSKEL_API bool UsdSkelAnimQuery::ComputeJointLocalTransforms(VtArray<GfMatrix4d> *,
                                                                        UsdTimeCode) const;

template USDSKEL_API bool UsdSkelAnimQuery::ComputeJointLocalTransforms(VtArray<GfMatrix4f> *,
                                                                        UsdTimeCode) const;

bool UsdSkelAnimQuery::ComputeJointLocalTransformComponents(VtVec3fArray *translations,
                                                            VtQuatfArray *rotations,
                                                            VtVec3hArray *scales,
                                                            UsdTimeCode time) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->ComputeJointLocalTransformComponents(translations, rotations, scales, time);
  }
  return false;
}

bool UsdSkelAnimQuery::ComputeBlendShapeWeights(VtFloatArray *weights, UsdTimeCode time) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->ComputeBlendShapeWeights(weights, time);
  }
  return false;
}

bool UsdSkelAnimQuery::GetJointTransformTimeSamples(std::vector<double> *times) const
{
  return GetJointTransformTimeSamplesInInterval(GfInterval::GetFullInterval(), times);
}

bool UsdSkelAnimQuery::GetJointTransformTimeSamplesInInterval(const GfInterval &interval,
                                                              std::vector<double> *times) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetJointTransformTimeSamples(interval, times);
  }
  return false;
}

bool UsdSkelAnimQuery::GetJointTransformAttributes(std::vector<UsdAttribute> *attrs) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetJointTransformAttributes(attrs);
  }
  return false;
}

bool UsdSkelAnimQuery::JointTransformsMightBeTimeVarying() const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->JointTransformsMightBeTimeVarying();
  }
  return false;
}

VtTokenArray UsdSkelAnimQuery::GetJointOrder() const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetJointOrder();
  }
  return VtTokenArray();
}

VtTokenArray UsdSkelAnimQuery::GetBlendShapeOrder() const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetBlendShapeOrder();
  }
  return VtTokenArray();
}

bool UsdSkelAnimQuery::GetBlendShapeWeightTimeSamples(std::vector<double> *times) const
{
  return GetBlendShapeWeightTimeSamplesInInterval(GfInterval::GetFullInterval(), times);
}

bool UsdSkelAnimQuery::GetBlendShapeWeightAttributes(std::vector<UsdAttribute> *attrs) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetBlendShapeWeightAttributes(attrs);
  }
  return false;
}

bool UsdSkelAnimQuery::GetBlendShapeWeightTimeSamplesInInterval(const GfInterval &interval,
                                                                std::vector<double> *times) const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->GetBlendShapeWeightTimeSamples(interval, times);
  }
  return false;
}

bool UsdSkelAnimQuery::BlendShapeWeightsMightBeTimeVarying() const
{
  if (TF_VERIFY(IsValid(), "invalid anim query.")) {
    return _impl->BlendShapeWeightsMightBeTimeVarying();
  }
  return false;
}

std::string UsdSkelAnimQuery::GetDescription() const
{
  if (_impl) {
    return TfStringPrintf("UsdSkelAnimQuery <%s>", _impl->GetPrim().GetPath().GetText());
  }
  return "invalid UsdSkelAnimQuery";
}

PXR_NAMESPACE_CLOSE_SCOPE
