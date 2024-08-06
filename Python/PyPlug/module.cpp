//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/pyModule.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_USING_DIRECTIVE

TF_WRAP_MODULE
{
  TF_WRAP(Notice);
  TF_WRAP(Plugin);
  TF_WRAP(Registry);

  TF_WRAP(_TestPlugBase);
}
