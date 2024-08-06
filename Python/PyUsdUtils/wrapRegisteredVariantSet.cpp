//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"
#include <boost/python.hpp>
#include <boost/python/def.hpp>

#include "UsdUtils/registeredVariantSet.h"

#include "Tf/pyEnum.h"
#include "Tf/pyResultConversions.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapRegisteredVariantSet()
{
  scope registeredVariantSet =
      class_<UsdUtilsRegisteredVariantSet>(
          "RegisteredVariantSet", "Info for registered variant set", no_init)
          .def_readonly("name", &UsdUtilsRegisteredVariantSet::name)
          .def_readonly("selectionExportPolicy",
                        &UsdUtilsRegisteredVariantSet::selectionExportPolicy);

  typedef UsdUtilsRegisteredVariantSet::SelectionExportPolicy SelectionExportPolicy;
  enum_<SelectionExportPolicy>("SelectionExportPolicy")
      .value("IfAuthored", SelectionExportPolicy::IfAuthored)
      .value("Always", SelectionExportPolicy::Always)
      .value("Never", SelectionExportPolicy::Never);
}
