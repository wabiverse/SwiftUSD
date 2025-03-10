//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdGeom/primvar.h"
#include "Usd/prim.h"
#include "Usd/relationship.h"
#include "pxr/pxrns.h"

#include "Tf/registryManager.h"
#include "Tf/staticTokens.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens,
                         ((primvarsPrefix, "primvars:"))((idFrom, ":idFrom"))((indicesSuffix,
                                                                               ":indices")));

UsdGeomPrimvar::UsdGeomPrimvar(const UsdAttribute &attr)
    : _attr(attr), _idTargetStatus(IdTargetUninitialized)
{
}

UsdGeomPrimvar::UsdGeomPrimvar(const UsdGeomPrimvar &other)
    : _attr(other._attr), _idTargetStatus(IdTargetUninitialized)
{
}

UsdGeomPrimvar &UsdGeomPrimvar::operator=(const UsdGeomPrimvar &other)
{
  if (this != &other) {
    _idTargetStatus = IdTargetUninitialized;
    _attr = other._attr;
  }
  return *this;
}

/* static */
bool UsdGeomPrimvar::IsPrimvar(const UsdAttribute &attr)
{
  if (!attr)
    return false;

  return IsValidPrimvarName(attr.GetName());
}

/* static */
bool UsdGeomPrimvar::IsValidPrimvarName(const TfToken &name)
{
  // All properly namespaced attributes are legal primvars, *except*
  // the "sidecar" attributes we create as part of the schema, like
  // "primvars:foo:indices".  We do not need to worry about the idFrom
  // suffix because it only appears on relationships.
  return (TfStringStartsWith(name, _tokens->primvarsPrefix) &&
          !TfStringEndsWith(name, _tokens->indicesSuffix));
}

/* static */
TfToken UsdGeomPrimvar::StripPrimvarsName(const TfToken &name)
{
  std::string const &fullName = name.GetString();

  std::pair<std::string, bool> res = SdfPath::StripPrefixNamespace(fullName,
                                                                   _tokens->primvarsPrefix);

  return res.second ? TfToken(res.first) : name;
}

/* static */
bool UsdGeomPrimvar::_IsNamespaced(const TfToken &name)
{
  return TfStringStartsWith(name, _tokens->primvarsPrefix);
}

/* static */
TfToken UsdGeomPrimvar::_MakeNamespaced(const TfToken &name, bool quiet)
{
  TfToken result;
  if (_IsNamespaced(name)) {
    result = name;
  }
  else {
    result = TfToken(_tokens->primvarsPrefix.GetString() + name.GetString());
  }

  if (!IsValidPrimvarName(result)) {
    result = TfToken();
    if (!quiet) {
      // XXX if we add more reserved keywords we'll need to extract
      // the offending keyword rather than assume it is "indices".
      TF_CODING_ERROR(
          "%s is not a valid name for a Primvar, because"
          " it contains the reserved name \"indices\"",
          name.GetText());
    }
  }

  return result;
}

/* static */
TfToken const &UsdGeomPrimvar::_GetNamespacePrefix()
{
  return _tokens->primvarsPrefix;
}

TfToken UsdGeomPrimvar::GetInterpolation() const
{
  TfToken interpolation;

  if (!_attr.GetMetadata(UsdGeomTokens->interpolation, &interpolation)) {
    interpolation = UsdGeomTokens->constant;
  }

  return interpolation;
}

bool UsdGeomPrimvar::HasAuthoredInterpolation() const
{
  return _attr.HasAuthoredMetadata(UsdGeomTokens->interpolation);
}

bool UsdGeomPrimvar::IsValidInterpolation(const TfToken &interpolation)
{
  return ((interpolation == UsdGeomTokens->constant) ||
          (interpolation == UsdGeomTokens->uniform) || (interpolation == UsdGeomTokens->vertex) ||
          (interpolation == UsdGeomTokens->varying) ||
          (interpolation == UsdGeomTokens->faceVarying));
}

bool UsdGeomPrimvar::SetInterpolation(const TfToken &interpolation)
{
  if (!IsValidInterpolation(interpolation)) {
    TF_CODING_ERROR(
        "Attempt to set invalid primvar interpolation "
        "\"%s\" for attribute %s",
        interpolation.GetText(),
        _attr.GetPath().GetString().c_str());
    return false;
  }
  return _attr.SetMetadata(UsdGeomTokens->interpolation, interpolation);
}

int UsdGeomPrimvar::GetElementSize() const
{
  int eltSize = 1;
  _attr.GetMetadata(UsdGeomTokens->elementSize, &eltSize);

  return eltSize;
}

