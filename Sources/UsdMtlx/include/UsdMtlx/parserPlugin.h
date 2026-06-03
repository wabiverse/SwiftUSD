//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USDMTLX_PARSER_PLUGIN_H
#define PXR_USD_USDMTLX_PARSER_PLUGIN_H

#include "Ndr/declare.h"
#include "Ndr/parserPlugin.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

// Forward declarations
class NdrNode;
struct NdrNodeDiscoveryResult;

/// Parses nodes in MaterialX files.
class UsdMtlxParserPlugin : public NdrParserPlugin {
 public:
  UsdMtlxParserPlugin() = default;
  ~UsdMtlxParserPlugin() override = default;

  NdrNodeUniquePtr Parse(const NdrNodeDiscoveryResult &discoveryResult) override;
  const NdrTokenVec &GetDiscoveryTypes() const override;
  const TfToken &GetSourceType() const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_USD_USDMTLX_PARSER_PLUGIN_H
