//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/warning.h"
#include "Tf/pyCallContext.h"
#include "Tf/callContext.h"
#include "Tf/diagnosticMgr.h"
#include "Tf/stringUtils.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/def.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static void
_Warn(string const &msg, string const& moduleName, string const& functionName,
      string const& fileName, int lineNo)
{
    TfDiagnosticMgr::
        WarningHelper(Tf_PythonCallContext(fileName, moduleName,
                                           functionName, lineNo),
                      TF_DIAGNOSTIC_WARNING_TYPE,
                      TfEnum::GetName(TfEnum(TF_DIAGNOSTIC_WARNING_TYPE)).
                      c_str()).
        Post(msg);
}

static string
TfWarning__repr__(TfWarning const &self)
{
    string ret = TfStringPrintf("Warning in '%s' at line %zu in file %s : '%s'",
             self.GetSourceFunction().c_str(),
             self.GetSourceLineNumber(),
             self.GetSourceFileName().c_str(),
             self.GetCommentary().c_str());

    return ret;
}

} // anonymous namespace 

void wrapWarning() {
    def("_Warn", &_Warn);

    typedef TfWarning This;

    scope warningScope =
        class_<This, bases<TfDiagnosticBase> >("Warning", no_init)

        .def("__repr__", TfWarning__repr__)
        ;
}
