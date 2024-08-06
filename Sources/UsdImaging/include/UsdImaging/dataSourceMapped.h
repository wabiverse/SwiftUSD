//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_USD_IMAGING_USD_IMAGING_DATA_SOURCE_MAPPED_H
#define PXR_USD_IMAGING_USD_IMAGING_DATA_SOURCE_MAPPED_H

#include "UsdImaging/dataSourceAttribute.h"
#include "UsdImaging/dataSourceStageGlobals.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace UsdImagingDataSourceMapped_Impl {
using _ContainerMappingsSharedPtr = std::shared_ptr<struct _ContainerMappings>;
}

/// \class UsdImagingDataSourceMapped
///
/// A data source that is a (potentially nested) container for the values of
/// the attributes of a given UsdPrim.
///
/// That is, this container data source contains `HdSampledDataSource`s giving
/// the value of an attribute, either directly or in a nested fashion by
/// containing container data sources itself.
///
/// The mapping of attributes to locations in the (nested) container data
/// source can be specified through AttributeMapping. These locations are
/// relative to the UsdImagingDataSourceMapped itself. To compute the correct
/// data source locators for invalidation purposes, the location of the
/// UsdImagingDataSourceMapped needs to be given to AttributeMappings so that
/// absolute locators (that is relative to the prim data source) can be
/// computed.
///
class UsdImagingDataSourceMapped : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(UsdImagingDataSourceMapped);

  /// Signature of function to compute data source from attribute.
  ///
  /// This could be generalized to HdDataSourceBaseHandle but we use
  /// HdSampledDataSourceHandle as result instead so that we can use
  /// the UsdImagingDataSourceAttributeNew function pointer.
  ///
  using DataSourceAttributeFactory =
      HdSampledDataSourceHandle(const UsdAttribute &,
                                const UsdImagingDataSourceStageGlobals &,
                                const SdfPath &,
                                const HdDataSourceLocator &);
  using DataSourceAttributeFactoryFn = std::function<DataSourceAttributeFactory>;
  using DataSourceAttributeFactoryPtr = DataSourceAttributeFactory *;

  /// Specify how one attribute on given Usd prim maps to data source in
  /// this (nested) container data source.
  struct AttributeMapping final {
    /// Name of attribute on Usd Prim.
    ///
    TfToken usdName;

    /// Corresponding location in this data source.
    ///
    /// Has to be non-empty. If length is greater than one, nested
    /// container data sources will be created.
    ///
    HdDataSourceLocator hdLocator;

    /// Function to compute data source from UsdAttribute.
    ///
    /// Defaults to the appropriate overload of
    /// UsdImagingDataSourceAttributeNew.
    ///
    /// Clients can implement custom behavior. For example, following
    /// the connection of a UsdShadeOutput and return the path of the
    /// connected prim.
    ///
    DataSourceAttributeFactoryFn factory = DataSourceAttributeFactoryPtr(
        UsdImagingDataSourceAttributeNew);
  };

  /// Specify how attributes on given Usd prim maps to data sources in
  /// this (nested) container data source.
  class AttributeMappings final {
   public:
    /// dataSourcePrefix is the location of this
    /// UsdImagingDataSourceMapped within a prim data source.
    USDIMAGING_API
    AttributeMappings(const std::vector<AttributeMapping> &mappings,
                      const HdDataSourceLocator &datasourcePrefix);

    USDIMAGING_API
    ~AttributeMappings();

   private:
    friend class UsdImagingDataSourceMapped;

    using _ContainerMappingsSharedPtr =
        UsdImagingDataSourceMapped_Impl::_ContainerMappingsSharedPtr;

    // Flat list with absolute locators for invalidation.
    std::vector<AttributeMapping> _absoluteMappings;
    // Nested list to implement HdContainerDataSource::Get.
    _ContainerMappingsSharedPtr _containerMappings;
  };

  USDIMAGING_API
  TfTokenVector GetNames() override;

  USDIMAGING_API
  HdDataSourceBaseHandle Get(const TfToken &name) override;

  USDIMAGING_API
  static HdDataSourceLocatorSet Invalidate(const TfTokenVector &usdNames,
                                           const AttributeMappings &mappings);

  USDIMAGING_API
  ~UsdImagingDataSourceMapped() override;

 private:
  using _ContainerMappingsSharedPtr = UsdImagingDataSourceMapped_Impl::_ContainerMappingsSharedPtr;

  USDIMAGING_API
  UsdImagingDataSourceMapped(UsdPrim const &usdPrim,
                             const SdfPath &sceneIndexPath,
                             const AttributeMappings &mappings,
                             const UsdImagingDataSourceStageGlobals &stageGlobals);

  UsdImagingDataSourceMapped(UsdPrim const &usdPrim,
                             const SdfPath &sceneIndexPath,
                             const _ContainerMappingsSharedPtr &containerMappings,
                             const UsdImagingDataSourceStageGlobals &stageGlobals);

  UsdPrim _usdPrim;
  const SdfPath _sceneIndexPath;
  _ContainerMappingsSharedPtr const _containerMappings;
  const UsdImagingDataSourceStageGlobals &_stageGlobals;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
