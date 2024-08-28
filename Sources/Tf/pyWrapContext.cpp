//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/diagnosticLite.h"
#include "Tf/instantiateSingleton.h"
#include "Tf/pyWrapContext.h"

PXR_NAMESPACE_OPEN_SCOPE

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

TF_INSTANTIATE_SINGLETON(Tf_PyWrapContextManager);

Tf_PyWrapContextManager::Tf_PyWrapContextManager()
{
  // initialize the stack of context names
  _contextStack.clear();
}

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_CLOSE_SCOPE
