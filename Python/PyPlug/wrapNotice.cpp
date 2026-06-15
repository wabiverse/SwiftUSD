//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Plug/notice.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyNoticeWrapper.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace {

TF_INSTANTIATE_NOTICE_WRAPPER(PlugNotice::Base, TfNotice);
TF_INSTANTIATE_NOTICE_WRAPPER(PlugNotice::DidRegisterPlugins, PlugNotice::Base);

} // anonymous namespace 

void
wrapNotice()
{
    scope noticeScope = class_<PlugNotice>("Notice", no_init);

    TfPyNoticeWrapper<PlugNotice::Base, TfNotice>::Wrap()
        ;

    TfPyNoticeWrapper<PlugNotice::DidRegisterPlugins, PlugNotice::Base>::Wrap()
        .def("GetNewPlugins", 
             make_function(&PlugNotice::DidRegisterPlugins::GetNewPlugins,
                           return_value_policy<TfPySequenceToList>()))
        ;
}
