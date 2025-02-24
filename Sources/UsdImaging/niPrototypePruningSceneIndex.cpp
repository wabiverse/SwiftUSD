//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdImaging/niPrototypePruningSceneIndex.h"

#include "UsdImaging/usdPrimInfoSchema.h"

#include "Hd/dataSourceTypeDefs.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

bool _IsUsdPrototype(HdSceneIndexBaseRefPtr const &sceneIndex, const SdfPath &primPath)
{
  HdContainerDataSourceHandle const primSource = sceneIndex->GetPrim(primPath).dataSource;
  UsdImagingUsdPrimInfoSchema schema = UsdImagingUsdPrimInfoSchema::GetFromParent(primSource);
  HdBoolDataSourceHandle const ds = schema.GetIsNiPrototype();
  if (!ds) {
    return false;
  }
  return ds->GetTypedValue(0.0f);
}

bool _ContainsPrefixOfPath(const SdfPathSet &pathSet, const SdfPath &path)
{
  // Use std::map::lower_bound over std::lower_bound since the latter
  // is slow given that std::map iterators are not random access.
  auto it = pathSet.lower_bound(path);
  if (it != pathSet.end() && path == *it) {
    // Path itself is in the container
    return true;
  }

  // If a prefix of path is in container, it will point to the next element
  // in the container, rather than the prefix itself.
  if (it == pathSet.begin()) {
    return false;
  }
  --it;
  return path.HasPrefix(*it);
}

// Only return entries (e.g., HdSceneIndexObserver::AddedEntries) where
// predicate is true.
//
// It implements a copy-on-write pattern, that is, it avoids copying the
// given vector if no entry was filtered out.
template<typename Entries> class _FilteredEntries {
 public:
  using Entry = typename Entries::value_type;

  _FilteredEntries(const Entries &entries, const std::function<bool(const SdfPath &)> &predicate)
      : _entries(entries), _useComputedEntries(false)
  {
    size_t i = 0;

    for (; i < entries.size(); i++) {
      if (!predicate(entries[i].primPath)) {
        break;
      }
    }

    if (i == entries.size()) {
      return;
    }

    _useComputedEntries = true;

    _computedEntries.insert(_computedEntries.begin(), _entries.begin(), _entries.begin() + i);

    i++;

    for (; i < _entries.size(); i++) {
      if (predicate(entries[i].primPath)) {
        _computedEntries.push_back(entries[i]);
      }
    }
  }

  const Entries &Get() const
  {
    if (_useComputedEntries) {
      return _computedEntries;
    }
    else {
      return _entries;
    }
  }

 private:
  const Entries &_entries;
  bool _useComputedEntries;
  Entries _computedEntries;
};

}  // namespace

UsdImaging_NiPrototypePruningSceneIndex::UsdImaging_NiPrototypePruningSceneIndex(
    HdSceneIndexBaseRefPtr const &inputSceneIndex)
    : HdSingleInputFilteringSceneIndexBase(inputSceneIndex)
{
  for (const SdfPath &path : _GetInputSceneIndex()->GetChildPrimPaths(SdfPath::AbsoluteRootPath()))
  {
    if (_IsUsdPrototype(_GetInputSceneIndex(), path)) {
      _prototypes.insert(path);
    }
  }
}

HdSceneIndexPrim UsdImaging_NiPrototypePruningSceneIndex::GetPrim(const SdfPath &primPath) const
{
  if (_ContainsPrefixOfPath(_prototypes, primPath)) {
    return {TfToken(), nullptr};
  }

  return _GetInputSceneIndex()->GetPrim(primPath);
}

SdfPathVector UsdImaging_NiPrototypePruningSceneIndex::GetChildPrimPaths(
    const SdfPath &primPath) const
{
  if (_prototypes.empty()) {
    return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
  }

  if (primPath.IsAbsoluteRootPath()) {
    SdfPathVector result;
    for (const SdfPath &child :
         _GetInputSceneIndex()->GetChildPrimPaths(SdfPath::AbsoluteRootPath()))
    {
      if (_prototypes.count(child) == 0) {
        result.push_back(child);
      }
    }
    return result;
  }

  if (_ContainsPrefixOfPath(_prototypes, primPath)) {
    return {};
  }

  return _GetInputSceneIndex()->GetChildPrimPaths(primPath);
}

void UsdImaging_NiPrototypePruningSceneIndex::_PrimsAdded(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::AddedPrimEntries &entries)
{
  _FilteredEntries<HdSceneIndexObserver::AddedPrimEntries> newEntries(
      entries, [this](const SdfPath &primPath) {
        if (primPath.GetPathElementCount() == 1) {
          if (_IsUsdPrototype(this->_GetInputSceneIndex(), primPath)) {
            _prototypes.insert(primPath);
            return false;
          }
          else {
            return true;
          }
        }
        else {
          return !_ContainsPrefixOfPath(this->_prototypes, primPath);
        }
      });

  _SendPrimsAdded(newEntries.Get());
}

void UsdImaging_NiPrototypePruningSceneIndex::_PrimsDirtied(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::DirtiedPrimEntries &entries)
{
  if (_prototypes.empty()) {
    _SendPrimsDirtied(entries);
    return;
  }

  _FilteredEntries<HdSceneIndexObserver::DirtiedPrimEntries> newEntries(
      entries, [this](const SdfPath &primPath) {
        return !_ContainsPrefixOfPath(this->_prototypes, primPath);
      });

  _SendPrimsDirtied(newEntries.Get());
}

void UsdImaging_NiPrototypePruningSceneIndex::_PrimsRemoved(
    const HdSceneIndexBase &sender, const HdSceneIndexObserver::RemovedPrimEntries &entries)
{
  _FilteredEntries<HdSceneIndexObserver::RemovedPrimEntries> newEntries(
      entries, [this](const SdfPath &primPath) {
        if (primPath.IsAbsoluteRootPath()) {
          this->_prototypes.clear();
          return true;
        }
        if (primPath.GetPathElementCount() == 1) {
          return _prototypes.erase(primPath) == 0;
        }
        return !_ContainsPrefixOfPath(this->_prototypes, primPath);
      });

  _SendPrimsRemoved(newEntries.Get());
}

PXR_NAMESPACE_CLOSE_SCOPE
