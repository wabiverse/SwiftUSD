//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/status.h"
#include "Tf/pyCallContext.h"
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
_Status(string const &msg, string const& moduleName, string const& functionName,
        string const& fileName, int lineNo)
{
    TfDiagnosticMgr::
        StatusHelper(Tf_PythonCallContext(fileName, moduleName,
                                          functionName, lineNo),
                     TF_DIAGNOSTIC_STATUS_TYPE,
                     TfEnum::GetName(TfEnum(TF_DIAGNOSTIC_STATUS_TYPE)).
                     c_str()).
        Post(msg);
}

static void
_QuietStatus(string const& msg)
{
    TfDiagnosticMgr::StatusHelper(
        TfCallContext{},
        TF_DIAGNOSTIC_STATUS_TYPE,
        TfEnum::GetName(TfEnum(TF_DIAGNOSTIC_STATUS_TYPE)).c_str()).Post(msg);
}

static string
TfStatus__repr__(TfStatus const &self)
{
    string ret = TfStringPrintf("Status in '%s' at line %zu in file %s : '%s'",
             self.GetSourceFunction().c_str(),
             self.GetSourceLineNumber(),
             self.GetSourceFileName().c_str(),
             self.GetCommentary().c_str());

    return ret;
}

} // anonymous namespace 

void wrapStatus() {
    def("_Status", &_Status);
    def("_Status", &_QuietStatus);

    typedef TfStatus This;

    // Can't call this scope Status because Tf.Status() is a function def'd
    // above.
    scope statusScope =
        class_<This, bases<TfDiagnosticBase> >("StatusObject", no_init)

        .def("__repr__", TfStatus__repr__)
        ;
}
