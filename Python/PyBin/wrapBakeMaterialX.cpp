//
// Copyright 2022 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Bin/usdBakeMtlx/bakeMaterialX.h"

#include "Tf/makePyConstructor.h"
#include "Usd/stage.h"
#include "pxr/pxrns.h"

#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdBakeMtlx()
{
  def("BakeMaterial",
      UsdBakeMtlxBakeMaterial,
      (arg("mtlxMaterial"),
       arg("bakedMtlxDir"),
       arg("textureWidth"),
       arg("textureHeight"),
       arg("bakeHdr"),
       arg("bakeAverage")));
  def("ReadFileToStage",
      UsdBakeMtlxReadDocToStage,
      (arg("pathname"), arg("stage")),
      return_value_policy<TfPyRefPtrFactory<>>());
}
