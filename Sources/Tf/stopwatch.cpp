//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/stopwatch.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

std::ostream &operator<<(std::ostream &out, const TfStopwatch &s)
{
  return out << s.GetSeconds() << " seconds";
}

PXR_NAMESPACE_CLOSE_SCOPE
