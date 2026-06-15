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
#include "Tf/staticData.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/handle.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#if PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_OPEN_SCOPE

using namespace pxr_boost::python;

TF_REGISTRY_FUNCTION(TfEnum) {
    TF_ADD_ENUM_NAME(TF_PYTHON_EXCEPTION);
}

// The held handle<> is intentionally leaked to avoid Python refcount ops
// during shutdown, which is unsafe if Python has been finalized.
static TfStaticData<handle<>> _ExceptionClass;

handle<> Tf_PyGetErrorExceptionClass()
{
    return *_ExceptionClass;
}

void Tf_PySetErrorExceptionClass(object const &cls)
{
    *_ExceptionClass = handle<>(borrowed(cls.ptr()));
}

TfPyExceptionStateScope::TfPyExceptionStateScope() :
    _state(TfPyExceptionState::Fetch())
{
}

TfPyExceptionStateScope::~TfPyExceptionStateScope()
{
    _state.Restore();
}

PXR_NAMESPACE_CLOSE_SCOPE
#endif // PXR_PYTHON_SUPPORT_ENABLED