//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyModuleNotice.h"
#include "Tf/pyNoticeWrapper.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_by_value.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/return_value_policy.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

TF_INSTANTIATE_NOTICE_WRAPPER(TfPyModuleWasLoaded, TfNotice);

} // anonymous namespace 

void wrapPyModuleNotice() {

    TfPyNoticeWrapper<TfPyModuleWasLoaded, TfNotice>::Wrap("PyModuleWasLoaded")
        .def("name", make_function(&TfPyModuleWasLoaded::GetName,
                                   return_value_policy<return_by_value>()))
        ;
}
