//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_DATA_SOURCE_STAGE_H
#define PXR_USD_IMAGING_USD_IMAGING_DATA_SOURCE_STAGE_H

#include "Hd/dataSource.h"
#include "UsdImaging/api.h"

#include "Tf/declarePtrs.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DECLARE_REF_PTRS(UsdStage);

/// Returns a dataSource that contains UsdStage level data.  In particular, this
/// populates the HdarSystem data.
class UsdImagingDataSourceStage : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(UsdImagingDataSourceStage);

 public:  //  HdContainerDataSource overrides
  USDIMAGING_API
  TfTokenVector GetNames() override;

  USDIMAGING_API
  HdDataSourceBaseHandle Get(const TfToken &name) override;

 private:
  UsdImagingDataSourceStage(UsdStageRefPtr stage);

  UsdStageRefPtr _stage;
};

HD_DECLARE_DATASOURCE_HANDLES(UsdImagingDataSourceStage);

PXR_NAMESPACE_CLOSE_SCOPE

#endif
