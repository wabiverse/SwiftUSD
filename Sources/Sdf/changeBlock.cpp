//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdf/changeBlock.h"
#include "Sdf/changeManager.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

SdfChangeBlock::SdfChangeBlock() : _key(Sdf_ChangeManager::Get()._OpenChangeBlock(this)) {}

void SdfChangeBlock::_CloseChangeBlock(void const *key) const
{
  Sdf_ChangeManager::Get()._CloseChangeBlock(this, key);
}

PXR_NAMESPACE_CLOSE_SCOPE
