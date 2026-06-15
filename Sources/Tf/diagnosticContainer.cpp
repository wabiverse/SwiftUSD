//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/diagnosticContainer.h"
#include "Tf/diagnosticMgr.h"
#include "Tf/stl.h"

PXR_NAMESPACE_OPEN_SCOPE

void
Tf_DiagnosticContainer::Post()
{
    TfDiagnosticMgr &mgr = TfDiagnosticMgr::GetInstance();
    Iterator it = GetIterator();
    while (it.Next(TfOverloads {
                [&mgr](TfError const &e)   { mgr._ReportError(e); },
                [&mgr](TfWarning const &w) { mgr.PostWarning(w);  },
                [&mgr](TfStatus const &s)  { mgr.PostStatus(s);   }
            }));
    Clear();
}

PXR_NAMESPACE_CLOSE_SCOPE
