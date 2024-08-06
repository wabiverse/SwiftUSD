//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_FLATTENED_XFORM_DATA_SOURCE_PROVIDER_H
#define PXR_IMAGING_HD_FLATTENED_XFORM_DATA_SOURCE_PROVIDER_H

#include "Hd/api.h"

#include "Hd/flattenedDataSourceProvider.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdFlattenedXformDataSourceProvider : public HdFlattenedDataSourceProvider {
  HD_API
  HdContainerDataSourceHandle GetFlattenedDataSource(const Context &) const override;

  HD_API
  void ComputeDirtyLocatorsForDescendants(HdDataSourceLocatorSet *locators) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_FLATTENED_XFORM_DATA_SOURCE_PROVIDER_H
