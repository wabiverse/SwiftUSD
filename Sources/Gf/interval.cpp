//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Gf/interval.h"
#include "Gf/ostreamHelpers.h"
#include "Tf/type.h"
#include "pxr/pxrns.h"

#include <ostream>

PXR_NAMESPACE_OPEN_SCOPE

// CODE_COVERAGE_OFF_GCOV_BUG  you know the drill.
TF_REGISTRY_FUNCTION(TfType)
{
  TfType::Define<GfInterval>();
}
// CODE_COVERAGE_ON_GCOV_BUG

std::ostream &operator<<(std::ostream &out, const GfInterval &i)
{
  out << (i.IsMinClosed() ? "[" : "(");
  out << Gf_OstreamHelperP(i.GetMin()) << ", ";
  out << Gf_OstreamHelperP(i.GetMax());
  out << (i.IsMaxClosed() ? "]" : ")");
  return out;
}

PXR_NAMESPACE_CLOSE_SCOPE
