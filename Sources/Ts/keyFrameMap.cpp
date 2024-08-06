//
// Copyright 2023 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Ts/keyFrameMap.h"
#include "pxr/pxrns.h"

#include "Ts/data.h"
#include "Ts/keyFrame.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace {

/// A predicate for TfFindBoundary which finds the lower
/// bound at a given time. It returns true for all keyframes
/// which have a time less than \p t.
class _LowerBoundPredicate {
 public:
  explicit _LowerBoundPredicate(TsTime t) : _time(t) {}

  bool operator()(const TsKeyFrame &kf) const
  {
    return kf.GetTime() < _time;
  }

 private:
  TsTime _time;
};

/// A predicate for TfFindBoundary which finds the upper
/// bound at a given time. It returns true for all keyframes
/// which have a time less than or equal to \p t.
class _UpperBoundPredicate {
 public:
  explicit _UpperBoundPredicate(TsTime t) : _time(t) {}

  bool operator()(const TsKeyFrame &kf) const
  {
    return kf.GetTime() <= _time;
  }

 private:
  TsTime _time;
};

}  // namespace

template<class Iterator, class Predicate>
static Iterator Ts_FindBoundaryImpl(Iterator begin, Iterator end, TsTime t, Predicate const &pred)
{
  static const int MaxSteps = 3;

  // Empty range.
  if (begin == end) {
    return end;
  }
  Iterator last = std::prev(end);
  // If predicate is true for last element, return end.
  if (pred(*last)) {
    return end;
  }
  // If predicate is false for first element, return begin.
  if (!pred(*begin)) {
    return begin;
  }

  // Splines often have keys that are fairly evenly spaced, so we can guess an
  // index to look near by using where `t` falls within the range of times.
  // We take the fraction (t - firstKey.GetTime()) / (lastKey.GetTime() -
  // firstKey.GetTime()), and multiply that by the number of keyframes to get
  // an index.  We then start searching from there.  If we don't find the
  // position of interest within a couple of steps, we resort to binary search
  // on the remaining range.

  TsTime firstTime = begin->GetTime();
  TsTime lastTime = last->GetTime();

  size_t len = std::distance(begin, end);
  double frac = (t - firstTime) / (lastTime - firstTime);
  size_t guessIdx(len * frac);

  // We should really only ever take this branch, since times outside the
  // range should've been handled when we checked the endpoints above.  This
  // guard is here just in case some floating point error in the fraction
  // calculation pushes us slightly off the ends.
  if (ARCH_LIKELY(guessIdx >= 0 && guessIdx < len)) {
    Iterator guessIter = std::next(begin, guessIdx);
    if (pred(*guessIter)) {
      // Walk forward a few steps to try to find the boundary.
      ++guessIter;
      for (int i = 0; i != MaxSteps && guessIter != end; ++i, ++guessIter) {
        if (!pred(*guessIter)) {
          return guessIter;
        }
      }
      // Did not find the boundary -- fall back to binary search.
      return guessIter == end ? guessIter : TfFindBoundary(guessIter, end, pred);
    }
    else {
      if (guessIter == begin) {
        return guessIter;
      }
      // Walk backward a few steps to try to find the boundary.
      for (int i = 0; i != MaxSteps && guessIter != begin; ++i, --guessIter) {
        if (pred(*std::prev(guessIter))) {
          return guessIter;
        }
      }
      // Did not find the boundary -- fall back to binary search.
      return guessIter == begin ? guessIter : TfFindBoundary(begin, guessIter, pred);
    }
  }
  else {
    // Our guess is not within the range -- just binary search.
    return TfFindBoundary(begin, end, pred);
  }
}

TsKeyFrameMap::iterator TsKeyFrameMap::lower_bound(TsTime t)
{
  return Ts_FindBoundaryImpl(_data.begin(), _data.end(), t, _LowerBoundPredicate(t));
}

TsKeyFrameMap::const_iterator TsKeyFrameMap::lower_bound(TsTime t) const
{
  return Ts_FindBoundaryImpl(_data.begin(), _data.end(), t, _LowerBoundPredicate(t));
}

TsKeyFrameMap::iterator TsKeyFrameMap::upper_bound(TsTime t)
{
  return Ts_FindBoundaryImpl(_data.begin(), _data.end(), t, _UpperBoundPredicate(t));
}

TsKeyFrameMap::const_iterator TsKeyFrameMap::upper_bound(TsTime t) const
{
  return Ts_FindBoundaryImpl(_data.begin(), _data.end(), t, _UpperBoundPredicate(t));
}

PXR_NAMESPACE_CLOSE_SCOPE
