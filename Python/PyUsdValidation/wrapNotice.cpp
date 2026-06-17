//
// Copyright 2026 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "UsdValidation/notice.h"
#include "UsdValidation/validator.h"
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

TF_INSTANTIATE_NOTICE_WRAPPER(
    UsdValidationNotice::DidRegisterValidator, TfNotice);
TF_INSTANTIATE_NOTICE_WRAPPER(
    UsdValidationNotice::DidRegisterValidatorSuite, TfNotice);

} // anonymous namespace

void
wrapUsdValidationNotice()
{
    scope noticeScope = class_<UsdValidationNotice>("Notice", no_init);

    TfPyNoticeWrapper<
        UsdValidationNotice::DidRegisterValidator, TfNotice>::Wrap()
        .def("GetValidator",
             &UsdValidationNotice::DidRegisterValidator::GetValidator,
             return_value_policy<reference_existing_object>())
        ;

    TfPyNoticeWrapper<
        UsdValidationNotice::DidRegisterValidatorSuite, TfNotice>::Wrap()
        .def("GetValidatorSuite",
             &UsdValidationNotice::DidRegisterValidatorSuite::GetValidatorSuite,
             return_value_policy<reference_existing_object>())
        ;
}
