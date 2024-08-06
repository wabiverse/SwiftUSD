//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdSkel/cache.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"
#include "Tf/wrapTypeHelpers.h"
#include "Usd/pyConversions.h"

#include "Usd/prim.h"

#include "UsdSkel/animation.h"
#include "UsdSkel/root.h"
#include "UsdSkel/skeleton.h"
#include "UsdSkel/skeletonQuery.h"
#include "UsdSkel/skinningQuery.h"

#include <boost/python.hpp>
#include <boost/python/extract.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

std::vector<UsdSkelBinding> _ComputeSkelBindings(const UsdSkelCache &self,
                                                 const UsdSkelRoot &skelRoot,
                                                 const Usd_PrimFlagsPredicate predicate)
{
  std::vector<UsdSkelBinding> bindings;
  self.ComputeSkelBindings(skelRoot, &bindings, predicate);
  return bindings;
}

UsdSkelBinding _ComputeSkelBinding(const UsdSkelCache &self,
                                   const UsdSkelRoot &skelRoot,
                                   const UsdSkelSkeleton &skel,
                                   const Usd_PrimFlagsPredicate predicate)
{
  UsdSkelBinding binding;
  self.ComputeSkelBinding(skelRoot, skel, &binding, predicate);
  return binding;
}

}  // namespace

void wrapUsdSkelCache()
{
  using This = UsdSkelCache;

  class_<This>("Cache", init<>())

      .def("Clear", &This::Clear)

      .def("Populate", &This::Populate, (arg("skelRoot"), arg("predicate")))

      .def("GetSkelQuery", &This::GetSkelQuery)

      .def("GetSkinningQuery", &This::GetSkinningQuery)

      .def("GetAnimQuery",
           (UsdSkelAnimQuery(UsdSkelCache::*)(const UsdPrim &) const) & This::GetAnimQuery,
           (arg("prim")))

      .def("GetAnimQuery",
           (UsdSkelAnimQuery(UsdSkelCache::*)(const UsdSkelAnimation &) const) &
               This::GetAnimQuery,
           (arg("anim")))

      .def("ComputeSkelBindings",
           &_ComputeSkelBindings,
           return_value_policy<TfPySequenceToList>(),
           (arg("skelRoot"), arg("predicate")))

      .def("ComputeSkelBinding",
           &_ComputeSkelBinding,
           (arg("skelRoot"), arg("skel"), arg("predicate")));
}
