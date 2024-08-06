//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/geomSubsetAdapter.h"

#include "UsdImaging/dataSourceAttribute.h"
#include "UsdImaging/dataSourcePrim.h"
#include "UsdImaging/primAdapter.h"
#include "UsdImaging/types.h"

#include "Hd/changeTracker.h"
#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"
#include "Hd/dataSourceTypeDefs.h"
#include "Hd/geomSubsetSchema.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/retainedDataSource.h"
#include "Hd/tokens.h"
#include "Hd/types.h"

#include "Sdf/path.h"
#include "UsdGeom/subset.h"
#include "UsdGeom/tokens.h"

#include "Tf/diagnostic.h"
#include "Tf/registryManager.h"
#include "Tf/token.h"
#include "Tf/type.h"
#include "Vt/types.h"
#include "Vt/value.h"

#include "pxr/pxrns.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  using Adapter = UsdImagingGeomSubsetAdapter;
  TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter>>();
  t.SetFactory<UsdImagingPrimAdapterFactory<Adapter>>();
}

namespace {

/**
 * @brief Simple data source for converting values of UsdGeomSubset's
 * `elementType` to the corresponding values of HdGeomSubset's `type`.
 */
class _ElementTypeConversionDataSource : public HdTokenDataSource {
 public:
  using Time = HdSampledDataSource::Time;

  HD_DECLARE_DATASOURCE(_ElementTypeConversionDataSource);

  VtValue GetValue(const Time shutterOffset) override
  {
    return VtValue(GetTypedValue(shutterOffset));
  }

  TfToken GetTypedValue(const Time shutterOffset) override
  {
    if (!_source) {
      return TfToken();
    }

    // Translate the type token from USD to Hydra.
    const TfToken type = _source->GetTypedValue(shutterOffset);
    if (type == UsdGeomTokens->face) {
      return HdGeomSubsetSchemaTokens->typeFaceSet;
    }
    if (type == UsdGeomTokens->point) {
      return HdGeomSubsetSchemaTokens->typePointSet;
    }
    // TODO: USD also supports 'edge' and 'tetrahedron' types. These will
    // be added to Hydra in an upcoming change.
    TF_WARN("Unsupported GeomSubset type: %s", type.GetText());
    return TfToken();
  }

  bool GetContributingSampleTimesForInterval(const Time startTime,
                                             const Time endTime,
                                             std::vector<Time> *sampleTimes) override
  {
    if (!_source) {
      return false;
    }
    return _source->GetContributingSampleTimesForInterval(startTime, endTime, sampleTimes);
  }

 private:
  _ElementTypeConversionDataSource(const HdTokenDataSourceHandle &source) : _source(source) {}

  HdTokenDataSourceHandle _source;
};

}  // anonymous namespace

UsdImagingGeomSubsetAdapter::~UsdImagingGeomSubsetAdapter() = default;

// ---------------------------------------------------------------------- //
/// Scene Index Support
// ---------------------------------------------------------------------- //

TfTokenVector UsdImagingGeomSubsetAdapter::GetImagingSubprims(const UsdPrim &prim)
{
  return {TfToken()};
}

TfToken UsdImagingGeomSubsetAdapter::GetImagingSubprimType(const UsdPrim &prim,
                                                           const TfToken &subprim)
{
  if (subprim.IsEmpty()) {
    return HdPrimTypeTokens->geomSubset;
  }
  return TfToken();
}

HdContainerDataSourceHandle UsdImagingGeomSubsetAdapter::GetImagingSubprimData(
    const UsdPrim &prim,
    const TfToken &subprim,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
  if (subprim.IsEmpty()) {
    UsdGeomSubset subset(prim);
    return HdOverlayContainerDataSource::New(
        HdRetainedContainerDataSource::New(
            HdGeomSubsetSchema::GetSchemaToken(),
            HdGeomSubsetSchema::Builder()
                .SetIndices(UsdImagingDataSourceAttribute<VtIntArray>::New(subset.GetIndicesAttr(),
                                                                           stageGlobals))
                .SetType(_ElementTypeConversionDataSource::New(
                    UsdImagingDataSourceAttribute<TfToken>::New(subset.GetElementTypeAttr(),
                                                                stageGlobals)))
                .Build()),
        // The geomSubset must also be a prim so it can
        // pick up existing material binding handling.
        UsdImagingDataSourcePrim::New(prim.GetPath(), prim, stageGlobals));
  }
  return nullptr;
}

HdDataSourceLocatorSet UsdImagingGeomSubsetAdapter::InvalidateImagingSubprim(
    const UsdPrim &prim,
    const TfToken &subprim,
    const TfTokenVector &properties,
    UsdImagingPropertyInvalidationType invalidationType)
{
  HdDataSourceLocatorSet locators;
  for (const TfToken &name : properties) {
    if (name == UsdGeomTokens->indices) {
      locators.insert(HdDataSourceLocator(HdGeomSubsetSchemaTokens->indices));
    }
    else if (name == UsdGeomTokens->elementType) {
      locators.insert(HdDataSourceLocator(HdGeomSubsetSchemaTokens->type));
    }
  }
  locators.insert(
      UsdImagingDataSourcePrim::Invalidate(prim, subprim, properties, invalidationType));
  return locators;
}

// ---------------------------------------------------------------------- //
/// Overrides for Pure Virtual Legacy Methods
// ---------------------------------------------------------------------- //

SdfPath UsdImagingGeomSubsetAdapter::Populate(const UsdPrim &prim,
                                              UsdImagingIndexProxy *index,
                                              const UsdImagingInstancerContext *instancerCtx)
{
  return SdfPath::EmptyPath();
}

HdDirtyBits UsdImagingGeomSubsetAdapter::ProcessPropertyChange(const UsdPrim &prim,
                                                               const SdfPath &cachePath,
                                                               const TfToken &propertyName)
{
  return HdChangeTracker::Clean;
}

PXR_NAMESPACE_CLOSE_SCOPE
