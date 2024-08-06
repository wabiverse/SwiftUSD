//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Sdf/pathTable.h"
#include "Tf/pyLock.h"
#include "Work/loops.h"
#include "pxr/pxrns.h"

PXR_NAMESPACE_OPEN_SCOPE

void Sdf_VisitPathTableInParallel(void **entryStart,
                                  size_t numEntries,
                                  TfFunctionRef<void(void *&)> const visitFn)
{
  // We must release the GIL here if we have it; otherwise, if visitFn
  // attempted to take the GIL, the workers would deadlock.
  TF_PY_ALLOW_THREADS_IN_SCOPE();

  WorkParallelForN(numEntries, [&entryStart, visitFn](size_t i, size_t end) {
    for (; i != end; ++i) {
      if (entryStart[i]) {
        visitFn(entryStart[i]);
      }
    }
  });
}

PXR_NAMESPACE_CLOSE_SCOPE
