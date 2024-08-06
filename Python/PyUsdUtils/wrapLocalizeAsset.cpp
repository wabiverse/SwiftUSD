//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyEnum.h"
#include "Tf/pyFunction.h"

#include "UsdUtils/localizeAsset.h"

#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapLocalizeAsset()
{
  def("LocalizeAsset",
      UsdUtilsLocalizeAsset,
      (arg("assetPath"),
       arg("localizationDirectory"),
       arg("editLayersInPlace") = false,
       arg("processingFunc") = object()));
}
