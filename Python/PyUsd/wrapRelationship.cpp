//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Usd/relationship.h"
#include "Usd/wrapUtils.h"
#include "pxr/pxrns.h"

#include "Tf/pyContainerConversions.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyUtils.h"

#include <boost/python/class.hpp>
#include <boost/python/tuple.hpp>

using std::string;

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

namespace {

static SdfPathVector _GetTargets(const UsdRelationship &self)
{
  SdfPathVector result;
  self.GetTargets(&result);
  return result;
}

static SdfPathVector _GetForwardedTargets(const UsdRelationship &self)
{
  SdfPathVector result;
  self.GetForwardedTargets(&result);
  return result;
}

static string __repr__(const UsdRelationship &self)
{
  if (self) {
    return TfStringPrintf("%s.GetRelationship(%s)",
                          TfPyRepr(self.GetPrim()).c_str(),
                          TfPyRepr(self.GetName()).c_str());
  }
  else {
    return "invalid " + self.GetDescription();
  }
}

}  // anonymous namespace

void wrapUsdRelationship()
{
  class_<UsdRelationship, bases<UsdProperty>>("Relationship")
      .def(Usd_ObjectSubclass())
      .def("__repr__", __repr__)
      .def("AddTarget",
           &UsdRelationship::AddTarget,
           (arg("target"), arg("position") = UsdListPositionBackOfPrependList))
      .def("RemoveTarget", &UsdRelationship::RemoveTarget, arg("target"))
      .def("SetTargets", &UsdRelationship::SetTargets, arg("targets"))
      .def("ClearTargets", &UsdRelationship::ClearTargets, arg("removeSpec"))
      .def("GetTargets", _GetTargets, return_value_policy<TfPySequenceToList>())
      .def("GetForwardedTargets", _GetForwardedTargets, return_value_policy<TfPySequenceToList>())
      .def("HasAuthoredTargets", &UsdRelationship::HasAuthoredTargets);
  TfPyRegisterStlSequencesFromPython<UsdRelationship>();
  to_python_converter<std::vector<UsdRelationship>,
                      TfPySequenceToPython<std::vector<UsdRelationship>>>();
}
