//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_CONE_ADAPTER_H
#define PXR_USD_IMAGING_USD_IMAGING_CONE_ADAPTER_H

/// \file usdImaging/coneAdapter.h

#include "UsdImaging/api.h"
#include "UsdImaging/gprimAdapter.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdGeomCone;

/// \class UsdImagingConeAdapter
///
/// Delegate support for UsdGeomCone.
///
class UsdImagingConeAdapter : public UsdImagingGprimAdapter {
 public:
  typedef UsdImagingGprimAdapter BaseAdapter;

  // Number of radial segments on a circular cross-section of the cone.
  static constexpr size_t numRadial = 10;

  UsdImagingConeAdapter() : UsdImagingGprimAdapter() {}
  USDIMAGING_API
  virtual ~UsdImagingConeAdapter();

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

  USDIMAGING_API
  HdDirtyBits ProcessPropertyChange(UsdPrim const &prim,
                                    SdfPath const &cachePath,
                                    TfToken const &propertyName) override;

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

  // ---------------------------------------------------------------------- //
  /// \name Data access
  // ---------------------------------------------------------------------- //

  USDIMAGING_API
  VtValue GetTopology(UsdPrim const &prim,
                      SdfPath const &cachePath,
                      UsdTimeCode time) const override;

  // Override the implemetation in GprimAdapter since we don't fetch the
  // points attribute for implicit primitives.
  USDIMAGING_API
  VtValue GetPoints(UsdPrim const &prim, UsdTimeCode time) const override;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_IMAGING_USD_IMAGING_CONE_ADAPTER_H
