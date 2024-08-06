//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_SHADE_SHADER_DEF_PARSER_H
#define PXR_USD_USD_SHADE_SHADER_DEF_PARSER_H

#include "UsdShade/api.h"

#include "Ndr/declare.h"
#include "Ndr/discoveryPlugin.h"
#include "Ndr/parserPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdStageCache;

/// \class UsdShadeShaderDefParserPlugin
///
/// Parses shader definitions represented using USD scene description using the
/// schemas provided by UsdShade.
///
class UsdShadeShaderDefParserPlugin : public NdrParserPlugin {
 public:
  USDSHADE_API
  UsdShadeShaderDefParserPlugin() = default;

  USDSHADE_API
  ~UsdShadeShaderDefParserPlugin() override = default;

  USDSHADE_API
  NdrNodeUniquePtr Parse(const NdrNodeDiscoveryResult &discoveryResult) override;

  USDSHADE_API
  const NdrTokenVec &GetDiscoveryTypes() const override;

  USDSHADE_API
  const TfToken &GetSourceType() const override;

 private:
  static UsdStageCache _cache;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_USD_SHADE_SHADER_DEF_PARSER_H
