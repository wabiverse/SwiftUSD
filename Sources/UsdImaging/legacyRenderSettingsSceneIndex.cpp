//
// Copyright 2026 Pixar
//
// Licensed under the derms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/legacyRenderSettingsSceneIndex.h"

#include "Hd/dataSource.h"
#include "Hd/dataSourceLocator.h"
#include "Hd/filteringSceneIndex.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/renderDelegate.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneGlobalsSchema.h"
#include "Hd/sceneIndex.h"
#include "Hd/sceneIndexObserver.h"

#include "Sdf/path.h"

#include "Tf/refPtr.h"
#include "Tf/staticTokens.h"
#include "Tf/token.h"
#include "Vt/typeHeaders.h" // IWYU pragma: keep
#include "Vt/value.h"
#include "Vt/visitValue.h"

#include "pxr/pxrns.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(
    _tokens,
    (legacyRenderSettings));

namespace {

struct _Visitor {
    template <typename T>
    HdDataSourceBaseHandle
    operator()(const T& value) const
    {
        return HdRetainedTypedSampledDataSource<T>::New(value);
    }

    HdDataSourceBaseHandle
    operator()(const VtValue& value) const
    {
        return HdRetainedSampledDataSource::New(value);
    }
};

} // anonymous namespace

UsdImagingLegacyRenderSettingsSceneIndexRefPtr
UsdImagingLegacyRenderSettingsSceneIndex::New(
    const HdSceneIndexBaseRefPtr& inputSceneIndex)
{
    return TfCreateRefPtr(
        new UsdImagingLegacyRenderSettingsSceneIndex(inputSceneIndex));
}

HdSceneIndexPrim
UsdImagingLegacyRenderSettingsSceneIndex::GetPrim(
    const SdfPath& primPath) const
{
    HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(primPath);
    if (primPath == SdfPath::AbsoluteRootPath()) {
        prim.dataSource = HdOverlayContainerDataSource::New(
            prim.dataSource, _dataSource);
    }
    return prim;
}

void
UsdImagingLegacyRenderSettingsSceneIndex::SetRenderSetting(
    const TfToken& id,
    const VtValue& value)
{
    static const HdDataSourceLocator legacyRenderSettingsLocator =
        HdSceneGlobalsSchema::GetDefaultLocator()
            .Append(_tokens->legacyRenderSettings);
    const auto it = _map.find(id);
    if (it != _map.end() && it->second == value) {
        // Do not update or notify if the value did not change
        return;
    }
    _map.insert_or_assign(id, value);
    _Compose();
    _SendPrimsDirtied({ {
        SdfPath::AbsoluteRootPath(), {
            legacyRenderSettingsLocator.Append(id),
            HdDataSourceLocator(
                HdDataSourceLocatorSentinelTokens->container) } } });
}

UsdImagingLegacyRenderSettingsSceneIndex::
UsdImagingLegacyRenderSettingsSceneIndex(
    const HdSceneIndexBaseRefPtr& inputSceneIndex)
  : HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
{ }

SdfPathVector
UsdImagingLegacyRenderSettingsSceneIndex::GetChildPrimPaths(
    const SdfPath& primPath) const
{
    return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
}

void
UsdImagingLegacyRenderSettingsSceneIndex::_PrimsAdded(
    const HdSceneIndexBase&,
    const HdSceneIndexObserver::AddedPrimEntries& entries)
{
    _SendPrimsAdded(entries);
}

void
UsdImagingLegacyRenderSettingsSceneIndex::_PrimsDirtied(
    const HdSceneIndexBase&,
    const HdSceneIndexObserver::DirtiedPrimEntries& entries)
{
    _SendPrimsDirtied(entries);
}

void
UsdImagingLegacyRenderSettingsSceneIndex::_PrimsRemoved(
    const HdSceneIndexBase&,
    const HdSceneIndexObserver::RemovedPrimEntries& entries)
{
    _SendPrimsRemoved(entries);
}

void
UsdImagingLegacyRenderSettingsSceneIndex::_Compose()
{
    static const _Visitor visitor;

    std::vector<TfToken> names(_map.size());
    std::vector<HdDataSourceBaseHandle> sources(_map.size());

    for (const _EntryType& entry : _map) {
        names.push_back(entry.first);
        sources.push_back(VtVisitValue(entry.second, visitor));
    }
    _dataSource = HdRetainedContainerDataSource::New(
        HdSceneGlobalsSchema::GetSchemaToken(),
        HdRetainedContainerDataSource::New(
            _tokens->legacyRenderSettings,
            HdRetainedContainerDataSource::New(
                names.size(), names.data(), sources.data())));
}

PXR_NAMESPACE_CLOSE_SCOPE
