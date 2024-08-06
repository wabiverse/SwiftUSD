//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Sdf/assetPath.h"
#include "Vt/array.h"
#include "Vt/valueFromPython.h"
#include "Vt/wrapArray.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

namespace Vt_WrapArray {
template<> std::string GetVtArrayName<VtArray<SdfAssetPath>>()
{
  return "AssetPathArray";
}
}  // namespace Vt_WrapArray

template<> SdfAssetPath VtZero()
{
  return SdfAssetPath();
}

PXR_NAMESPACE_CLOSE_SCOPE

PXR_NAMESPACE_USING_DIRECTIVE

void wrapArrayAssetPath()
{
  VtWrapArray<VtArray<SdfAssetPath>>();
  VtValueFromPythonLValue<VtArray<SdfAssetPath>>();
}
