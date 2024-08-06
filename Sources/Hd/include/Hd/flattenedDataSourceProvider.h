//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_FLATTENED_DATA_SOURCE_PROVIDER_H
#define PXR_IMAGING_HD_FLATTENED_DATA_SOURCE_PROVIDER_H

#include "Hd/api.h"

#include "Hd/dataSource.h"
#include "Hd/retainedDataSource.h"
#include "Sdf/path.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdSceneIndexBase;
using HdFlattenedDataSourceProviderSharedPtr =
    std::shared_ptr<class HdFlattenedDataSourceProvider>;

/// \class HdFlattenedDataSourceProvider.
///
/// Given to HdFlatteningSceneIndex to determine how to compute the
/// flattened data source which is in the prim container data
/// source.
///
class HdFlattenedDataSourceProvider {
 public:
  class Context {
   public:
    Context(const HdSceneIndexBase &flatteningSceneIndex,
            const SdfPath &primPath,
            const TfToken &name,
            const HdContainerDataSourceHandle &inputPrimDataSource)
        : _flatteningSceneIndex(flatteningSceneIndex),
          _primPath(primPath),
          _name(name),
          _inputPrimDataSource(inputPrimDataSource)
    {
    }

    // Returns data source of input scene index which is in
    // the prim container data source.
    HD_API
    HdContainerDataSourceHandle GetInputDataSource() const;
    // Returns flattened data source which is in the flattened
    // container data source of the parent prim.
    HD_API
    HdContainerDataSourceHandle GetFlattenedDataSourceFromParentPrim() const;

   private:
    const HdSceneIndexBase &_flatteningSceneIndex;
    const SdfPath &_primPath;
    const TfToken &_name;
    const HdContainerDataSourceHandle &_inputPrimDataSource;
  };

  HD_API
  virtual ~HdFlattenedDataSourceProvider();

  /// Returns flattened data source.
  virtual HdContainerDataSourceHandle GetFlattenedDataSource(const Context &ctx) const = 0;

  /// If data source locators are dirtied in the input scene index, the
  /// locators relevant for the input data source serving this provider
  /// are extracted and made relative to the input data source.
  ///
  /// They are later used to invalidate the flattened data source of the
  /// dirtied prim and its descendants and send prim dirtied messages to
  /// the descendants.
  ///
  /// Example: If a prim dirtied for locator xform:matrix was received, the
  /// flattening scene index will call the flattened data source provider
  /// for xform. The locators given to ComputeDirtyLocatorsForDescendants
  /// will be { matrix }. If ComputeDirtyLocatorsForDescendants sets it to
  /// the universal set, the flatening scene index will emit a prim dirtied
  /// locator xform for the descendants.
  ///
  /// The implementation of ComputeDirtyLocatorsForDescendants gives a chance
  /// to drop locators or expand the locator set in between.
  ///
  /// Note that ComputeDirtyLocatorsForDescendants will never be called with
  /// the empty or universal set as these cases are already handled by the
  /// callee.
  ///
  virtual void ComputeDirtyLocatorsForDescendants(HdDataSourceLocatorSet *locators) const = 0;
};

namespace HdMakeDataSourceContainingFlattenedDataSourceProvider {

template<typename T>
HdTypedSampledDataSource<HdFlattenedDataSourceProviderSharedPtr>::Handle Make()
{
  using DataSource = HdRetainedTypedSampledDataSource<HdFlattenedDataSourceProviderSharedPtr>;
  return DataSource::New(std::make_shared<T>());
}

}  // namespace HdMakeDataSourceContainingFlattenedDataSourceProvider

PXR_NAMESPACE_CLOSE_SCOPE

#endif
