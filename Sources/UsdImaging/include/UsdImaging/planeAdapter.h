//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_USD_IMAGING_USD_IMAGING_PLANE_ADAPTER_H
#define PXR_USD_IMAGING_USD_IMAGING_PLANE_ADAPTER_H

/// \file usdImaging/planeAdapter.h

#include "UsdImaging/api.h"
#include "UsdImaging/gprimAdapter.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

class UsdGeomPlane;

/// \class UsdImagingPlaneAdapter
///
/// Delegate support for UsdGeomPlane.
///
class UsdImagingPlaneAdapter : public UsdImagingGprimAdapter {
 public:
  typedef UsdImagingGprimAdapter BaseAdapter;

  UsdImagingPlaneAdapter() : UsdImagingGprimAdapter() {}
  USDIMAGING_API
  virtual ~UsdImagingPlaneAdapter();

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

  // Used by the legacyEngine.
  USDIMAGING_API
  static VtValue GetMeshPoints(UsdPrim const &prim, UsdTimeCode time);

  // Used by the legacyEngine.
  USDIMAGING_API
  static VtValue GetMeshTopology();
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_USD_IMAGING_USD_IMAGING_PLANE_ADAPTER_H
