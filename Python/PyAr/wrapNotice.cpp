//
// Copyright 2021 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/pxrns.h"

#include "Ar/notice.h"

#include "Tf/pyNoticeWrapper.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/scope.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

namespace
{

TF_INSTANTIATE_NOTICE_WRAPPER(
    ArNotice::ResolverNotice, TfNotice);
TF_INSTANTIATE_NOTICE_WRAPPER(
    ArNotice::ResolverChanged, ArNotice::ResolverNotice);

} // end anonymous namespace

void
wrapNotice()
{
    scope s = class_<ArNotice>("Notice", no_init);
    
    TfPyNoticeWrapper<ArNotice::ResolverNotice, TfNotice>::Wrap();

    TfPyNoticeWrapper<
        ArNotice::ResolverChanged, ArNotice::ResolverNotice>::Wrap()
        .def("AffectsContext", &ArNotice::ResolverChanged::AffectsContext,
             args("context"))
        ;
}
