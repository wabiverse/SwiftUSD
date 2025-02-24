//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
// GENERATED FILE.  DO NOT EDIT.
#include "UsdSkel/tokens.h"
#include <boost/python/class.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

// Helper to return a static token as a string.  We wrap tokens as Python
// strings and for some reason simply wrapping the token using def_readonly
// bypasses to-Python conversion, leading to the error that there's no
// Python type for the C++ TfToken type.  So we wrap this functor instead.
class _WrapStaticToken {
 public:
  _WrapStaticToken(const TfToken *token) : _token(token) {}

  std::string operator()() const
  {
    return _token->GetString();
  }

 private:
  const TfToken *_token;
};

template<typename T> void _AddToken(T &cls, const char *name, const TfToken &token)
{
  cls.add_static_property(name,
                          boost::python::make_function(
                              _WrapStaticToken(&token),
                              boost::python::return_value_policy<boost::python::return_by_value>(),
                              boost::mpl::vector1<std::string>()));
}

}  // namespace

void wrapUsdSkelTokens()
{
  boost::python::class_<UsdSkelTokensType, boost::noncopyable> cls("Tokens",
                                                                   boost::python::no_init);
  _AddToken(cls, "bindTransforms", UsdSkelTokens->bindTransforms);
  _AddToken(cls, "blendShapes", UsdSkelTokens->blendShapes);
  _AddToken(cls, "blendShapeWeights", UsdSkelTokens->blendShapeWeights);
  _AddToken(cls, "classicLinear", UsdSkelTokens->classicLinear);
  _AddToken(cls, "dualQuaternion", UsdSkelTokens->dualQuaternion);
  _AddToken(cls, "jointNames", UsdSkelTokens->jointNames);
  _AddToken(cls, "joints", UsdSkelTokens->joints);
  _AddToken(cls, "normalOffsets", UsdSkelTokens->normalOffsets);
  _AddToken(cls, "offsets", UsdSkelTokens->offsets);
  _AddToken(cls, "pointIndices", UsdSkelTokens->pointIndices);
  _AddToken(cls, "primvarsSkelGeomBindTransform", UsdSkelTokens->primvarsSkelGeomBindTransform);
  _AddToken(cls, "primvarsSkelJointIndices", UsdSkelTokens->primvarsSkelJointIndices);
  _AddToken(cls, "primvarsSkelJointWeights", UsdSkelTokens->primvarsSkelJointWeights);
  _AddToken(cls, "primvarsSkelSkinningMethod", UsdSkelTokens->primvarsSkelSkinningMethod);
  _AddToken(cls, "restTransforms", UsdSkelTokens->restTransforms);
  _AddToken(cls, "rotations", UsdSkelTokens->rotations);
  _AddToken(cls, "scales", UsdSkelTokens->scales);
  _AddToken(cls, "skelAnimationSource", UsdSkelTokens->skelAnimationSource);
  _AddToken(cls, "skelBlendShapes", UsdSkelTokens->skelBlendShapes);
  _AddToken(cls, "skelBlendShapeTargets", UsdSkelTokens->skelBlendShapeTargets);
  _AddToken(cls, "skelJoints", UsdSkelTokens->skelJoints);
  _AddToken(cls, "skelSkeleton", UsdSkelTokens->skelSkeleton);
  _AddToken(cls, "translations", UsdSkelTokens->translations);
  _AddToken(cls, "weight", UsdSkelTokens->weight);
  _AddToken(cls, "BlendShape", UsdSkelTokens->BlendShape);
  _AddToken(cls, "SkelAnimation", UsdSkelTokens->SkelAnimation);
  _AddToken(cls, "SkelBindingAPI", UsdSkelTokens->SkelBindingAPI);
  _AddToken(cls, "Skeleton", UsdSkelTokens->Skeleton);
  _AddToken(cls, "SkelRoot", UsdSkelTokens->SkelRoot);
}
