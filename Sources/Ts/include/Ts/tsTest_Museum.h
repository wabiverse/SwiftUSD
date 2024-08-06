//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_BASE_TS_TS_TEST_MUSEUM_H
#define PXR_BASE_TS_TS_TEST_MUSEUM_H

#include "Ts/api.h"
#include "Ts/tsTest_SplineData.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

// A collection of museum exhibits.  These are spline cases that can be used by
// tests to exercise various behaviors.
//
class TS_API TsTest_Museum {
 public:
  enum DataId { TwoKnotBezier, TwoKnotLinear, SimpleInnerLoop, Recurve, Crossover };

  static TsTest_SplineData GetData(DataId id);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
