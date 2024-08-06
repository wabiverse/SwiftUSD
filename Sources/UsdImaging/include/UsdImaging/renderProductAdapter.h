//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_RENDER_PRODUCT_ADAPTER_H
#define PXR_USD_IMAGING_USD_IMAGING_RENDER_PRODUCT_ADAPTER_H

/// \file usdImaging/renderProductAdapter.h

#include "UsdImaging/api.h"
#include "UsdImaging/primAdapter.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class UsdImagingRenderProductAdapter
///
/// Adapter support for UsdRenderProduct for *only* the scene index (2.0) API.
///
/// \note For the legacy (UsdImagingDelegate and associated prim adapter API)
///       scenario, UsdImagingRenderSettingsAdapter handles the flattening of
///       products and vars.
///
class UsdImagingRenderProductAdapter : public UsdImagingPrimAdapter {
 public:
  using BaseAdapter = UsdImagingPrimAdapter;

  UsdImagingRenderProductAdapter() : UsdImagingPrimAdapter() {}

  USDIMAGING_API
  ~UsdImagingRenderProductAdapter() override;

  // ---------------------------------------------------------------------- //
  /// \name Scene Index Support
  // ---------------------------------------------------------------------- //

  USDIMAGING_API
  TfTokenVector GetImagingSubprims(UsdPrim const &prim) override;

  USDIMAGING_API
  TfToken GetImagingSubprimType(UsdPrim const &prim, TfToken const &subprim) override;

  USDIMAGING_API
  HdContainerDataSourceHandle GetImagingSubprimData(
      UsdPrim const &prim,
      TfToken const &subprim,
      const UsdImagingDataSourceStageGlobals &stageGlobals) override;

  USDIMAGING_API
  HdDataSourceLocatorSet InvalidateImagingSubprim(
      UsdPrim const &prim,
      TfToken const &subprim,
      TfTokenVector const &properties,
      UsdImagingPropertyInvalidationType invalidationType) override;

  // ---------------------------------------------------------------------- //
  /// \name Initialization
  // ---------------------------------------------------------------------- //

  USDIMAGING_API
  SdfPath Populate(UsdPrim const &prim,
                   UsdImagingIndexProxy *index,
                   UsdImagingInstancerContext const *instancerContext = nullptr) override;

  USDIMAGING_API
  bool IsSupported(UsdImagingIndexProxy const *index) const override;

  // ---------------------------------------------------------------------- //
  /// \name Parallel Setup and Resolve
  // ---------------------------------------------------------------------- //

  /// Thread Safe.
  USDIMAGING_API
  void TrackVariability(
      UsdPrim const &prim,
      SdfPath const &cachePath,
      HdDirtyBits *timeVaryingBits,
      UsdImagingInstancerContext const *instancerContext = nullptr) const override;

  /// Thread Safe.
  USDIMAGING_API
  void UpdateForTime(UsdPrim const &prim,
                     SdfPath const &cachePath,
                     UsdTimeCode time,
                     HdDirtyBits requestedBits,
                     UsdImagingInstancerContext const *instancerContext = nullptr) const override;

  // ---------------------------------------------------------------------- //
  /// \name Change Processing
  // ---------------------------------------------------------------------- //

  /// Returns a bit mask of attributes to be udpated, or
  /// HdChangeTracker::AllDirty if the entire prim must be resynchronized.
  USDIMAGING_API
  HdDirtyBits ProcessPropertyChange(UsdPrim const &prim,
                                    SdfPath const &cachePath,
                                    TfToken const &propertyName) override;

  USDIMAGING_API
  void MarkDirty(UsdPrim const &prim,
                 SdfPath const &cachePath,
                 HdDirtyBits dirty,
                 UsdImagingIndexProxy *index) override;

  // ---------------------------------------------------------------------- //
  /// \name Data access
  // ---------------------------------------------------------------------- //

  USDIMAGING_API
  VtValue Get(UsdPrim const &prim,
              SdfPath const &cachePath,
              TfToken const &key,
              UsdTimeCode time,
              VtIntArray *outIndices) const override;

 protected:
  USDIMAGING_API
  void _RemovePrim(SdfPath const &cachePath, UsdImagingIndexProxy *index) override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_IMAGING_USD_IMAGING_RENDER_PRODUCT_ADAPTER_H
