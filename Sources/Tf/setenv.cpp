//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/setenv.h"
#include "Arch/env.h"
#include "Arch/errno.h"
#include "Tf/diagnostic.h"
#include "pxr/pxrns.h"

#ifdef PXR_PYTHON_SUPPORT_ENABLED
#  include "Tf/pyUtils.h"
#endif  // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_OPEN_SCOPE

bool TfSetenv(const std::string &name, const std::string &value)
{
#ifdef PXR_PYTHON_SUPPORT_ENABLED
  if (TfPyIsInitialized()) {
    return TfPySetenv(name, value);
  }
#endif  // PXR_PYTHON_SUPPORT_ENABLED

  if (ArchSetEnv(name.c_str(), value.c_str(), /* overwrite */ true)) {
    return true;
  }

  TF_WARN("Error setting '%s': %s", name.c_str(), ArchStrerror().c_str());
  return false;
}

bool TfUnsetenv(const std::string &name)
{
#ifdef PXR_PYTHON_SUPPORT_ENABLED
  if (TfPyIsInitialized()) {
    return TfPyUnsetenv(name);
  }
#endif  // PXR_PYTHON_SUPPORT_ENABLED

  if (ArchRemoveEnv(name.c_str())) {
    return true;
  }

  TF_WARN("Error unsetting '%s': %s", name.c_str(), ArchStrerror().c_str());
  return false;
}

PXR_NAMESPACE_CLOSE_SCOPE
