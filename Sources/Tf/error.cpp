//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Tf/error.h"
#include "pxr/pxrns.h"

#include "Tf/diagnosticMgr.h"

#include <string>

using std::string;

PXR_NAMESPACE_OPEN_SCOPE

TfError::TfError(TfEnum errorCode,
                 const char *errorCodeString,
                 TfCallContext const &context,
                 const string &commentary,
                 TfDiagnosticInfo info,
                 bool quiet)
    : TfDiagnosticBase(errorCode, errorCodeString, context, commentary, info, quiet)
{
  _serial = TfDiagnosticMgr::GetInstance()._nextSerial.fetch_add(1);
}

PXR_NAMESPACE_CLOSE_SCOPE
