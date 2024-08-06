//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Work/threadLimits.h"
#include "pxr/pxrns.h"

#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapThreadLimits()
{
  def("GetConcurrencyLimit", &WorkGetConcurrencyLimit);
  def("HasConcurrency", &WorkHasConcurrency);
  def("GetPhysicalConcurrencyLimit", &WorkGetPhysicalConcurrencyLimit);

  def("SetConcurrencyLimit", &WorkSetConcurrencyLimit);
  def("SetConcurrencyLimitArgument", &WorkSetConcurrencyLimitArgument);
  def("SetMaximumConcurrencyLimit", &WorkSetMaximumConcurrencyLimit);
}
