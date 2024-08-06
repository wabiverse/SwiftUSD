//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "UsdPhysics/metrics.h"
#include "pxr/pxrns.h"

#include "Usd/stage.h"

#include "Tf/pyResultConversions.h"

#include <boost/python/class.hpp>
#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapMetrics()
{
  def("GetStageKilogramsPerUnit", UsdPhysicsGetStageKilogramsPerUnit, arg("stage"));
  def("StageHasAuthoredKilogramsPerUnit",
      UsdPhysicsStageHasAuthoredKilogramsPerUnit,
      arg("stage"));
  def("SetStageKilogramsPerUnit",
      UsdPhysicsSetStageKilogramsPerUnit,
      (arg("stage"), arg("metersPerUnit")));
  def("MassUnitsAre",
      UsdPhysicsMassUnitsAre,
      (arg("authoredUnits"), arg("standardUnits"), arg("epsilon") = 1e-5));

  boost::python::class_<UsdPhysicsMassUnits> cls("MassUnits", boost::python::no_init);
  cls.def_readonly("kilograms", UsdPhysicsMassUnits::kilograms)
      .def_readonly("grams", UsdPhysicsMassUnits::grams)
      .def_readonly("slugs", UsdPhysicsMassUnits::slugs);
}
