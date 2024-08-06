//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdShade/output.h"
#include "pxr/pxrns.h"

#include "UsdShade/connectableAPI.h"
#include "UsdShade/input.h"
#include "UsdShade/utils.h"

#include "Sdf/schema.h"

#include "UsdShade/connectableAPI.h"

#include <algorithm>
#include <stdlib.h>

PXR_NAMESPACE_OPEN_SCOPE

using std::string;
using std::vector;

TF_DEFINE_PRIVATE_TOKENS(_tokens, (renderType));

UsdShadeOutput::UsdShadeOutput(const UsdAttribute &attr) : _attr(attr) {}

TfToken UsdShadeOutput::GetBaseName() const
{
  return TfToken(SdfPath::StripPrefixNamespace(GetFullName(), UsdShadeTokens->outputs).first);
}

SdfValueTypeName UsdShadeOutput::GetTypeName() const
{
  return _attr.GetTypeName();
}

static TfToken _GetOutputAttrName(const TfToken outputName)
{
  return TfToken(UsdShadeTokens->outputs.GetString() + outputName.GetString());
}

UsdShadeOutput::UsdShadeOutput(UsdPrim prim, TfToken const &name, SdfValueTypeName const &typeName)
{
  // XXX what do we do if the type name doesn't match and it exists already?
  TfToken attrName = _GetOutputAttrName(name);
  _attr = prim.GetAttribute(attrName);
  if (!_attr) {
    _attr = prim.CreateAttribute(attrName, typeName, /* custom = */ false);
  }
}

bool UsdShadeOutput::Set(const VtValue &value, UsdTimeCode time) const
{
  if (UsdAttribute attr = GetAttr()) {
    return attr.Set(value, time);
  }
  return false;
}

bool UsdShadeOutput::SetRenderType(TfToken const &renderType) const
{
  return _attr.SetMetadata(_tokens->renderType, renderType);
}

TfToken UsdShadeOutput::GetRenderType() const
{
  TfToken renderType;
  _attr.GetMetadata(_tokens->renderType, &renderType);
  return renderType;
}

bool UsdShadeOutput::HasRenderType() const
{
  return _attr.HasMetadata(_tokens->renderType);
}

NdrTokenMap UsdShadeOutput::GetSdrMetadata() const
{
  NdrTokenMap result;

  VtDictionary sdrMetadata;
  if (GetAttr().GetMetadata(UsdShadeTokens->sdrMetadata, &sdrMetadata)) {
    for (const auto &it : sdrMetadata) {
      result[TfToken(it.first)] = TfStringify(it.second);
    }
  }

  return result;
}

std::string UsdShadeOutput::GetSdrMetadataByKey(const TfToken &key) const
{
  VtValue val;
  GetAttr().GetMetadataByDictKey(UsdShadeTokens->sdrMetadata, key, &val);
  return TfStringify(val);
}

void UsdShadeOutput::SetSdrMetadata(const NdrTokenMap &sdrMetadata) const
{
  for (auto &i : sdrMetadata) {
    SetSdrMetadataByKey(i.first, i.second);
  }
}

void UsdShadeOutput::SetSdrMetadataByKey(const TfToken &key, const std::string &value) const
{
  GetAttr().SetMetadataByDictKey(UsdShadeTokens->sdrMetadata, key, value);
}

bool UsdShadeOutput::HasSdrMetadata() const
{
  return GetAttr().HasMetadata(UsdShadeTokens->sdrMetadata);
}

bool UsdShadeOutput::HasSdrMetadataByKey(const TfToken &key) const
{
  return GetAttr().HasMetadataDictKey(UsdShadeTokens->sdrMetadata, key);
}

void UsdShadeOutput::ClearSdrMetadata() const
{
  GetAttr().ClearMetadata(UsdShadeTokens->sdrMetadata);
}

void UsdShadeOutput::ClearSdrMetadataByKey(const TfToken &key) const
{
  GetAttr().ClearMetadataByDictKey(UsdShadeTokens->sdrMetadata, key);
}