bool UsdGeomPrimvar::SetElementSize(int eltSize)
{
  if (eltSize < 1) {
    TF_CODING_ERROR(
        "Attempt to set elementSize to %d for attribute "
        "%s (must be a positive, non-zero value)",
        eltSize,
        _attr.GetPath().GetString().c_str());
    return false;
  }
  return _attr.SetMetadata(UsdGeomTokens->elementSize, eltSize);
}

bool UsdGeomPrimvar::HasAuthoredElementSize() const
{
  return _attr.HasAuthoredMetadata(UsdGeomTokens->elementSize);
}

void UsdGeomPrimvar::GetDeclarationInfo(TfToken *name,
                                        SdfValueTypeName *typeName,
                                        TfToken *interpolation,
                                        int *elementSize) const
{
  TF_VERIFY(name && typeName && interpolation && elementSize);

  // We don't have any more efficient access pattern yet, but at least
  // we're still saving client some code
  *name = GetPrimvarName();
  *typeName = GetTypeName();
  *interpolation = GetInterpolation();
  *elementSize = GetElementSize();
}

UsdAttribute UsdGeomPrimvar::_GetIndicesAttr(bool create) const
{
  TfToken indicesAttrName(GetName().GetString() + _tokens->indicesSuffix.GetString());

  if (create) {
    return _attr.GetPrim().CreateAttribute(
        indicesAttrName, SdfValueTypeNames->IntArray, /*custom*/ false, SdfVariabilityVarying);
  }
  else {
    return _attr.GetPrim().GetAttribute(indicesAttrName);
  }
}

UsdAttribute UsdGeomPrimvar::GetIndicesAttr() const
{
  return _GetIndicesAttr(/*create*/ false);
}

UsdAttribute UsdGeomPrimvar::CreateIndicesAttr() const
{
  return _GetIndicesAttr(/*create*/ true);
}

bool UsdGeomPrimvar::SetIndices(const VtIntArray &indices, UsdTimeCode time) const
{
  // Check if the typeName is array valued here and issue a warning
  // if it's not.
  SdfValueTypeName typeName = GetTypeName();
  if (!typeName.IsArray()) {
    TF_CODING_ERROR(
        "Setting indices on non-array valued primvar of type "
        "'%s'.",
        typeName.GetAsToken().GetText());
    return false;
  }
  return _GetIndicesAttr(/*create*/ true).Set(indices, time);
}

void UsdGeomPrimvar::BlockIndices() const
{
  // Check if the typeName is array valued here and issue a warning
  // if it's not.
  SdfValueTypeName typeName = GetTypeName();
  if (!typeName.IsArray()) {
    TF_CODING_ERROR(
        "Setting indices on non-array valued primvar of type "
        "'%s'.",
        typeName.GetAsToken().GetText());
    return;
  }
  _GetIndicesAttr(/*create*/ true).Block();
}

bool UsdGeomPrimvar::GetIndices(VtIntArray *indices, UsdTimeCode time) const
{
  UsdAttribute indicesAttr = _GetIndicesAttr(/*create*/ false);
  if (indicesAttr)
    return indicesAttr.Get(indices, time);

  return false;
}

bool UsdGeomPrimvar::IsIndexed() const
{
  return _GetIndicesAttr(/*create*/ false).HasAuthoredValue();
}

bool UsdGeomPrimvar::SetUnauthoredValuesIndex(int unauthoredValuesIndex) const
{
  return _attr.SetMetadata(UsdGeomTokens->unauthoredValuesIndex, unauthoredValuesIndex);
}

int UsdGeomPrimvar::GetUnauthoredValuesIndex() const
{
  int unauthoredValuesIndex = -1;
  _attr.GetMetadata(UsdGeomTokens->unauthoredValuesIndex, &unauthoredValuesIndex);

  return unauthoredValuesIndex;
}

// Helper function to evaluate the flattened array value of a primvar given
// the attribute value and the indices array.
template<typename ArrayType>
bool UsdGeomPrimvar::_ComputeFlattenedArray(const VtValue &attrVal,
                                            const VtIntArray &indices,
                                            int elementSize,
                                            VtValue *value,
                                            std::string *errorString)
{
  if (!attrVal.IsHolding<ArrayType>())
    return false;

  ArrayType result;
  if (_ComputeFlattenedHelper(
          attrVal.UncheckedGet<ArrayType>(), indices, elementSize, &result, errorString))
  {
    *value = VtValue::Take(result);
  }

  return true;
}

