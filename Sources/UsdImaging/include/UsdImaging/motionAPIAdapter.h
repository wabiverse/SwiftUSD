//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_MOTION_API_ADAPTER_H
#define PXR_USD_IMAGING_USD_IMAGING_MOTION_API_ADAPTER_H

#include "UsdImaging/api.h"
#include "UsdImaging/apiSchemaAdapter.h"
#include "UsdImaging/types.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"

#include "Usd/prim.h"

#include "Tf/token.h"

#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdImagingMotionAPIAdapter : public UsdImagingAPISchemaAdapter
{
public:
    using BaseAdapter = UsdImagingAPISchemaAdapter;

    USDIMAGING_API
    HdContainerDataSourceHandle GetImagingSubprimData(
        UsdPrim const& prim,
        TfToken const& subprim,
        TfToken const& appliedInstanceName,
        const UsdImagingDataSourceStageGlobals &stageGlobals) override;

    USDIMAGING_API
    HdDataSourceLocatorSet InvalidateImagingSubprim(
        UsdPrim const& prim,
        TfToken const& subprim,
        TfToken const& appliedInstanceName,
        TfTokenVector const& properties,
        UsdImagingPropertyInvalidationType invalidationType) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_USD_IMAGING_USD_IMAGING_MOTION_API_ADAPTER_H
