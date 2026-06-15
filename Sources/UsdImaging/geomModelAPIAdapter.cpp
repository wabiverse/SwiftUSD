//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/geomModelAPIAdapter.h"

#include "UsdImaging/dataSourceMapped.h"
#include "UsdImaging/geomModelSchema.h"
#include "UsdImaging/tokens.h"
#include "Hd/extentSchema.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/tokens.h"
#include "Hd/retainedDataSource.h"
#include "Kind/registry.h"
#include "UsdGeom/modelAPI.h"
#include "Usd/modelAPI.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

std::vector<UsdImagingDataSourceMapped::PropertyMapping>
_GetPropertyMappings()
{
    std::vector<UsdImagingDataSourceMapped::PropertyMapping> result;

    for (const TfToken &usdName :
             UsdGeomModelAPI::GetSchemaAttributeNames(
                 /* includeInherited = */ false)) {

        const std::pair<std::string, bool> nameAndMatch =
            SdfPath::StripPrefixNamespace(
                usdName.GetString(), "model");
        if (nameAndMatch.second) {
            result.push_back(
                UsdImagingDataSourceMapped::AttributeMapping{
                    { usdName,
                      HdDataSourceLocator(TfToken(nameAndMatch.first)) }
                });
        }
    }

    return result;
}

const UsdImagingDataSourceMapped::PropertyMappings &
_GetMappings() {
    static const UsdImagingDataSourceMapped::PropertyMappings result(
        _GetPropertyMappings(), UsdImagingGeomModelSchema::GetDefaultLocator());
    return result;
}

}

TF_REGISTRY_FUNCTION(TfType)
{
    using Adapter = UsdImagingGeomModelAPIAdapter;
    TfType t = TfType::Define<Adapter, TfType::Bases<Adapter::BaseAdapter> >();
    t.SetFactory< UsdImagingAPISchemaAdapterFactory<Adapter> >();
}

HdContainerDataSourceHandle
UsdImagingGeomModelAPIAdapter::GetImagingSubprimData(
    UsdPrim const& prim,
    TfToken const& subprim,
    TfToken const& appliedInstanceName,
    const UsdImagingDataSourceStageGlobals &stageGlobals)
{
    if (!subprim.IsEmpty() || !appliedInstanceName.IsEmpty()) {
        return nullptr;
    }

    // Reflect UsdGeomModelAPI as UsdImagingGeomModelSchema.
    HdContainerDataSourceHandle geomModelDs =
        UsdImagingDataSourceMapped::New(
            prim, prim.GetPath(), _GetMappings(), stageGlobals);

    // For model components, overlay applyDrawMode=true.
    if (UsdModelAPI(prim).IsKind(KindTokens->component)) {
        static HdContainerDataSourceHandle const applyDrawModeDs =
            UsdImagingGeomModelSchema::Builder()
                .SetApplyDrawMode(
                    HdRetainedTypedSampledDataSource<bool>::New(true))
                .Build();
        geomModelDs = HdOverlayContainerDataSource::
            OverlayedContainerDataSources(applyDrawModeDs, geomModelDs);
    }
    
    return HdRetainedContainerDataSource::New(
        UsdImagingGeomModelSchema::GetSchemaToken(), geomModelDs);
}


HdDataSourceLocatorSet
UsdImagingGeomModelAPIAdapter::InvalidateImagingSubprim(
    UsdPrim const& prim,
    TfToken const& subprim,
    TfToken const& appliedInstanceName,
    TfTokenVector const& properties,
    const UsdImagingPropertyInvalidationType invalidationType)
{
    if (!subprim.IsEmpty() || !appliedInstanceName.IsEmpty()) {
        return HdDataSourceLocatorSet();
    }

    return UsdImagingDataSourceMapped::Invalidate(
        properties, _GetMappings());
}

PXR_NAMESPACE_CLOSE_SCOPE