bool UsdGeomPrimvar::ComputeFlattened(VtValue *value, UsdTimeCode time) const
{
  VtValue attrVal;
  if (!Get(&attrVal, time)) {
    return false;
  }

  // If the primvar attr value is not an array or if the primvar isn't
  // indexed, simply return the attribute value.
  if (!attrVal.IsArrayValued() || !IsIndexed()) {
    *value = VtValue::Take(attrVal);
    return true;
  }

  VtIntArray indices;
  if (!GetIndices(&indices, time)) {
    TF_CODING_ERROR("No indices authored for indexed primvar <%s>.", _attr.GetPath().GetText());
    return false;
  }

  std::string errStr;
  bool res = ComputeFlattened(value, attrVal, indices, GetElementSize(), &errStr);
  if (!errStr.empty()) {
    TF_WARN("For primvar %s: %s", UsdDescribe(_attr).c_str(), errStr.c_str());
  }
  return res;
}

bool UsdGeomPrimvar::ComputeFlattened(VtValue *value,
                                      const VtValue &attrVal,
                                      const VtIntArray &indices,
                                      std::string *errStr)
{
  return ComputeFlattened(value, attrVal, indices, 1, errStr);
}

bool UsdGeomPrimvar::ComputeFlattened(VtValue *value,
                                      const VtValue &attrVal,
                                      const VtIntArray &indices,
                                      int elementSize,
                                      std::string *errStr)
{
  // If the primvar attr value is not an array simply return the
  // attribute value.
  if (!attrVal.IsArrayValued()) {
    *value = attrVal;
    return true;
  }

  // Handle all known supported array value types.
  bool foundSupportedType =
      _ComputeFlattenedArray<VtVec2fArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec2dArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec2iArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec2hArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec3fArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec3dArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec3iArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec3hArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec4fArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec4dArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec4iArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtVec4hArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtMatrix3dArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtMatrix4dArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtStringArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtDoubleArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtIntArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtUIntArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtFloatArray>(attrVal, indices, elementSize, value, errStr) ||
      _ComputeFlattenedArray<VtHalfArray>(attrVal, indices, elementSize, value, errStr);

  if (!foundSupportedType && errStr) {
    std::string thisErr = TfStringPrintf("Unsupported indexed primvar value type %s.",
                                         attrVal.GetTypeName().c_str());
    *errStr = errStr->empty() ? thisErr : *errStr + "\n" + thisErr;
  }

  return !value->IsEmpty();
}

UsdGeomPrimvar::UsdGeomPrimvar(const UsdPrim &prim,
                               const TfToken &primvarName,
                               const SdfValueTypeName &typeName)
    : _idTargetStatus(IdTargetUninitialized)
{
  TF_VERIFY(prim);

  TfToken attrName = _MakeNamespaced(primvarName);

  if (!attrName.IsEmpty()) {
    _attr = prim.CreateAttribute(attrName, typeName, /* custom = */ false);
  }
  // If a problem occurred, an error should already have been issued,
  // and _attr will be invalid, which is what we want
}

// Note! caller must ensure that _idTargetStatus == IdTargetPossible before
// calling.
UsdRelationship UsdGeomPrimvar::_GetIdTargetRel(bool create) const
{
  if (create) {
    return _attr.GetPrim().CreateRelationship(_idTargetRelName);
  }
  else {
    return _attr.GetPrim().GetRelationship(_idTargetRelName);
  }
}

bool UsdGeomPrimvar::IsIdTarget() const
{
  return _ComputeIdTargetPossibility() && !_idTargetRelName.IsEmpty() && _GetIdTargetRel(false);
}

bool UsdGeomPrimvar::SetIdTarget(const SdfPath &path) const
{
  if (!_ComputeIdTargetPossibility()) {
    TF_CODING_ERROR(
        "Can only set ID Target for string or string[] typed"
        " primvars (primvar type is '%s')",
        _attr.GetTypeName().GetAsToken().GetText());
    return false;
  }

  if (UsdRelationship rel = _GetIdTargetRel(true)) {
    SdfPathVector targets;
    targets.push_back(path.IsEmpty() ? _attr.GetPrimPath() : path);
    return rel.SetTargets(targets);
  }
  return false;
}

template<> bool UsdGeomPrimvar::Get(std::string *value, UsdTimeCode time) const
{
  // check if there is a relationship and if so use the target path string to
  // get the string value.
  if (_ComputeIdTargetPossibility()) {
    if (UsdRelationship rel = _GetIdTargetRel(false)) {
      SdfPathVector targets;
      if (rel.GetForwardedTargets(&targets) && targets.size() == 1) {
        *value = targets[0].GetString();
        return true;
      }
      return false;
    }
  }

  return _attr.Get(value, time);
}

