//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "UsdValidation/timeRange.h"

#include "Gf/interval.h"
#include "Usd/timeCode.h"

PXR_NAMESPACE_OPEN_SCOPE

UsdValidationTimeRange::UsdValidationTimeRange() : 
    _interval(GfInterval::GetFullInterval()), _includeTimeCodeDefault(true)
{
}

UsdValidationTimeRange::UsdValidationTimeRange(const UsdTimeCode &timeCode)
    : _interval(timeCode.IsDefault() ? 
                GfInterval() : GfInterval(timeCode.GetValue())),
      _includeTimeCodeDefault(timeCode.IsDefault())
{
}

UsdValidationTimeRange::UsdValidationTimeRange(
    const GfInterval &interval, bool includeTimeCodeDefault)
    : _interval(interval), _includeTimeCodeDefault(includeTimeCodeDefault)
{
}

bool
UsdValidationTimeRange::IncludesTimeCodeDefault() const
{
    return _includeTimeCodeDefault;
}

GfInterval
UsdValidationTimeRange::UsdValidationTimeRange::GetInterval() const
{
    return _interval;
}

PXR_NAMESPACE_CLOSE_SCOPE
