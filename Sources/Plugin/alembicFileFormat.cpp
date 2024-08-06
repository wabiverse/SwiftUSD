//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Plugin/usdAbc/alembicFileFormat.h"
#include "pxr/pxrns.h"

#include "Plugin/usdAbc/alembicData.h"
#include "Usd/usdaFileFormat.h"

#include "Sdf/layer.h"

#include "Trace/traceImpl.h"

#include "Tf/fileUtils.h"
#include "Tf/pathUtils.h"
#include "Tf/registryManager.h"
#include "Tf/staticData.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

using std::string;

TF_DEFINE_PUBLIC_TOKENS(UsdAbcAlembicFileFormatTokens, USDABC_ALEMBIC_FILE_FORMAT_TOKENS);

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(UsdAbcAlembicFileFormat, SdfFileFormat);
}

UsdAbcAlembicFileFormat::UsdAbcAlembicFileFormat()
    : SdfFileFormat(UsdAbcAlembicFileFormatTokens->Id,
                    UsdAbcAlembicFileFormatTokens->Version,
                    UsdAbcAlembicFileFormatTokens->Target,
                    UsdAbcAlembicFileFormatTokens->Id),
      _usda(SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id))
{
}

UsdAbcAlembicFileFormat::~UsdAbcAlembicFileFormat() {}

SdfAbstractDataRefPtr UsdAbcAlembicFileFormat::InitData(const FileFormatArguments &args) const
{
  return UsdAbc_AlembicData::New(args);
}

bool UsdAbcAlembicFileFormat::CanRead(const string &filePath) const
{
  // XXX: Add more verification of file header magic
  auto extension = TfGetExtension(filePath);
  if (extension.empty()) {
    return false;
  }

  return extension == this->GetFormatId();
}

bool UsdAbcAlembicFileFormat::Read(SdfLayer *layer,
                                   const string &resolvedPath,
                                   bool metadataOnly) const
{
  TRACE_FUNCTION();

  SdfAbstractDataRefPtr data = InitData(layer->GetFileFormatArguments());
  UsdAbc_AlembicDataRefPtr abcData = TfStatic_cast<UsdAbc_AlembicDataRefPtr>(data);
  if (!abcData->Open(resolvedPath)) {
    return false;
  }

  _SetLayerData(layer, data);
  return true;
}

bool UsdAbcAlembicFileFormat::_ReadDetached(SdfLayer *layer,
                                            const std::string &resolvedPath,
                                            bool metadataOnly) const
{
  return _ReadAndCopyLayerDataToMemory(layer, resolvedPath, metadataOnly);
}

bool UsdAbcAlembicFileFormat::WriteToFile(const SdfLayer &layer,
                                          const std::string &filePath,
                                          const std::string &comment,
                                          const FileFormatArguments &args) const
{
  // Write.
  SdfAbstractDataConstPtr data = _GetLayerData(layer);
  return TF_VERIFY(data) && UsdAbc_AlembicData::Write(data, filePath, comment);
}

bool UsdAbcAlembicFileFormat::ReadFromString(SdfLayer *layer, const std::string &str) const
{
  // XXX: For now, defer to the usda file format for this. May need to
  //      revisit this as the alembic reader gets fully fleshed out.
  return _usda->ReadFromString(layer, str);
}

bool UsdAbcAlembicFileFormat::WriteToString(const SdfLayer &layer,
                                            std::string *str,
                                            const std::string &comment) const
{
  // XXX: For now, defer to the usda file format for this. May need to
  //      revisit this as the alembic reader gets fully fleshed out.
  return _usda->WriteToString(layer, str, comment);
}

bool UsdAbcAlembicFileFormat::WriteToStream(const SdfSpecHandle &spec,
                                            std::ostream &out,
                                            size_t indent) const
{
  // XXX: Because WriteToString() uses the usda file format and because
  //      a spec will always use it's own file format for writing we'll
  //      get here trying to write an Alembic layer as usda.  So we
  //      turn around call usda.
  return _usda->WriteToStream(spec, out, indent);
}

PXR_NAMESPACE_CLOSE_SCOPE
