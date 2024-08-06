//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ts/tsTest_TsEvaluator.h"
#include "pxr/pxrns.h"

#include "Ts/spline.h"

#include "Tf/diagnostic.h"

PXR_NAMESPACE_OPEN_SCOPE

using SData = TsTest_SplineData;
using STimes = TsTest_SampleTimes;

static TsSpline _ConvertToTsSpline(const SData &data)
{
  const SData::Features features = data.GetRequiredFeatures();
  if ((features & SData::FeatureHermiteSegments) ||
      (features & SData::FeatureExtrapolatingLoops) || (features & SData::FeatureAutoTangents))
  {
    TF_CODING_ERROR("Unsupported spline features");
    return TsSpline();
  }

  const SData::KnotSet &dataKnots = data.GetKnots();

  if (data.GetPreExtrapolation().method == SData::ExtrapSloped && !dataKnots.empty() &&
      dataKnots.begin()->nextSegInterpMethod != SData::InterpCurve)
  {
    TF_CODING_ERROR("Unsupported pre-slope");
    return TsSpline();
  }

  if (data.GetPostExtrapolation().method == SData::ExtrapSloped && !dataKnots.empty() &&
      dataKnots.rbegin()->nextSegInterpMethod != SData::InterpCurve)
  {
    TF_CODING_ERROR("Unsupported post-slope");
    return TsSpline();
  }

  TsSpline spline;

  const TsExtrapolationType leftExtrap = (data.GetPreExtrapolation().method == SData::ExtrapHeld ?
                                              TsExtrapolationHeld :
                                              TsExtrapolationLinear);
  const TsExtrapolationType rightExtrap = (data.GetPostExtrapolation().method ==
                                                   SData::ExtrapHeld ?
                                               TsExtrapolationHeld :
                                               TsExtrapolationLinear);
  spline.SetExtrapolation(leftExtrap, rightExtrap);

  for (const SData::Knot &dataKnot : dataKnots) {
    TsKeyFrame knot;

    knot.SetTime(dataKnot.time);
    knot.SetValue(VtValue(dataKnot.value));
    knot.SetLeftTangentSlope(VtValue(dataKnot.preSlope));
    knot.SetRightTangentSlope(VtValue(dataKnot.postSlope));
    knot.SetLeftTangentLength(dataKnot.preLen);
    knot.SetRightTangentLength(dataKnot.postLen);

    switch (dataKnot.nextSegInterpMethod) {
      case SData::InterpHeld:
        knot.SetKnotType(TsKnotHeld);
        break;
      case SData::InterpLinear:
        knot.SetKnotType(TsKnotLinear);
        break;
      case SData::InterpCurve:
        knot.SetKnotType(TsKnotBezier);
        break;
      default:
        TF_CODING_ERROR("Unexpected knot type");
    }

    if (dataKnot.isDualValued) {
      knot.SetIsDualValued(true);
      knot.SetValue(VtValue(dataKnot.preValue), TsLeft);
    }

    spline.SetKeyFrame(knot);
  }

  if (data.GetPreExtrapolation().method == SData::ExtrapLinear && !dataKnots.empty() &&
      dataKnots.begin()->nextSegInterpMethod == SData::InterpCurve)
  {
    TsKeyFrame knot = *(spline.begin());
    knot.SetLeftTangentSlope(knot.GetRightTangentSlope());
    knot.SetLeftTangentLength(1.0);
    spline.SetKeyFrame(knot);
  }
  else if (data.GetPreExtrapolation().method == SData::ExtrapSloped && !dataKnots.empty()) {
    TsKeyFrame knot = *(spline.begin());
    knot.SetLeftTangentSlope(VtValue(data.GetPreExtrapolation().slope));
    knot.SetLeftTangentLength(1.0);
    spline.SetKeyFrame(knot);
  }

  if (data.GetPostExtrapolation().method == SData::ExtrapLinear && !dataKnots.empty() &&
      dataKnots.rbegin()->nextSegInterpMethod == SData::InterpCurve)
  {
    TsKeyFrame knot = *(spline.rbegin());
    knot.SetRightTangentSlope(knot.GetLeftTangentSlope());
    knot.SetRightTangentLength(1.0);
    spline.SetKeyFrame(knot);
  }
  else if (data.GetPostExtrapolation().method == SData::ExtrapSloped && !dataKnots.empty()) {
    TsKeyFrame knot = *(spline.rbegin());
    knot.SetRightTangentSlope(VtValue(data.GetPostExtrapolation().slope));
    knot.SetRightTangentLength(1.0);
    spline.SetKeyFrame(knot);
  }

  const SData::InnerLoopParams &loop = data.GetInnerLoopParams();
  if (loop.enabled) {
    // XXX: account for TsLoopParams not yet having the closedEnd feature
    const double postLenAdj = (loop.closedEnd && loop.postLoopEnd > loop.protoEnd ? 1 : 0);

    spline.SetLoopParams(TsLoopParams(true,
                                      loop.protoStart,
                                      loop.protoEnd - loop.protoStart,
                                      loop.protoStart - loop.preLoopStart,
                                      loop.postLoopEnd - loop.protoEnd + postLenAdj,
                                      loop.valueOffset));
  }

  return spline;
}

