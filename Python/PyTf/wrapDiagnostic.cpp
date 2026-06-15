//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/diagnostic.h"
#include "Tf/pyEnum.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

void wrapDiagnostic()
{
    TfPyWrapEnum<TfDiagnosticType>();

    def("InstallTerminateAndCrashHandlers",
        TfInstallTerminateAndCrashHandlers);

}
