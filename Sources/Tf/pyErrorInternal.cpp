//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyErrorInternal.h"

#include "Tf/enum.h"
#include "Tf/registryManager.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

#include <boost/python/handle.hpp>
#include <boost/python/object.hpp>

using namespace boost::python;

PXR_NAMESPACE_OPEN_SCOPE

TF_REGISTRY_FUNCTION(TfEnum)
{
  TF_ADD_ENUM_NAME(TF_PYTHON_EXCEPTION);
}

// Should probably use a better mechanism.

static handle<> _ExceptionClass;

handle<> Tf_PyGetErrorExceptionClass()
{
  return _ExceptionClass;
}

void Tf_PySetErrorExceptionClass(object const &cls)
{
  _ExceptionClass = handle<>(borrowed(cls.ptr()));
}

TfPyExceptionStateScope::TfPyExceptionStateScope() : _state(TfPyExceptionState::Fetch()) {}

TfPyExceptionStateScope::~TfPyExceptionStateScope()
{
  _state.Restore();
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
