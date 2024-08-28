//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/singleton.h"
#include "Tf/instantiateSingleton.h"
#include "Tf/pyLock.h"
#include "pxr/pxrns.h"

#include <memory>

PXR_NAMESPACE_OPEN_SCOPE

// This GIL-releasing helper is declared in tf/instantiateSingleton.h.  It
// exists so that users of instantiateSingleton.h don't need to pull in the
// Python headers via tf/pyLock.h.

Tf_SingletonPyGILDropper::Tf_SingletonPyGILDropper()
{
#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
  if (PyGILState_Check()) {
    _pyLock = std::make_unique<TfPyLock>();
    _pyLock->BeginAllowThreads();
  }
#endif  // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
}

Tf_SingletonPyGILDropper::~Tf_SingletonPyGILDropper() = default;

PXR_NAMESPACE_CLOSE_SCOPE
