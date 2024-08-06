//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "Tf/diagnostic.h"
#include "Tf/pyEnum.h"

#include <boost/python/def.hpp>

using namespace boost::python;

PXR_NAMESPACE_USING_DIRECTIVE

void wrapDiagnostic()
{
  TfPyWrapEnum<TfDiagnosticType>();

  def("InstallTerminateAndCrashHandlers", TfInstallTerminateAndCrashHandlers);
}
