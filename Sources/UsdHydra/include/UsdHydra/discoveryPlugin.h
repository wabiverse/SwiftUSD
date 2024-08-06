//
// Copyright 2018 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_USD_HYDRA_DISCOVERY_PLUGIN_H
#define PXR_USD_USD_HYDRA_DISCOVERY_PLUGIN_H

#include "Tf/token.h"
#include "UsdHydra/api.h"
#include "pxr/pxrns.h"

#include "Ndr/declare.h"
#include "Ndr/discoveryPlugin.h"
#include "Ndr/parserPlugin.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdHydraDiscoveryPlugin : public NdrDiscoveryPlugin {
 public:
  UsdHydraDiscoveryPlugin() = default;

  ~UsdHydraDiscoveryPlugin() override = default;

  virtual NdrNodeDiscoveryResultVec DiscoverNodes(const Context &context) override;

  virtual const NdrStringVec &GetSearchURIs() const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_USD_HYDRA_DISCOVERY_PLUGIN_H
