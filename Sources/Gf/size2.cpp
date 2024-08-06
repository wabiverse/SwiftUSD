//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Gf/size2.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<GfSize2>();
}

std::ostream &operator<<(std::ostream &o, GfSize2 const &v)
{
  return o << "( " << v._vec[0] << " " << v._vec[1] << " )";
}

PXR_NAMESPACE_CLOSE_SCOPE
