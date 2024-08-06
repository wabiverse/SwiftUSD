//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef PXR_IMAGING_HDX_HGI_CONVERSIONS_H
#define PXR_IMAGING_HDX_HGI_CONVERSIONS_H

#include "Hd/types.h"
#include "Hdx/api.h"
#include "Hgi/types.h"

PXR_NAMESPACE_OPEN_SCOPE

///
/// \class HdxHgiConversions
///
/// Converts from Hd types to Hgi types
///
class HdxHgiConversions {
 public:
  HDX_API
  static HgiFormat GetHgiFormat(HdFormat hdFormat);

  HDX_API
  static HdFormat GetHdFormat(HgiFormat hgiFormat);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
