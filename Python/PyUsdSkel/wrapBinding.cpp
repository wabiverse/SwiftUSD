//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/binding.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyPtrHelpers.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"

#include "Usd/pyConversions.h"

#include "UsdSkel/cache.h"
#include "UsdSkel/root.h"

#include <boost/python.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

UsdSkelBinding *_New(const UsdSkelSkeleton &skel, const boost::python::list &skinningQueries)
{
  const size_t numQueries = len(skinningQueries);
  VtArray<UsdSkelSkinningQuery> skinningQueriesArray(numQueries);
  for (size_t i = 0; i < numQueries; ++i) {
    skinningQueriesArray[i] = extract<const UsdSkelSkinningQuery &>(skinningQueries[i]);
  }
  return new UsdSkelBinding(skel, skinningQueriesArray);
}

}  // namespace

void wrapUsdSkelBinding()
{
  using This = UsdSkelBinding;

  class_<This>("Binding", init<>())

      .def("__init__", make_constructor(&_New))

      .def("GetSkeleton", &This::GetSkeleton, return_value_policy<return_by_value>())

      .def("GetSkinningTargets",
           &This::GetSkinningTargets,
           return_value_policy<TfPySequenceToList>());
}
