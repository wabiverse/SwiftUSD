//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/pyFunction.h"
#include "Tf/pyObjWrapper.h"
#include "pxr/pxrns.h"

#include <boost/python/object.hpp>

#include <string>

using namespace boost;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapFunction()
{
  TfPyFunctionFromPython<void()>();
  TfPyFunctionFromPython<bool()>();
  TfPyFunctionFromPython<int()>();
  TfPyFunctionFromPython<long()>();
  TfPyFunctionFromPython<double()>();
  TfPyFunctionFromPython<std::string()>();
  TfPyFunctionFromPython<python::object()>();
  TfPyFunctionFromPython<TfPyObjWrapper()>();
}
