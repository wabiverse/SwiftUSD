//
// Copyright 2024 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"
#include "Ts/tsTest_AnimXEvaluator.h"
#include "Ts/tsTest_SplineData.h"
#include "Ts/tsTest_SampleTimes.h"
#include "Tf/pyResultConversions.h"
#include "Tf/pyEnum.h"

#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/class.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED
#if PXR_PYTHON_SUPPORT_ENABLED
#include "boost/python/make_constructor.hpp"
#endif // PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_USING_DIRECTIVE

using namespace pxr_boost::python;

using This = TsTest_AnimXEvaluator;


static This*
_ConstructEvaluator(
    const This::AutoTanType autoTanType)
{
    return new This(autoTanType);
}


void wrapTsTest_AnimXEvaluator()
{
    // First the class object, so we can create a scope for it...
    class_<This> classObj("TsTest_AnimXEvaluator", no_init);
    scope classScope(classObj);

    // ...then the nested type wrappings, which require the scope...
    TfPyWrapEnum<This::AutoTanType>();

    // ...then the defs, which must occur after the nested type wrappings.
    classObj

        .def("__init__",
            make_constructor(
                &_ConstructEvaluator, default_call_policies(),
                (arg("autoTanType") = This::AutoTanAuto)))

        .def("Eval", &This::Eval,
            (arg("splineData"),
             arg("sampleTimes")),
            return_value_policy<TfPySequenceToList>())

        ;
}
