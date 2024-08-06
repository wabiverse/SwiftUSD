//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include <locale>

#include "UsdRi/rmanUtilities.h"

#include "Tf/token.h"

#include <boost/python/def.hpp>
#include <boost/python/return_by_value.hpp>
#include <boost/python/return_value_policy.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapUsdRiRmanUtilities()
{
  def("ConvertToRManInterpolateBoundary",
      (int (*)(const TfToken &))UsdRiConvertToRManInterpolateBoundary,
      return_value_policy<return_by_value>());
  def("ConvertFromRManInterpolateBoundary",
      (const TfToken &(*)(int))UsdRiConvertFromRManInterpolateBoundary,
      return_value_policy<return_by_value>());

  def("ConvertToRManFaceVaryingLinearInterpolation",
      (int (*)(const TfToken &))UsdRiConvertToRManFaceVaryingLinearInterpolation,
      return_value_policy<return_by_value>());
  def("ConvertFromRManFaceVaryingLinearInterpolation",
      (const TfToken &(*)(int))UsdRiConvertFromRManFaceVaryingLinearInterpolation,
      return_value_policy<return_by_value>());
}
