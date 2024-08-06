//
// Copyright 2019 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Sdf/timeCode.h"
#include "Vt/array.h"
#include "Vt/valueFromPython.h"
#include "Vt/wrapArray.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace Vt_WrapArray {
template<> std::string GetVtArrayName<VtArray<SdfTimeCode>>()
{
  return "TimeCodeArray";
}
}  // namespace Vt_WrapArray

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayTimeCode()
{
  VtWrapArray<VtArray<SdfTimeCode>>();
  VtValueFromPythonLValue<VtArray<SdfTimeCode>>();
}
