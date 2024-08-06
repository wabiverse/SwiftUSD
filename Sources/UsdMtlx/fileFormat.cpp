//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdMtlx/fileFormat.h"
#include "Tf/pathUtils.h"
#include "Trace/traceImpl.h"
#include "Usd/stage.h"
#include "Usd/usdaFileFormat.h"
#include "UsdMtlx/reader.h"
#include "UsdMtlx/utils.h"
#include "pxr/pxrns.h"

#include <MaterialX/MXCoreDocument.h>
#include <MaterialX/MXFormatXmlIo.h>

namespace mx = MaterialX;

PXR_NAMESPACE_OPEN_SCOPE

namespace {

template<typename R> static bool _Read(UsdStagePtr stage, R &&reader)
{
  try {
    auto doc = reader();
    if (doc) {
      UsdMtlxRead(doc, stage);
      return true;
    }
  }
  catch (mx::ExceptionFoundCycle &x) {
    TF_RUNTIME_ERROR("MaterialX cycle found: %s\n", x.what());
    return false;
  }
  catch (mx::Exception &x) {
    TF_RUNTIME_ERROR("MaterialX error: %s\n", x.what());
    return false;
  }
  return false;
}

}  // anonymous namespace

TF_DEFINE_PUBLIC_TOKENS(UsdMtlxFileFormatTokens, USDMTLX_FILE_FORMAT_TOKENS);

TF_REGISTRY_FUNCTION(TfType)
{
  SDF_DEFINE_FILE_FORMAT(UsdMtlxFileFormat, SdfFileFormat);
}

UsdMtlxFileFormat::UsdMtlxFileFormat()
    : SdfFileFormat(UsdMtlxFileFormatTokens->Id,
                    UsdMtlxFileFormatTokens->Version,
                    UsdMtlxFileFormatTokens->Target,
                    UsdMtlxFileFormatTokens->Id)
{
}

UsdMtlxFileFormat::~UsdMtlxFileFormat() {}

SdfAbstractDataRefPtr UsdMtlxFileFormat::InitData(const FileFormatArguments &args) const
{
  return SdfFileFormat::InitData(args);
}

bool UsdMtlxFileFormat::CanRead(const std::string &filePath) const
{
  // XXX -- MaterialX doesn't provide this function.  We should attempt
  //        to parse XML as far as finding the first 'materialx' node.

  // XXX -- Emergency backup test.  This should be removed when the
  //        proper test described above is implemented because the
  //        actual filename extension shouldn't matter.
  const auto extension = TfGetExtension(filePath);
  if (extension != this->GetFormatId()) {
    return false;
  }

  return true;
}

bool UsdMtlxFileFormat::Read(SdfLayer *layer,
                             const std::string &resolvedPath,
                             bool metadataOnly) const
{
  TRACE_FUNCTION();

  auto stage = UsdStage::CreateInMemory();
  if (!_Read(stage, [&resolvedPath]() { return UsdMtlxReadDocument(resolvedPath); })) {
    return false;
  }

  layer->TransferContent(stage->GetRootLayer());
  return true;
}

bool UsdMtlxFileFormat::WriteToFile(const SdfLayer &layer,
                                    const std::string &filePath,
                                    const std::string &comment,
                                    const FileFormatArguments &args) const
{
  return false;
}

bool UsdMtlxFileFormat::ReadFromString(SdfLayer *layer, const std::string &str) const
{
  TRACE_FUNCTION();

  auto stage = UsdStage::CreateInMemory();
  if (!_Read(stage, [&str]() { return UsdMtlxGetDocumentFromString(str); })) {
    return false;
  }

  layer->TransferContent(stage->GetRootLayer());
  return true;
}

bool UsdMtlxFileFormat::WriteToString(const SdfLayer &layer,
                                      std::string *str,
                                      const std::string &comment) const
{
  return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)->WriteToString(layer, str, comment);
}

bool UsdMtlxFileFormat::WriteToStream(const SdfSpecHandle &spec,
                                      std::ostream &out,
                                      size_t indent) const
{
  return SdfFileFormat::FindById(UsdUsdaFileFormatTokens->Id)->WriteToStream(spec, out, indent);
}

PXR_NAMESPACE_CLOSE_SCOPE
