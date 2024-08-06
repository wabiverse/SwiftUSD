//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HD_DIRTY_BITS_TRANSLATOR_H
#define PXR_IMAGING_HD_DIRTY_BITS_TRANSLATOR_H

#include "Hd/dataSourceLocator.h"
#include "Hd/types.h"
#include "Tf/token.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

/// \class HdDirtyBitsTranslator
///
/// A set of optimized functions for translating between dirty bits and
/// datasource locators for different prim types.
class HdDirtyBitsTranslator {
 public:
  // Dirty bits to locators.
  HD_API
  static void RprimDirtyBitsToLocatorSet(TfToken const &primType,
                                         const HdDirtyBits bits,
                                         HdDataSourceLocatorSet *set);
  HD_API
  static void SprimDirtyBitsToLocatorSet(TfToken const &primType,
                                         const HdDirtyBits bits,
                                         HdDataSourceLocatorSet *set);
  HD_API
  static void BprimDirtyBitsToLocatorSet(TfToken const &primType,
                                         const HdDirtyBits bits,
                                         HdDataSourceLocatorSet *set);
  HD_API
  static void InstancerDirtyBitsToLocatorSet(TfToken const &primType,
                                             const HdDirtyBits bits,
                                             HdDataSourceLocatorSet *set);

  // Locators to dirty bits.
  HD_API
  static HdDirtyBits RprimLocatorSetToDirtyBits(TfToken const &primType,
                                                HdDataSourceLocatorSet const &set);
  HD_API
  static HdDirtyBits SprimLocatorSetToDirtyBits(TfToken const &primType,
                                                HdDataSourceLocatorSet const &set);
  HD_API
  static HdDirtyBits BprimLocatorSetToDirtyBits(TfToken const &primType,
                                                HdDataSourceLocatorSet const &set);
  HD_API
  static HdDirtyBits InstancerLocatorSetToDirtyBits(TfToken const &primType,
                                                    HdDataSourceLocatorSet const &set);

  using LocatorSetToDirtyBitsFnc =
      std::function<void(HdDataSourceLocatorSet const &, HdDirtyBits *)>;

  using DirtyBitsToLocatorSetFnc =
      std::function<void(const HdDirtyBits, HdDataSourceLocatorSet *)>;

  /// Allows for customization of translation for unknown (to the system)
  /// sprim types. Absence of registered functions for an unknown type falls
  /// back to DirtyAll equivalents in both directions.
  HD_API
  static void RegisterTranslatorsForCustomSprimType(TfToken const &primType,
                                                    LocatorSetToDirtyBitsFnc sToBFnc,
                                                    DirtyBitsToLocatorSetFnc bToSFnc);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif  // PXR_IMAGING_HD_DIRTY_BITS_TRANSLATOR_H
