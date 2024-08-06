//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/pyResultConversions.h"
#include "Ts/tsTest_SampleBezier.h"
#include "pxr/pxrns.h"

#include <boost/python.hpp>

PXR_NAMESPACE_USING_DIRECTIVE

using namespace boost::python;

void wrapTsTest_SampleBezier()
{
  def("TsTest_SampleBezier",
      &TsTest_SampleBezier,
      (arg("splineData"), arg("numSamples")),
      return_value_policy<TfPySequenceToList>());
}
