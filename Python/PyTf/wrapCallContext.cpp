//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/callContext.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

using std::string;
PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

static string
_GetFileString(TfCallContext const& cc) {
    return string(cc.GetFile());
}

static string
_GetFunctionString(TfCallContext const& cc) {
    return string(cc.GetFunction());
}

static string
_GetPrettyFunctionString(TfCallContext const& cc) {
    return string(cc.GetPrettyFunction());
}

} // anonymous namespace 

void wrapCallContext() {
    typedef TfCallContext This;

    class_ <This> ("CallContext", no_init)
        .add_property("file", &_GetFileString)
        .add_property("function", &_GetFunctionString)
        .add_property("line", &This::GetLine)
        .add_property("prettyFunction", &_GetPrettyFunctionString)
    ;
}
