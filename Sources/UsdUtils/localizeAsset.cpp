//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
///
/// \file usdUtils/localizeAsset.cpp

#include "pxr/pxrns.h"

#include "Ar/asset.h"
#include "Ar/resolver.h"
#include "Ar/writableAsset.h"

#include "Sdf/assetPath.h"
#include "Tf/diagnostic.h"
#include "Tf/fileUtils.h"
#include "Tf/pathUtils.h"

#include "UsdUtils/assetLocalization.h"
#include "UsdUtils/assetLocalizationDelegate.h"
#include "UsdUtils/assetLocalizationPackage.h"
#include "UsdUtils/debugCodes.h"
#include "UsdUtils/localizeAsset.h"

#include "Trace/traceImpl.h"

#include <algorithm>

PXR_NAMESPACE_OPEN_SCOPE

class UsdUtils_LocalizedAssetBuilder : public UsdUtils_AssetLocalizationPackage {
 public:
  virtual bool Write(const std::string &localizationRoot) override
  {
    _localizationRoot = localizationRoot;

    return UsdUtils_AssetLocalizationPackage::Write(_localizationRoot);
  }

 protected:
  virtual bool _WriteToPackage(const std::string &src, const std::string &dest) override
  {
    auto &resolver = ArGetResolver();

    const std::string destPath = TfStringCatPaths(_localizationRoot, dest);
    ArResolvedPath srcResolvedPath = resolver.Resolve(src);
    ArResolvedPath destResolvedPath = resolver.ResolveForNewAsset(destPath);

    if (srcResolvedPath.empty()) {
      TF_WARN("Failed to resolve source path: %s", src.c_str());

      return false;
    }

    if (destResolvedPath.empty()) {
      TF_WARN("Failed to resolve source path: %s", dest.c_str());

      return false;
    }

    auto sourceAsset = resolver.OpenAsset(srcResolvedPath);
    auto destAsset = resolver.OpenAssetForWrite(destResolvedPath, ArResolver::WriteMode::Replace);

    if (!sourceAsset) {
      TF_WARN("Failed to open source asset: %s", src.c_str());
      return false;
    }

    if (!destAsset) {
      TF_WARN("Failed to open destination asset: %s", dest.c_str());
      return false;
    }

    constexpr size_t COPY_BUFFER_SIZE = 4096U;
    char buffer[COPY_BUFFER_SIZE];
    size_t dataRemaining = sourceAsset->GetSize();

    while (dataRemaining > 0) {
      size_t chunkSize = std::min(dataRemaining, COPY_BUFFER_SIZE);

      sourceAsset->Read(buffer, chunkSize, 0);
      destAsset->Write(buffer, chunkSize, 0);

      dataRemaining -= chunkSize;
    }

    return true;
  }

  std::string _localizationRoot;
};

bool UsdUtilsLocalizeAsset(const SdfAssetPath &assetPath,
                           const std::string &localizationDir,
                           bool editLayersInPlace,
                           std::function<UsdUtilsProcessingFunc> processingFunc)
{
  TRACE_FUNCTION();

  if (TfPathExists(localizationDir) && !TfIsDir(localizationDir)) {
    TF_CODING_ERROR("Unable to localize to non directory path: %s", localizationDir.c_str());
    return false;
  }

  UsdUtils_LocalizedAssetBuilder builder;

  builder.SetEditLayersInPlace(editLayersInPlace);
  builder.SetUserProcessingFunc(processingFunc);

  if (!builder.Build(assetPath, std::string())) {
    return false;
  }

  return builder.Write(localizationDir);
}

PXR_NAMESPACE_CLOSE_SCOPE
