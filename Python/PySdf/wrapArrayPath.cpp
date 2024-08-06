//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Sdf/path.h"
#include "Vt/array.h"
#include "Vt/valueFromPython.h"
#include "Vt/wrapArray.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace Vt_WrapArray {
template<> std::string GetVtArrayName<VtArray<SdfPath>>()
{
  return "PathArray";
}
}  // namespace Vt_WrapArray

template<> SdfPath VtZero()
{
  return SdfPath();
}

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayPath()
{
  VtWrapArray<VtArray<SdfPath>>();
  VtValueFromPythonLValue<VtArray<SdfPath>>();
}
