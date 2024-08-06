//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "HdSi/sceneGlobalsSceneIndex.h"

#include "Hd/overlayContainerDataSource.h"
#include "Hd/renderSettingsSchema.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneGlobalsSchema.h"
#include "Hd/tokens.h"

PXR_NAMESPACE_OPEN_SCOPE

// -----------------------------------------------------------------------------
// _SceneGlobalsDataSource
// -----------------------------------------------------------------------------
class _SceneGlobalsDataSource : public HdContainerDataSource {
 public:
  HD_DECLARE_DATASOURCE(_SceneGlobalsDataSource);

  TfTokenVector GetNames() override;

  HdDataSourceBaseHandle Get(const TfToken &name) override;

 private:
  _SceneGlobalsDataSource(HdsiSceneGlobalsSceneIndex const *const si) : _si(si) {}

  const HdsiSceneGlobalsSceneIndex *const _si;
};

TfTokenVector _SceneGlobalsDataSource::GetNames()
{
  static const TfTokenVector names = {HdSceneGlobalsSchemaTokens->activeRenderPassPrim,
                                      HdSceneGlobalsSchemaTokens->activeRenderSettingsPrim,
                                      HdSceneGlobalsSchemaTokens->currentFrame};

  return names;
}

HdDataSourceBaseHandle _SceneGlobalsDataSource::Get(const TfToken &name)
{
  if (name == HdSceneGlobalsSchemaTokens->activeRenderPassPrim) {
    SdfPath const &path = _si->_activeRenderPassPrimPath;
    return HdRetainedTypedSampledDataSource<SdfPath>::New(path);
  }
  if (name == HdSceneGlobalsSchemaTokens->activeRenderSettingsPrim) {
    SdfPath const &path = _si->_activeRenderSettingsPrimPath;
    return HdRetainedTypedSampledDataSource<SdfPath>::New(path);
  }
  if (name == HdSceneGlobalsSchemaTokens->currentFrame) {
    const double timeCode = _si->_time;
    return HdRetainedTypedSampledDataSource<double>::New(timeCode);
  }

  return nullptr;
}

// -----------------------------------------------------------------------------
// HdsiSceneGlobalsSceneIndex
// -----------------------------------------------------------------------------

/* static */
HdsiSceneGlobalsSceneIndexRefPtr HdsiSceneGlobalsSceneIndex::New(
    const HdSceneIndexBaseRefPtr &inputSceneIndex)
{
  return TfCreateRefPtr(new HdsiSceneGlobalsSceneIndex(inputSceneIndex));
}

void HdsiSceneGlobalsSceneIndex::SetActiveRenderPassPrimPath(const SdfPath &path)
{
  if (_activeRenderPassPrimPath == path) {
    return;
  }

  // A scene index downstream will invalidate and update the
  // sceneGlobals.activeRenderSettingsPrim locator (if the render pass points
  // to a valid render settings prim).
  // We keep things simple in this scene index.
  _activeRenderPassPrimPath = path;

  if (_IsObserved()) {
    _SendPrimsDirtied({{HdSceneGlobalsSchema::GetDefaultPrimPath(),
                        HdSceneGlobalsSchema::GetActiveRenderPassPrimLocator()}});
  }
}

void HdsiSceneGlobalsSceneIndex::SetActiveRenderSettingsPrimPath(const SdfPath &path)
{
  if (_activeRenderSettingsPrimPath == path) {
    return;
  }

  _activeRenderSettingsPrimPath = path;

  if (_IsObserved()) {
    _SendPrimsDirtied({{HdSceneGlobalsSchema::GetDefaultPrimPath(),
                        HdSceneGlobalsSchema::GetActiveRenderSettingsPrimLocator()}});
  }
}

void HdsiSceneGlobalsSceneIndex::SetCurrentFrame(const double &time)
{
  // XXX We might need to add a flag to force dirtying of the Frame locator
  // even if the time has not changed
  if (_time == time) {
    return;
  }

  _time = time;

  if (_IsObserved()) {
    _SendPrimsDirtied({{HdSceneGlobalsSchema::GetDefaultPrimPath(),
                        HdSceneGlobalsSchema::GetCurrentFrameLocator()}});
  }
}

HdSceneIndexPrim HdsiSceneGlobalsSceneIndex::GetPrim(const SdfPath &primPath) const
{
  HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(primPath);

  // Overlay a data source at the scene globals locator for the default prim.
  if (primPath == HdSceneGlobalsSchema::GetDefaultPrimPath()) {
    HdContainerDataSourceHandle sceneGlobalsContainerDS = HdRetainedContainerDataSource::New(
        HdSceneGlobalsSchemaTokens->sceneGlobals, _SceneGlobalsDataSource::New(this));

    if (prim.dataSource) {
      prim.dataSource = HdOverlayContainerDataSource::New(sceneGlobalsContainerDS,
                                                          prim.dataSource);
    }
    else {
      prim.dataSource = sceneGlobalsContainerDS;
    }
  }

  return prim;
}

SdfPathVector HdsiSceneGlobalsSceneIndex::GetChildPrimPaths(const SdfPath &primPath) const
{
  return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
}

HdsiSceneGlobalsSceneIndex::HdsiSceneGlobalsSceneIndex(
    const HdSceneIndexBaseRefPtr &inputSceneIndex)
    : HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
{
}

void HdsiSceneGlobalsSceneIndex::_PrimsAdded(const HdSceneIndexBase &sender,
                                             const HdSceneIndexObserver::AddedPrimEntries &entries)
{
  _SendPrimsAdded(entries);
}

void HdsiSceneGlobalsSceneIndex::_PrimsRemoved(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::RemovedPrimEntries &entries)
{
  // XXX Since this is now a filtering scene index, handle removals of
  //     the active render settings prim.
  _SendPrimsRemoved(entries);
}

void HdsiSceneGlobalsSceneIndex::_PrimsDirtied(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::DirtiedPrimEntries &entries)
{
  _SendPrimsDirtied(entries);
}

// XXX Handle renames by sending a dirty notice that the active render settings
//     prim has changed.

PXR_NAMESPACE_CLOSE_SCOPE
