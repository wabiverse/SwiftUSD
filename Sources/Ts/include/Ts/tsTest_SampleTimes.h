//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#ifndef PXR_BASE_TS_TS_TEST_SAMPLE_TIMES_H
#define PXR_BASE_TS_TS_TEST_SAMPLE_TIMES_H

#include "Ts/api.h"
#include "Ts/tsTest_SplineData.h"
#include "pxr/pxrns.h"

#include <set>
#include <vector>

PXR_NAMESPACE_OPEN_SCOPE

class TsTest_SampleTimes {
 public:
  // A time at which to perform evaluation.  Typically just a time, but can
  // also be a "pre" time, which at a dual-valued knot can differ from the
  // ordinary value.
  struct TS_API SampleTime {
    double time = 0.0;
    bool pre = false;

   public:
    SampleTime();
    SampleTime(double time);
    SampleTime(double time, bool pre);
    SampleTime(const SampleTime &other);
    SampleTime &operator=(const SampleTime &other);
    SampleTime &operator=(double time);
    bool operator<(const SampleTime &other) const;
    bool operator==(const SampleTime &other) const;
    bool operator!=(const SampleTime &other) const;
  };

  using SampleTimeSet = std::set<SampleTime>;

 public:
  // DIRECT SPECIFICATION

  // Constructs a SampleTimes object for direct specification of times.
  TS_API
  TsTest_SampleTimes();

  // Adds the specified times.
  TS_API
  void AddTimes(const std::vector<double> &times);

  // Adds the specified times.
  TS_API
  void AddTimes(const std::vector<SampleTime> &times);

  // SPLINE-DRIVEN

  // Constructs a SampleTimes object for specification of times based on the
  // contents of splineData.
  TS_API
  TsTest_SampleTimes(const TsTest_SplineData &splineData);

  // Adds a time for each knot in splineData.  For dual-valued knots, adds
  // both a pre-time and an ordinary time.
  TS_API
  void AddKnotTimes();

  // Adds evenly spaced sample times within the frame range of splineData.
  // The first sample is after the first knot, and the last sample is before
  // the last knot.
  TS_API
  void AddUniformInterpolationTimes(int numSamples);

  // Determines the time range of the knots in splineData, extends it by
  // extrapolationFactor on each end, and adds one pre-extrapolating and one
  // post-extrapolating sample.  For example, with a time range of 10, and an
  // extrapolationFactor of 0.25, samples will be added 2.5 time units before
  // the first knot and 2.5 time units after the last.
  TS_API
  void AddExtrapolationTimes(double extrapolationFactor);

  // MACRO

  // Calls AddKnotTimes(), AddUniformInterpolationTimes(200), and
  // AddExtrapolationTimes(0.2).
  TS_API
  void AddStandardTimes();

  // ACCESSORS

  // Returns the set of sample times.
  TS_API
  const SampleTimeSet &GetTimes() const;

 private:
  SampleTimeSet _GetKnotTimes() const;

 private:
  const bool _haveSplineData;
  const TsTest_SplineData _splineData;

  SampleTimeSet _times;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
