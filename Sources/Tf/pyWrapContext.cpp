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

TF_INSTANTIATE_SINGLETON(Tf_PyWrapContextManager);

Tf_PyWrapContextManager::Tf_PyWrapContextManager()
{
  // initialize the stack of context names
  _contextStack.clear();
}

PXR_NAMESPACE_CLOSE_SCOPE
