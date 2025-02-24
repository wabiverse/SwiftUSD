//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/usdcFileFormat.h"
#include "pxr/pxrns.h"

#include "Usd/usdFileFormat.h"
#include "Usd/usdaFileFormat.h"

#include "Sdf/fileFormat.h"
#include "Sdf/layer.h"
#include "Sdf/textFileFormat.h"

#include "Trace/traceImpl.h"

#include "Tf/registryManager.h"

#include "Usd/crateData.h"

#include <iosfwd>

PXR_NAMESPACE_OPEN_SCOPE

using std::string;

TF_DECLARE_WEAK_AND_REF_PTRS(Usd_CrateData);

TF_DEFINE_PUBLIC_TOKENS(UsdUsdcFileFormatTokens, USD_USDC_FILE_FORMAT_TOKENS);

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(UsdUsdcFileFormat, SdfFileFormat);
}

UsdUsdcFileFormat::UsdUsdcFileFormat()
    : SdfFileFormat(UsdUsdcFileFormatTokens->Id,
                    Usd_CrateData::GetSoftwareVersionToken(),
                    UsdUsdFileFormatTokens->Target,
                    UsdUsdcFileFormatTokens->Id)
{
}

UsdUsdcFileFormat::~UsdUsdcFileFormat() {}

SdfAbstractDataRefPtr UsdUsdcFileFormat::InitData(const FileFormatArguments &args) const
{
  auto newData = new Usd_CrateData(/* detached = */ false);

  // The pseudo-root spec must always exist in a layer's SdfData, so
  // add it here.
  newData->CreateSpec(SdfPath::AbsoluteRootPath(), SdfSpecTypePseudoRoot);
  return TfCreateRefPtr(newData);
}

SdfAbstractDataRefPtr UsdUsdcFileFormat::_InitDetachedData(const FileFormatArguments &args) const
{
  auto newData = new Usd_CrateData(/* detached = */ true);

  // The pseudo-root spec must always exist in a layer's SdfData, so
  // add it here.
  newData->CreateSpec(SdfPath::AbsoluteRootPath(), SdfSpecTypePseudoRoot);
  return TfCreateRefPtr(newData);
}

bool UsdUsdcFileFormat::CanRead(const string &filePath) const
{
  return Usd_CrateData::CanRead(filePath);
}

bool UsdUsdcFileFormat::_CanReadFromAsset(const string &filePath,
                                          const std::shared_ptr<ArAsset> &asset) const
{
  return Usd_CrateData::CanRead(filePath, asset);
}

bool UsdUsdcFileFormat::Read(SdfLayer *layer, const string &resolvedPath, bool metadataOnly) const
{
  TRACE_FUNCTION();
  return _ReadHelper(layer,
                     resolvedPath,
                     metadataOnly,
                     /* detached = */ false);
}

bool UsdUsdcFileFormat::_ReadDetached(SdfLayer *layer,
                                      const std::string &resolvedPath,
                                      bool metadataOnly) const
{
  TRACE_FUNCTION();
  return _ReadHelper(layer,
                     resolvedPath,
                     metadataOnly,
                     /* detached = */ true);
}

bool UsdUsdcFileFormat::_ReadFromAsset(SdfLayer *layer,
                                       const string &resolvedPath,
                                       const std::shared_ptr<ArAsset> &asset,
                                       bool metadataOnly,
                                       bool detached) const
{
  TRACE_FUNCTION();
  return _ReadHelper(layer, resolvedPath, metadataOnly, asset, detached);
}

template<class... Args>
bool UsdUsdcFileFormat::_ReadHelper(SdfLayer *layer,
                                    const std::string &resolvedPath,
                                    bool metadataOnly,
                                    Args &&...args) const
{
  SdfAbstractDataRefPtr data = InitData(layer->GetFileFormatArguments());
  auto crateData = TfDynamic_cast<Usd_CrateDataRefPtr>(data);

  if (!crateData || !crateData->Open(resolvedPath, std::forward<Args>(args)...)) {
    return false;
  }

  _SetLayerData(layer, data);
  return true;
}

bool UsdUsdcFileFormat::WriteToFile(const SdfLayer &layer,
                                    const std::string &filePath,
                                    const std::string &comment,
                                    const FileFormatArguments &args) const
{
  SdfAbstractDataConstPtr dataSource = _GetLayerData(layer);

  // XXX: WBN to avoid const-cast -- saving can't be non-mutating in general.
  if (auto const *constCrateData = dynamic_cast<Usd_CrateData const *>(get_pointer(dataSource))) {
    auto *crateData = const_cast<Usd_CrateData *>(constCrateData);
    return crateData->Export(filePath);
  }

  // Otherwise we're dealing with some arbitrary data object, just copy the
  // contents into the binary data.
  if (auto dataDest = TfDynamic_cast<Usd_CrateDataRefPtr>(InitData(FileFormatArguments()))) {
    dataDest->CopyFrom(dataSource);
    return dataDest->Export(filePath);
  }
  return false;
}

bool UsdUsdcFileFormat::SaveToFile(const SdfLayer &layer,
                                   const std::string &filePath,
                                   const std::string &comment,
                                   const FileFormatArguments &args) const
{
  SdfAbstractDataConstPtr dataSource = _GetLayerData(layer);

  // XXX: WBN to avoid const-cast -- saving can't be non-mutating in general.
  if (auto const *constCrateData = dynamic_cast<Usd_CrateData const *>(get_pointer(dataSource))) {
    auto *crateData = const_cast<Usd_CrateData *>(constCrateData);
    return crateData->Save(filePath);
  }

  TF_CODING_ERROR(
      "Called UsdUsdcFileFormat::SaveToFile with "
      "non-Crate-backed layer @%s@",
      layer.GetIdentifier().c_str());
  return false;
}

bool UsdUsdcFileFormat::ReadFromString(SdfLayer *layer, const std::string &str) const
{
  return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)->ReadFromString(layer, str);
}

bool UsdUsdcFileFormat::WriteToString(const SdfLayer &layer,
                                      std::string *str,
                                      const std::string &comment) const
{
  return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)->WriteToString(layer, str, comment);
}

bool UsdUsdcFileFormat::WriteToStream(const SdfSpecHandle &spec,
                                      std::ostream &out,
                                      size_t indent) const
{
  return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)->WriteToStream(spec, out, indent);
}

PXR_NAMESPACE_CLOSE_SCOPE
