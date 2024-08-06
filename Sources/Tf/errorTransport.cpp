//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/errorTransport.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

void TfErrorTransport::_PostImpl()
{
  TfDiagnosticMgr::GetInstance()._SpliceErrors(_errorList);
}

PXR_NAMESPACE_CLOSE_SCOPE
