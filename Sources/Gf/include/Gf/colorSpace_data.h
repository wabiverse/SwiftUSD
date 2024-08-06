//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include <pxr/pxrns.h>

#include "nc/nanocolor.h"

PXR_NAMESPACE_OPEN_SCOPE

struct GfColorSpace::_Data {
  ~_Data()
  {
    NcFreeColorSpace(colorSpace);
  }

  const NcColorSpace *colorSpace = nullptr;
};

PXR_NAMESPACE_CLOSE_SCOPE
