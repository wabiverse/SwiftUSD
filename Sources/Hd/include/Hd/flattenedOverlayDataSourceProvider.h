//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_FLATTENED_OVERLAY_DATA_SOURCE_PROVIDER_H
#define PXR_IMAGING_HD_FLATTENED_OVERLAY_DATA_SOURCE_PROVIDER_H

#include "Hd/api.h"

#include "Hd/flattenedDataSourceProvider.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdFlattenedOverlayDataSourceProvider
///
/// Flattens a data source by using HdOverlayContainerDataSource.
///
class HdFlattenedOverlayDataSourceProvider : public HdFlattenedDataSourceProvider {
 public:
  HD_API
  HdContainerDataSourceHandle GetFlattenedDataSource(const Context &) const override;

  HD_API
  void ComputeDirtyLocatorsForDescendants(HdDataSourceLocatorSet *locators) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
