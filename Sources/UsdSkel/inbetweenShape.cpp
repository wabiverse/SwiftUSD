//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/inbetweenShape.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens,
                         ((inbetweensPrefix, "inbetweens:"))((normalOffsetsSuffix,
                                                              ":normalOffsets")));

UsdSkelInbetweenShape::UsdSkelInbetweenShape(const UsdAttribute &attr) : _attr(attr) {}

/* static */
UsdSkelInbetweenShape UsdSkelInbetweenShape::_Create(const UsdPrim &prim, const TfToken &name)
{
  if (TF_VERIFY(prim)) {
    TfToken attrName = _MakeNamespaced(name);

    if (!attrName.IsEmpty()) {
      return UsdSkelInbetweenShape(prim.CreateAttribute(attrName,
                                                        SdfValueTypeNames->Point3fArray,
                                                        /*custom*/ false,
                                                        SdfVariabilityUniform));
    }
  }
  return UsdSkelInbetweenShape();
}

/* static */
bool UsdSkelInbetweenShape::IsInbetween(const UsdAttribute &attr)
{
  return attr ? _IsValidInbetweenName(attr.GetName()) : false;
}

/* static */
bool UsdSkelInbetweenShape::_IsValidInbetweenName(const std::string &name, bool quiet)
{
  // All properly namespaced attributes are legal inbetweens.
  // We do, however, need to exclude extra properties that apply
  // within the namespace of each inbetween. For now, the only
  // such property is 'normalOffsets', which we elide here manually.
  return TfStringStartsWith(name, _tokens->inbetweensPrefix) &&
         !TfStringEndsWith(name, _tokens->normalOffsetsSuffix);
}

/* static */
bool UsdSkelInbetweenShape::_IsNamespaced(const TfToken &name)
{
  return TfStringStartsWith(name, _tokens->inbetweensPrefix);
}

/* static */
TfToken UsdSkelInbetweenShape::_MakeNamespaced(const TfToken &name, bool quiet)
{
  TfToken result;
  if (_IsNamespaced(name)) {
    result = name;
  }
  else {
    result = TfToken(_tokens->inbetweensPrefix.GetString() + name.GetString());
  }

  // XXX: All properly namespaced attributes are legal inbetweens.
  // However, if we extend the schema to include any special attributes
  // -- such as a namespaced pointIndices attr on each shape -- then
  // we must validate that the name does not conflict with those.

  if (!_IsValidInbetweenName(result, quiet)) {
    result = TfToken();
  }
  return result;
}

/* static */
const TfToken &UsdSkelInbetweenShape::_GetNamespacePrefix()
{
  return _tokens->inbetweensPrefix;
}

UsdAttribute UsdSkelInbetweenShape::_GetNormalOffsetsAttr(bool create) const
{
  const TfToken normalOffsetsName(_attr.GetName().GetString() +
                                  _tokens->normalOffsetsSuffix.GetString());

  if (!create) {
    return _attr.GetPrim().GetAttribute(normalOffsetsName);
  }
  else {
    return _attr.GetPrim().CreateAttribute(normalOffsetsName,
                                           SdfValueTypeNames->Vector3fArray,
                                           /*custom*/ false,
                                           SdfVariabilityVarying);
  }
}

UsdAttribute UsdSkelInbetweenShape::GetNormalOffsetsAttr() const
{
  return _GetNormalOffsetsAttr(/*create*/ false);
}

UsdAttribute UsdSkelInbetweenShape::CreateNormalOffsetsAttr(const VtValue &defaultValue) const
{
  const UsdAttribute attr = _GetNormalOffsetsAttr(/*create*/ true);
  if (attr && !defaultValue.IsEmpty()) {
    attr.Set(defaultValue);
  }
  return attr;
}

bool UsdSkelInbetweenShape::GetWeight(float *weight) const
{
  return _attr.GetMetadata(UsdSkelTokens->weight, weight);
}

bool UsdSkelInbetweenShape::SetWeight(float weight) const
{
  return _attr.SetMetadata(UsdSkelTokens->weight, weight);
}

bool UsdSkelInbetweenShape::HasAuthoredWeight() const
{
  return _attr.HasAuthoredMetadata(UsdSkelTokens->weight);
}

bool UsdSkelInbetweenShape::GetOffsets(VtVec3fArray *offsets) const
{
  return _attr.Get(offsets);
}

bool UsdSkelInbetweenShape::SetOffsets(const VtVec3fArray &offsets) const
{
  return _attr.Set(offsets);
}

bool UsdSkelInbetweenShape::GetNormalOffsets(VtVec3fArray *offsets) const
{
  if (const UsdAttribute attr = GetNormalOffsetsAttr()) {
    return attr.Get(offsets);
  }
  return false;
}

bool UsdSkelInbetweenShape::SetNormalOffsets(const VtVec3fArray &offsets) const
{
  if (const UsdAttribute attr = _GetNormalOffsetsAttr(/*create*/ true)) {
    return attr.Set(offsets);
  }
  return false;
}

PXR_NAMESPACE_CLOSE_SCOPE
