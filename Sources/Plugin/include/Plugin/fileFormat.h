//
// Copyright 2019 Google LLC
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_USD_PLUGIN_USD_DRACO_FILE_FORMAT_H
#define PXR_USD_PLUGIN_USD_DRACO_FILE_FORMAT_H

#include "Sdf/fileFormat.h"
#include "pxr/pxrns.h"

#include <ostream>
#include <string>

PXR_NAMESPACE_OPEN_SCOPE

#define USDDRACO_FILE_FORMAT_TOKENS ((Id, "drc"))((Version, "1.3.5.0"))((Target, "usd"))

TF_DECLARE_PUBLIC_TOKENS(UsdDracoFileFormatTokens, USDDRACO_FILE_FORMAT_TOKENS);
TF_DECLARE_WEAK_AND_REF_PTRS(UsdDracoFileFormat);

/// \class UsdDracoFileFormat
///
/// Adds support for ireading Draco *.drc files.
///
class UsdDracoFileFormat : public SdfFileFormat {
 public:
  virtual bool CanRead(const std::string &file) const;
  virtual bool Read(SdfLayer *layer, const std::string &resolvedPath, bool metadataOnly) const;
  virtual bool ReadFromString(SdfLayer *layer, const std::string &str) const;
  virtual bool WriteToFile(const SdfLayer &layer,
                           const std::string &filePath,
                           const std::string &comment = std::string(),
                           const FileFormatArguments &args = FileFormatArguments()) const;
  virtual bool WriteToString(const SdfLayer &layer,
                             std::string *str,
                             const std::string &comment = std::string()) const;
  virtual bool WriteToStream(const SdfSpecHandle &spec, std::ostream &out, size_t indent) const;

 protected:
  SDF_FILE_FORMAT_FACTORY_ACCESS;

  virtual ~UsdDracoFileFormat();
  UsdDracoFileFormat();

 private:
  bool _ReadFromChars(
      SdfLayer *layer, const char *str, size_t size, bool metadataOnly, std::string *outErr) const;

  virtual bool _IsStreamingLayer(const SdfLayer &layer) const
  {
    return false;
  }
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_PLUGIN_USD_DRACO_FILE_FORMAT_H
