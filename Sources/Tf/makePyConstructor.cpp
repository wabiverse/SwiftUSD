//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/makePyConstructor.h"

#if PXR_PYTHON_SUPPORT_ENABLED
PXR_NAMESPACE_OPEN_SCOPE

namespace Tf_MakePyConstructor {

bp::object _DummyInit(bp::tuple const & /* args */,
                      bp::dict const & /* kw */) {
    return bp::object();
}

}

PXR_NAMESPACE_CLOSE_SCOPE
#endif // PXR_PYTHON_SUPPORT_ENABLED