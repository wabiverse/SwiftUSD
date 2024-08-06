//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ts/tsTest_Evaluator.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

TsTest_SampleVec TsTest_Evaluator::Sample(const TsTest_SplineData &splineData,
                                          double tolerance) const
{
  // Default implementation returns no samples.
  return {};
}

TsTest_SplineData TsTest_Evaluator::BakeInnerLoops(const TsTest_SplineData &splineData) const
{
  // Default implementation returns the input data unmodified.
  return splineData;
}

PXR_NAMESPACE_CLOSE_SCOPE