/* static */
bool UsdShadeOutput::IsOutput(const UsdAttribute &attr)
{
  return attr && attr.IsDefined() &&
         TfStringStartsWith(attr.GetName().GetString(), UsdShadeTokens->outputs);
}

bool UsdShadeOutput::CanConnect(const UsdAttribute &source) const
{
  return UsdShadeConnectableAPI::CanConnect(*this, source);
}

bool UsdShadeOutput::CanConnect(const UsdShadeInput &sourceInput) const
{
  return CanConnect(sourceInput.GetAttr());
}

bool UsdShadeOutput::CanConnect(const UsdShadeOutput &sourceOutput) const
{
  return CanConnect(sourceOutput.GetAttr());
}

bool UsdShadeOutput::ConnectToSource(UsdShadeConnectionSourceInfo const &source,
                                     ConnectionModification const mod) const
{
  return UsdShadeConnectableAPI::ConnectToSource(*this, source, mod);
}

bool UsdShadeOutput::ConnectToSource(UsdShadeConnectableAPI const &source,
                                     TfToken const &sourceName,
                                     UsdShadeAttributeType const sourceType,
                                     SdfValueTypeName typeName) const
{
  return UsdShadeConnectableAPI::ConnectToSource(*this, source, sourceName, sourceType, typeName);
}

bool UsdShadeOutput::ConnectToSource(SdfPath const &sourcePath) const
{
  return UsdShadeConnectableAPI::ConnectToSource(*this, sourcePath);
}

bool UsdShadeOutput::ConnectToSource(UsdShadeInput const &sourceInput) const
{
  return UsdShadeConnectableAPI::ConnectToSource(*this, sourceInput);
}

bool UsdShadeOutput::ConnectToSource(UsdShadeOutput const &sourceOutput) const
{
  return UsdShadeConnectableAPI::ConnectToSource(*this, sourceOutput);
}

bool UsdShadeOutput::SetConnectedSources(
    std::vector<UsdShadeConnectionSourceInfo> const &sourceInfos) const
{
  return UsdShadeConnectableAPI::SetConnectedSources(*this, sourceInfos);
}

UsdShadeOutput::SourceInfoVector UsdShadeOutput::GetConnectedSources(
    SdfPathVector *invalidSourcePaths) const
{
  return UsdShadeConnectableAPI::GetConnectedSources(*this, invalidSourcePaths);
}

bool UsdShadeOutput::GetConnectedSource(UsdShadeConnectableAPI *source,
                                        TfToken *sourceName,
                                        UsdShadeAttributeType *sourceType) const
{
  return UsdShadeConnectableAPI::GetConnectedSource(*this, source, sourceName, sourceType);
}

bool UsdShadeOutput::GetRawConnectedSourcePaths(SdfPathVector *sourcePaths) const
{
  return UsdShadeConnectableAPI::GetRawConnectedSourcePaths(*this, sourcePaths);
}

bool UsdShadeOutput::HasConnectedSource() const
{
  return UsdShadeConnectableAPI::HasConnectedSource(*this);
}

bool UsdShadeOutput::IsSourceConnectionFromBaseMaterial() const
{
  return UsdShadeConnectableAPI::IsSourceConnectionFromBaseMaterial(*this);
}

bool UsdShadeOutput::DisconnectSource(UsdAttribute const &sourceAttr) const
{
  return UsdShadeConnectableAPI::DisconnectSource(*this, sourceAttr);
}

bool UsdShadeOutput::ClearSources() const
{
  return UsdShadeConnectableAPI::ClearSources(*this);
}

bool UsdShadeOutput::ClearSource() const
{
  return UsdShadeConnectableAPI::ClearSources(*this);
}

UsdShadeAttributeVector UsdShadeOutput::GetValueProducingAttributes(bool shaderOutputsOnly) const
{
  return UsdShadeUtils::GetValueProducingAttributes(*this, shaderOutputsOnly);
}

PXR_NAMESPACE_CLOSE_SCOPE
