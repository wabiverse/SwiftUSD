//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyFunction.h"
#include "Tf/pyResultConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>

#include "UsdUtils/userProcessingFunc.h"

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUserProcessingFunc()
{
  TfPyFunctionFromPython<UsdUtilsProcessingFunc>();

  typedef UsdUtilsDependencyInfo This;

  class_<This>("DependencyInfo", init<>())
      .def(init<const This &>())
      .def(init<const std::string &>())
      .def(init<const std::string &, const std::vector<std::string>>())
      .add_property("assetPath",
                    make_function(&This::GetAssetPath, return_value_policy<return_by_value>()))
      .add_property(
          "dependencies",
          make_function(&This::GetDependencies, return_value_policy<TfPySequenceToList>()));
}