// XXX: for now we just take the first.  here's an idea for how
// it'd work for multiple targets:
//   string[] primvars:handleids (interpolation = "uniform")
//   int[]    primvars:handleids:indices = [0, 1, 1, 1, 0, ...., 1]
//   rel      primvars:handleids:idFrom = [</a/t1>, </a/t2>]
template<> bool UsdGeomPrimvar::Get(VtStringArray *value, UsdTimeCode time) const
{
  // check if there is a relationship and if so use the target path string to
  // get the string value... Just take the first target, for now.
  if (_ComputeIdTargetPossibility()) {
    if (UsdRelationship rel = _GetIdTargetRel(false)) {
      value->clear();
      SdfPathVector targets;
      if (rel.GetForwardedTargets(&targets) && targets.size() > 1) {
        value->push_back(targets[0].GetString());
        return true;
      }
      return false;
    }
  }

  return _attr.Get(value, time);
}

template<> bool UsdGeomPrimvar::Get(VtValue *value, UsdTimeCode time) const
{
  if (_ComputeIdTargetPossibility()) {
    const SdfValueTypeName &typeName = _attr.GetTypeName();
    if (typeName == SdfValueTypeNames->String) {
      std::string s;
      bool ret = Get(&s, time);
      if (ret) {
        *value = VtValue(s);
      }
      return ret;
    }
    else if (typeName == SdfValueTypeNames->StringArray) {
      VtStringArray s;
      bool ret = Get(&s, time);
      if (ret) {
        *value = VtValue(s);
      }
      return ret;
    }
  }

  return _attr.Get(value, time);
}

bool UsdGeomPrimvar::GetTimeSamples(std::vector<double> *times) const
{
  return GetTimeSamplesInInterval(GfInterval::GetFullInterval(), times);
}

bool UsdGeomPrimvar::GetTimeSamplesInInterval(const GfInterval &interval,
                                              std::vector<double> *times) const
{
  if (IsIndexed()) {
    if (UsdAttribute indicesAttr = _GetIndicesAttr(false)) {
      return UsdAttribute::GetUnionedTimeSamplesInInterval({_attr, indicesAttr}, interval, times);
    }
  }

  return _attr.GetTimeSamplesInInterval(interval, times);
}

bool UsdGeomPrimvar::ValueMightBeTimeVarying() const
{
  if (IsIndexed()) {
    if (UsdAttribute indicesAttr = _GetIndicesAttr(false)) {
      if (indicesAttr.ValueMightBeTimeVarying()) {
        return true;
      }
    }
  }

  return _attr.ValueMightBeTimeVarying();
}

TfToken UsdGeomPrimvar::GetPrimvarName() const
{
  std::string const &fullName = _attr.GetName().GetString();

  std::pair<std::string, bool> res = SdfPath::StripPrefixNamespace(fullName,
                                                                   _tokens->primvarsPrefix);

  return res.second ? TfToken(res.first) : TfToken();
}

bool UsdGeomPrimvar::NameContainsNamespaces() const
{
  static const size_t primvarsPrefixLen = _tokens->primvarsPrefix.GetString().size();
  return (_attr.GetName().GetString().find(':', primvarsPrefixLen) != std::string::npos);
}

bool UsdGeomPrimvar::_ComputeIdTargetPossibility() const
{
  // Read the current value.
  _IdTargetStatus status = _idTargetStatus.load();

  if (status == IdTargetUninitialized) {
    // Attempt to take it to Initializing.
    if (_idTargetStatus.compare_exchange_strong(status, IdTargetInitializing)) {
      // We get to do the initialization.
      if (!_attr) {
        _idTargetStatus = IdTargetImpossible;
      }
      else {
        // Set the rel target name.
        const SdfValueTypeName &typeName = _attr.GetTypeName();
        if (typeName == SdfValueTypeNames->String || typeName == SdfValueTypeNames->StringArray) {
          std::string name(_attr.GetName().GetString());
          _idTargetRelName = TfToken(name.append(_tokens->idFrom.GetText()));
          _idTargetStatus = status = IdTargetPossible;
        }
        else {
          _idTargetStatus = status = IdTargetImpossible;
        }
      }
    }
  }
  while (status == IdTargetInitializing) {
    std::this_thread::yield();
    status = _idTargetStatus.load();
  }
  return status == IdTargetPossible;
}

PXR_NAMESPACE_CLOSE_SCOPE
