//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_ADAPTER_MANAGER_H
#define PXR_USD_IMAGING_USD_IMAGING_ADAPTER_MANAGER_H

#include "pxr/pxrns.h"

#include "Usd/prim.h"

#include <OneTBB/tbb/concurrent_unordered_map.h>

PXR_NAMESPACE_OPEN_SCOPE

using UsdImagingAPISchemaAdapterSharedPtr = std::shared_ptr<class UsdImagingAPISchemaAdapter>;
using UsdImagingPrimAdapterSharedPtr = std::shared_ptr<class UsdImagingPrimAdapter>;

/// \class UsdImaging_AdapterManager
///
/// Computes the prim and API schema adapters that are needed to compute the
/// HdSceneIndexPrim from a UsdPrim.
///
class UsdImaging_AdapterManager {
 public:
  UsdImaging_AdapterManager();
  void Reset();

  struct AdapterEntry {
    AdapterEntry(const UsdImagingAPISchemaAdapterSharedPtr &adapter,
                 const TfToken &appliedInstanceName = TfToken())
        : adapter(adapter), appliedInstanceName(appliedInstanceName)
    {
    }

    // This is either an API schema adapter or the prim adapter
    // wrapped as an API schema adapter.
    UsdImagingAPISchemaAdapterSharedPtr adapter;
    // Instance name for an multi-apply API schema.
    //
    // For example the prepending the apiSchema to CollectionAPI:lightLink
    // a USD prim will use the CollectionAPI adapter with
    // appliedInstancedName "lightLink".
    TfToken appliedInstanceName;
  };

  using AdapterEntries = TfSmallVector<AdapterEntry, 8>;

  struct AdaptersEntry {
    // Ordered. And includes the primAdapter wrapped as a an
    // API schema adapter.
    AdapterEntries allAdapters;

    // Just the prim adapter for the prim type.
    UsdImagingPrimAdapterSharedPtr primAdapter;
  };

  // Look-up all adapters needed to serve a prim.
  const AdaptersEntry &LookupAdapters(const UsdPrim &prim);

 private:
  const AdaptersEntry &_LookupAdapters(const UsdPrimTypeInfo &typeInfo);

  // A prim adapter together with an API schema wrapping the prim
  // adapter.
  struct _WrappedPrimAdapterEntry {
    UsdImagingPrimAdapterSharedPtr primAdapter;
    UsdImagingAPISchemaAdapterSharedPtr apiSchemaAdapter;
  };

  // Concurrent because it could
  // be potentially filled during concurrent GetPrim calls rather than
  // just during single-threaded population.
  using _PrimTypeToWrappedPrimAdapterEntry =
      tbb::concurrent_unordered_map<TfToken, _WrappedPrimAdapterEntry, TfHash>;
  using _SchemaNameToAPISchemaAdapter =
      tbb::concurrent_unordered_map<TfToken, UsdImagingAPISchemaAdapterSharedPtr, TfHash>;
  // Use UsdPrimTypeInfo pointer as key because they are guaranteed to be
  // cached at least as long as the stage is open.
  using _TypeInfoToAdaptersEntry =
      tbb::concurrent_unordered_map<const UsdPrimTypeInfo *, AdaptersEntry, TfHash>;

  const _WrappedPrimAdapterEntry &_LookupWrappedPrimAdapter(const TfToken &primType);

  UsdImagingAPISchemaAdapterSharedPtr _LookupAPISchemaAdapter(const TfToken &schemaName);

  AdaptersEntry _ComputeAdapters(const UsdPrimTypeInfo &typeInfo);

  _WrappedPrimAdapterEntry _ComputeWrappedPrimAdapter(const TfToken &schemaName);

  _PrimTypeToWrappedPrimAdapterEntry _primTypeToWrappedPrimAdapterEntry;
  _SchemaNameToAPISchemaAdapter _schemaNameToAPISchemaAdapter;
  _TypeInfoToAdaptersEntry _typeInfoToAdaptersEntry;

  const std::vector<UsdImagingAPISchemaAdapterSharedPtr> _keylessAPISchemaAdapters;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
