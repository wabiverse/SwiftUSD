//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.

#include "HdSt/dependencySceneIndexPlugin.h"

#include "Hd/containerDataSourceEditor.h"
#include "Hd/dependenciesSchema.h"
#include "Hd/filteringSceneIndex.h"
#include "Hd/lazyContainerDataSource.h"
#include "Hd/mapContainerDataSource.h"
#include "Hd/overlayContainerDataSource.h"
#include "Hd/perfLog.h"
#include "Hd/retainedDataSource.h"
#include "Hd/sceneIndexPluginRegistry.h"
#include "Hd/tokens.h"
#include "Hd/volumeFieldBindingSchema.h"
#include "Hd/volumeFieldSchema.h"

PXR_NAMESPACE_OPEN_SCOPE

TF_DEFINE_PRIVATE_TOKENS(_tokens, ((sceneIndexPluginName, "HdSt_DependencySceneIndexPlugin")));

static const char *const _pluginDisplayName = "GL";

TF_REGISTRY_FUNCTION(TfType)
{
  HdSceneIndexPluginRegistry::Define<HdSt_DependencySceneIndexPlugin>();
}

TF_REGISTRY_FUNCTION(HdSceneIndexPlugin)
{
  // This scene index should be added *before*
  // HdSt_DependencyForwardingSceneIndexPlugin (which currently uses 1000).
  const HdSceneIndexPluginRegistry::InsertionPhase insertionPhase = 100;

  HdSceneIndexPluginRegistry::GetInstance().RegisterSceneIndexForRenderer(
      _pluginDisplayName,
      _tokens->sceneIndexPluginName,
      nullptr,
      insertionPhase,
      HdSceneIndexPluginRegistry::InsertionOrderAtStart);
}

namespace {

/// Given a prim path data source, returns a dependency of volumeFieldBinding
/// on volumeField of that given prim.
HdDataSourceBaseHandle _ComputeVolumeFieldDependency(const HdDataSourceBaseHandle &src)
{
  HdDependencySchema::Builder builder;

  builder.SetDependedOnPrimPath(HdPathDataSource::Cast(src));

  static HdLocatorDataSourceHandle dependedOnLocatorDataSource =
      HdRetainedTypedSampledDataSource<HdDataSourceLocator>::New(
          HdVolumeFieldSchema::GetDefaultLocator());
  builder.SetDependedOnDataSourceLocator(dependedOnLocatorDataSource);

  static HdLocatorDataSourceHandle affectedLocatorDataSource =
      HdRetainedTypedSampledDataSource<HdDataSourceLocator>::New(
          HdVolumeFieldBindingSchema::GetDefaultLocator());
  builder.SetAffectedDataSourceLocator(affectedLocatorDataSource);
  return builder.Build();
}

/// Given a prim path, returns a dependency of __dependencies
/// on volumeFieldBinding of the given prim.

HdContainerDataSourceHandle _ComputeVolumeFieldBindingDependency(const SdfPath &primPath)
{
  HdDependencySchema::Builder builder;

  builder.SetDependedOnPrimPath(HdRetainedTypedSampledDataSource<SdfPath>::New(primPath));

  static HdLocatorDataSourceHandle dependedOnLocatorDataSource =
      HdRetainedTypedSampledDataSource<HdDataSourceLocator>::New(
          HdVolumeFieldBindingSchema::GetDefaultLocator());
  builder.SetDependedOnDataSourceLocator(dependedOnLocatorDataSource);

  static HdLocatorDataSourceHandle affectedLocatorDataSource =
      HdRetainedTypedSampledDataSource<HdDataSourceLocator>::New(
          HdDependenciesSchema::GetDefaultLocator());
  builder.SetAffectedDataSourceLocator(affectedLocatorDataSource);

  return HdRetainedContainerDataSource::New(HdVolumeFieldBindingSchemaTokens->volumeFieldBinding,
                                            builder.Build());
}

HdContainerDataSourceHandle _ComputeVolumeFieldBindingDependencies(
    const SdfPath &primPath, const HdContainerDataSourceHandle &primSource)
{
  return HdOverlayContainerDataSource::New(
      HdMapContainerDataSource::New(
          _ComputeVolumeFieldDependency,
          HdContainerDataSource::Cast(HdContainerDataSource::Get(
              primSource, HdVolumeFieldBindingSchema::GetDefaultLocator()))),
      _ComputeVolumeFieldBindingDependency(primPath));
}

TF_DECLARE_REF_PTRS(_SceneIndex);

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/// \class _SceneIndex
///
/// The scene index that adds dependencies for volume prims.
///
class _SceneIndex : public HdSingleInputFilteringSceneIndexBase {
 public:
  static _SceneIndexRefPtr New(const HdSceneIndexBaseRefPtr &inputSceneIndex)
  {
    return TfCreateRefPtr(new _SceneIndex(inputSceneIndex));
  }

  HdSceneIndexPrim GetPrim(const SdfPath &primPath) const override
  {
    const HdSceneIndexPrim prim = _GetInputSceneIndex()->GetPrim(primPath);
    if (prim.primType == HdPrimTypeTokens->volume) {
      return {prim.primType,
              HdContainerDataSourceEditor(prim.dataSource)
                  .Overlay(HdDependenciesSchema::GetDefaultLocator(),
                           HdLazyContainerDataSource::New(std::bind(
                               _ComputeVolumeFieldBindingDependencies, primPath, prim.dataSource)))
                  .Finish()};
    }
    return prim;
  }

  SdfPathVector GetChildPrimPaths(const SdfPath &primPath) const override
  {
    return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
  }

 protected:
  _SceneIndex(const HdSceneIndexBaseRefPtr &inputSceneIndex)
      : HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
  {
    SetDisplayName("HdSt: declare Storm dependencies");
  }

  void _PrimsAdded(const HdSceneIndexBase &sender,
                   const HdSceneIndexObserver::AddedPrimEntries &entries) override
  {
    if (!_IsObserved()) {
      return;
    }

    _SendPrimsAdded(entries);
  }

  void _PrimsRemoved(const HdSceneIndexBase &sender,
                     const HdSceneIndexObserver::RemovedPrimEntries &entries) override
  {
    if (!_IsObserved()) {
      return;
    }

    _SendPrimsRemoved(entries);
  }

  void _PrimsDirtied(const HdSceneIndexBase &sender,
                     const HdSceneIndexObserver::DirtiedPrimEntries &entries) override
  {
    HD_TRACE_FUNCTION();

    if (!_IsObserved()) {
      return;
    }

    _SendPrimsDirtied(entries);
  }
};

}  // namespace

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Implementation of HdSt_DependencySceneIndexPlugin

HdSt_DependencySceneIndexPlugin::HdSt_DependencySceneIndexPlugin() = default;

HdSceneIndexBaseRefPtr HdSt_DependencySceneIndexPlugin::_AppendSceneIndex(
    const HdSceneIndexBaseRefPtr &inputScene, const HdContainerDataSourceHandle &inputArgs)
{
  return _SceneIndex::New(inputScene);
}

PXR_NAMESPACE_CLOSE_SCOPE
