//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_BASE_TS_TS_TEST_EVALUATOR_H
#define PXR_BASE_TS_TS_TEST_EVALUATOR_H

#include "Ts/api.h"
#include "Ts/tsTest_SampleTimes.h"
#include "Ts/tsTest_SplineData.h"
#include "Ts/tsTest_Types.h"
#include "pxr/pxrns.h"

#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class TS_API TsTest_Evaluator {
 public:
  // Required.  Evaluates a spline at the specified times.
  virtual TsTest_SampleVec Eval(const TsTest_SplineData &splineData,
                                const TsTest_SampleTimes &sampleTimes) const = 0;

  // Optional.  Produces samples at implementation-determined times,
  // sufficient to produce a piecewise linear approximation of the spline with
  // an absolute value error less than the specified tolerance.  Default
  // implementation returns no samples.
  virtual TsTest_SampleVec Sample(const TsTest_SplineData &splineData, double tolerance) const;

  // Optional.  Produce a copy of splineData with inner loops, if any, baked
  // out into ordinary knots.  Default implementation returns the input data
  // unmodified.
  virtual TsTest_SplineData BakeInnerLoops(const TsTest_SplineData &splineData) const;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
