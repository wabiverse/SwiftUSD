//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Tf/pyFunction.h"
#include "Tf/pyObjWrapper.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/object.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

#include <string>

PXR_NAMESPACE_USING_DIRECTIVE

void wrapFunction() {
    TfPyFunctionFromPython<void ()>();
    TfPyFunctionFromPython<bool ()>();
    TfPyFunctionFromPython<int ()>();
    TfPyFunctionFromPython<long ()>();
    TfPyFunctionFromPython<double ()>();
    TfPyFunctionFromPython<std::string ()>();
    TfPyFunctionFromPython<pxr_boost::python::object ()>();
    TfPyFunctionFromPython<TfPyObjWrapper ()>();
}
