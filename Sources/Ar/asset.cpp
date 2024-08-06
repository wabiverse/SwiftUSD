//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Ar/asset.h"
#include "Ar/inMemoryAsset.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

ArAsset::ArAsset() {}

ArAsset::~ArAsset() {}

std::shared_ptr<ArAsset> ArAsset::GetDetachedAsset() const
{
  return ArInMemoryAsset::FromAsset(*this);
}

PXR_NAMESPACE_CLOSE_SCOPE