static SData _ConvertToSplineData(const TsSpline &spline)
{
  SData result;

  auto extrapPair = spline.GetExtrapolation();
  result.SetPreExtrapolation(extrapPair.first == TsExtrapolationHeld ? SData::ExtrapHeld :
                                                                       SData::ExtrapLinear);
  result.SetPostExtrapolation(extrapPair.second == TsExtrapolationHeld ? SData::ExtrapHeld :
                                                                         SData::ExtrapLinear);

  for (const TsKeyFrame &knot : spline) {
    SData::Knot dataKnot;

    dataKnot.time = knot.GetTime();
    dataKnot.value = knot.GetValue().Get<double>();
    dataKnot.preSlope = knot.GetLeftTangentSlope().Get<double>();
    dataKnot.postSlope = knot.GetRightTangentSlope().Get<double>();
    dataKnot.preLen = knot.GetLeftTangentLength();
    dataKnot.postLen = knot.GetRightTangentLength();

    switch (knot.GetKnotType()) {
      case TsKnotHeld:
        dataKnot.nextSegInterpMethod = SData::InterpHeld;
        break;
      case TsKnotLinear:
        dataKnot.nextSegInterpMethod = SData::InterpLinear;
        break;
      case TsKnotBezier:
        dataKnot.nextSegInterpMethod = SData::InterpCurve;
        break;
      default:
        TF_CODING_ERROR("Unexpected knot type");
    }

    if (knot.GetIsDualValued()) {
      dataKnot.isDualValued = true;
      dataKnot.preValue = knot.GetLeftValue().Get<double>();
    }

    result.AddKnot(dataKnot);
  }

  return result;
}

TsTest_SampleVec TsTest_TsEvaluator::Eval(const SData &splineData, const STimes &sampleTimes) const
{
  const TsSpline spline = _ConvertToTsSpline(splineData);
  if (spline.empty())
    return {};

  TsTest_SampleVec result;

  for (const STimes::SampleTime time : sampleTimes.GetTimes()) {
    const TsSide side = (time.pre ? TsLeft : TsRight);
    result.push_back(TsTest_Sample(time.time, spline.Eval(time.time, side).Get<double>()));
  }

  return result;
}

TsTest_SampleVec TsTest_TsEvaluator::Sample(const SData &splineData, const double tolerance) const
{
  const TsSpline spline = _ConvertToTsSpline(splineData);
  if (spline.empty())
    return {};

  if (spline.size() < 2)
    return {};

  const TsSamples samples = spline.Sample(spline.begin()->GetTime(),
                                          spline.rbegin()->GetTime(),
                                          /* timeScale = */ 1,
                                          /* valueScale = */ 1,
                                          /* tolerance = */ 1e-6);

  TsTest_SampleVec result;

  for (const TsValueSample &sample : samples) {
    // XXX: is this a correct interpretation?
    result.push_back(TsTest_Sample(sample.leftTime, sample.leftValue.Get<double>()));
  }

  return result;
}

TsTest_SplineData TsTest_TsEvaluator::BakeInnerLoops(const SData &splineData) const
{
  if (!splineData.GetInnerLoopParams().enabled)
    return splineData;

  TsSpline spline = _ConvertToTsSpline(splineData);
  spline.BakeSplineLoops();
  return _ConvertToSplineData(spline);
}

PXR_NAMESPACE_CLOSE_SCOPE
